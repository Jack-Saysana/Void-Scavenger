#include <collision.h>

/*                                COLLISION.C

  Queries and handles all collision events in both the space and station mode
  simulations. Handles physical, combat-based and trigger-based collisions.

*/

void handle_collisions() {
  if (mode != SPACE && mode != STATION) {
    return;
  }

  // Update simulations
  update_query_spheres();
  prepare_object_movement();

  // Get current position of player
  vec3 player_position;
  if (mode == SPACE) {
    glm_vec3_copy(player_ship.ent->translation, player_position);
  } else {
    glm_vec3_copy(st_player.ent->translation, player_position);
  }

  integrate_sim(physics_sim, sim_sphere->translation, SIM_DIST);
  
  // Take new position and find distance between
  if (mode == SPACE) {
    st_player.total_distance_flown += glm_vec3_distance(player_position,
                                        player_ship.ent->translation);
  } else {
    st_player.total_distance_walked += glm_vec3_distance(player_position,
                                              st_player.ent->translation);
  }

  integrate_projectiles();
  update_object_movement();

  // Detect and respond to physics based collisions
  COLLISION *physics_collisions = NULL;
  size_t num_p_col = get_sim_collisions(physics_sim, &physics_collisions,
                                        sim_sphere->translation,
                                        SIM_DIST, 1);
  // Physics collision resolution will move objects in the scene, so we must
  // prepare the game simulations for potential movement
  prepare_object_movement();
  handle_physics_collisions(physics_collisions, num_p_col);
  update_object_movement();

  COLLISION *combat_collisions = NULL;
  size_t num_c_col = get_sim_collisions(combat_sim, &combat_collisions,
                                        sim_sphere->translation,
                                        SIM_DIST, 0);
  handle_combat_collisions(combat_collisions, num_c_col);

  COLLISION *event_collisions = NULL;
  size_t num_e_col = get_sim_collisions(event_sim, &event_collisions,
                                        sim_sphere->translation,
                                        SIM_DIST, 0);
  handle_event_collisions(event_collisions, num_e_col);

  free(physics_collisions);
  free(combat_collisions);
  free(event_collisions);
}

void handle_physics_collisions(COLLISION *cols, size_t num_cols) {
  SOBJ *proj_wrapper = NULL;
  SOBJ *target_wrapper = NULL;

  SOBJ *a_wrapper = NULL;
  SOBJ *b_wrapper = NULL;
  ST_ENEMY *cur_enemy = NULL;

  vec3 rel_vel = GLM_VEC3_ZERO_INIT;
  float damage = 0.0;
  for (size_t i = 0; i < num_cols; i++) {
    proj_wrapper = NULL;
    target_wrapper = NULL;
    a_wrapper = object_wrappers + (size_t) cols[i].a_ent->data;
    b_wrapper = object_wrappers + (size_t) cols[i].b_ent->data;
    glm_vec3_sub(a_wrapper->entity->velocity, b_wrapper->entity->velocity,
                 rel_vel);
    damage = (glm_vec3_norm(rel_vel) * BASE_COLLISION_DAMAGE) /
             BASE_COLLISION_DAMAGE_VEL;
    if (damage < 10.0) {
      damage = 0.0;
    }

    impulse_resolution(physics_sim, cols[i]);

    a_wrapper->to_refresh = 1;
    b_wrapper->to_refresh = 1;

    cur_enemy = NULL;
    if (a_wrapper->type == ENEMY_OBJ && b_wrapper->type == CORRIDOR_OBJ) {
      cur_enemy = st_enemies + (size_t) a_wrapper->data;
      if (cur_enemy->target_corridor == INVALID_INDEX) {
        cur_enemy->target_corridor = (size_t) b_wrapper->data;
      }
    } else if (a_wrapper->type == CORRIDOR_OBJ &&
               b_wrapper->type == ENEMY_OBJ) {
      cur_enemy = st_enemies + (size_t) b_wrapper->data;
      if (cur_enemy->target_corridor == INVALID_INDEX) {
        cur_enemy->target_corridor = (size_t) a_wrapper->data;
      }
    }

    // Ship-on-ship
    if (a_wrapper->type == PLAYER_SHIP_OBJ &&
        b_wrapper->type == ENEMY_SHIP_OBJ) {
      decrement_player_shield(damage, 1.0);
      decrement_enemy_shield((size_t) b_wrapper->data, damage, 1.0);
      continue;
    } else if (a_wrapper->type == ENEMY_SHIP_OBJ &&
               b_wrapper->type == PLAYER_SHIP_OBJ) {
      decrement_player_shield(damage, 1.0);
      decrement_enemy_shield((size_t) a_wrapper->data, damage, 1.0);
      continue;
    } else if (a_wrapper->type == ENEMY_SHIP_OBJ &&
               b_wrapper->type == ENEMY_SHIP_OBJ)  {
      decrement_enemy_shield((size_t) a_wrapper->data, damage, 1.0);
      decrement_enemy_shield((size_t) b_wrapper->data, damage, 1.0);
      continue;
    }

    // Debris-on-ship
    if (a_wrapper->type == OBSTACLE_OBJ && b_wrapper->type != OBSTACLE_OBJ &&
        b_wrapper->type != PROJ_OBJ) {
      proj_wrapper = a_wrapper;
      target_wrapper = b_wrapper;
    } else if (b_wrapper->type == OBSTACLE_OBJ &&
               a_wrapper->type != OBSTACLE_OBJ &&
               a_wrapper->type != PROJ_OBJ) {
      proj_wrapper = b_wrapper;
      target_wrapper = a_wrapper;
    }
    if (proj_wrapper && target_wrapper) {
      if (target_wrapper->type == PLAYER_SHIP_OBJ) {
        decrement_player_shield(damage, 1.0);
      } else if (target_wrapper->type == ENEMY_SHIP_OBJ) {
        decrement_enemy_shield((size_t) target_wrapper->data, damage, 1.0);
      }

      continue;
    }
  }
}

void handle_combat_collisions(COLLISION *cols, size_t num_cols) {
  SOBJ *proj_wrapper = NULL;
  SOBJ *target_wrapper = NULL;

  SOBJ *a_wrapper = NULL;
  SOBJ *b_wrapper = NULL;

  for (size_t i = 0; i < num_cols; i++) {
    proj_wrapper = NULL;
    target_wrapper = NULL;
    a_wrapper = object_wrappers + (size_t) cols[i].a_ent->data;
    b_wrapper = object_wrappers + (size_t) cols[i].b_ent->data;

    // Projectile on ship/character
    if (a_wrapper->type == PROJ_OBJ && b_wrapper->type != PROJ_OBJ) {
      proj_wrapper = a_wrapper;
      target_wrapper = b_wrapper;
    } else if (b_wrapper->type == PROJ_OBJ && a_wrapper->type != PROJ_OBJ) {
      proj_wrapper = b_wrapper;
      target_wrapper = a_wrapper;
    } else {
      continue;
    }

    PROJ *proj = projectiles + (size_t) proj_wrapper->data;
    if (proj->collision) {
      continue;
    }

    if (proj->source == SRC_ENEMY && (target_wrapper->type == PLAYER_OBJ ||
        target_wrapper->type == PLAYER_SHIP_OBJ)) {
      if (mode == STATION || proj->type == BALLISTIC) {
        decrement_player_shield(proj->damage, 0.1);
        st_player.total_damage_taken += proj->damage;
      } else { 
        float shield_dmg = 0;
        float health_dmg = 0;
        if (proj->type == LASER) {
          shield_dmg = proj->damage + (proj->damage/2);
          health_dmg = proj->damage - (proj->damage/2);
        } else if (proj->type == PLASMA) {
          shield_dmg = proj->damage - (proj->damage/2);
          health_dmg = proj->damage + (proj->damage/2);
        }
        if (player_ship.cur_shield >= shield_dmg) {
          decrement_player_shield(shield_dmg, 0.1);
          st_player.total_damage_taken += shield_dmg;
        } else if (player_ship.cur_shield > 0) {
          decrement_player_shield(player_ship.cur_shield, 0.1);
          st_player.total_damage_taken += player_ship.cur_shield;
        } else {
          decrement_player_shield(health_dmg, 0.1);
          st_player.total_damage_taken += health_dmg;
        }
      }
    } else if (proj->source == SRC_PLAYER &&
               (target_wrapper->type == ENEMY_OBJ ||
                target_wrapper->type == ENEMY_SHIP_OBJ)) {
      if (mode == STATION) {
        if (st_enemies[(size_t)target_wrapper->data].cur_health > 0.0) {
          st_player.total_damage_dealt += proj->damage;
        }
        decrement_enemy_shield((size_t) target_wrapper->data, proj->damage, 0.1);
        if (mode == STATION && st_enemies[(size_t)target_wrapper->data].cur_health <= 0.0 && 
            st_enemies[(size_t)target_wrapper->data].dropped_xp == 0) {
          /*Enemey killed by player */
          st_player.total_enemies_defeated++;
          st_enemies[(size_t)target_wrapper->data].dropped_xp = 1;
          float xp = st_enemies[(size_t)target_wrapper->data].amount_xp + E_LEVEL_SCALE * st_player.total_levels_completed;
          xp +=  gen_rand_float_plus_minus(xp/E_XP_RANGE);
          st_player.cur_experience += (int)xp;
          st_player.total_experience += (int) xp;
          if (st_player.cur_experience >= st_player.max_experience) {
            st_player.cur_experience -= st_player.max_experience;
            st_player.cur_level++;
            st_player.max_experience += P_LEVEL_SCALE*st_player.cur_level;
            st_player.skill_points++;
          }
        }
      } else {
        if (proj->type == BALLISTIC) {
          if (sp_enemies[(size_t)target_wrapper->data].cur_health > 0.0 && 
              !sp_enemies[(size_t)target_wrapper->data].invuln) {
            st_player.total_damage_dealt += proj->damage;
          }
          decrement_enemy_shield((size_t) target_wrapper->data, proj->damage, 0.1);
        } else {
          float shield_dmg = 0;
          float health_dmg = 0;
          if (proj->type == LASER) {
            shield_dmg = proj->damage + (proj->damage/2);
            health_dmg = proj->damage - (proj->damage/2);
          } else if (proj->type == PLASMA) {
            shield_dmg = proj->damage - (proj->damage/2);
            health_dmg = proj->damage + (proj->damage/2);
          }
          if (sp_enemies[(size_t)target_wrapper->data].cur_shield >= shield_dmg) {
            if (!sp_enemies[(size_t)target_wrapper->data].invuln) {
              st_player.total_damage_dealt += shield_dmg;
            }
            decrement_enemy_shield((size_t) target_wrapper->data, shield_dmg, 0.1);
          } else if (sp_enemies[(size_t)target_wrapper->data].cur_shield > 0.0) {
            if (!sp_enemies[(size_t)target_wrapper->data].invuln) {
              st_player.total_damage_dealt += sp_enemies[(size_t)target_wrapper->data].cur_shield;
            }
            decrement_enemy_shield((size_t) target_wrapper->data, 
                                   sp_enemies[(size_t)target_wrapper->data].cur_shield, 0.1);
          } else {
            if (sp_enemies[(size_t)target_wrapper->data].cur_health > 0.0 && 
              !sp_enemies[(size_t)target_wrapper->data].invuln) {
              if (health_dmg < sp_enemies[(size_t)target_wrapper->data].cur_health) {
                st_player.total_damage_dealt += health_dmg;
              } else {
                st_player.total_damage_dealt += sp_enemies[(size_t)target_wrapper->data].cur_health;
              }
            }
            decrement_enemy_shield((size_t) target_wrapper->data, health_dmg, 0.1);
          }
        }
        if (sp_enemies[(size_t)target_wrapper->data].cur_health <= 0.0 &&
            !sp_enemies[(size_t)target_wrapper->data].invuln) {
            st_player.total_ships_defeated++;
        }
      }
    }

    start_proj_collision_anim((size_t) proj_wrapper->data);
  }
}

void handle_event_collisions(COLLISION *cols, size_t num_cols) {
  set_terminal_ui(0);
  set_item_prompt(0);
  int player_out_of_bounds = 0;

  SOBJ *target_wrapper = NULL;

  SOBJ *a_wrapper = NULL;
  SOBJ *b_wrapper = NULL;
  vec3 temp = GLM_VEC3_ZERO_INIT;
  for (size_t i = 0; i < num_cols; i++) {
    a_wrapper = object_wrappers + (size_t) cols[i].a_ent->data;
    b_wrapper = object_wrappers + (size_t) cols[i].b_ent->data;

    // Direct enemies away from one another
    if (a_wrapper->type == ENEMY_OBJ && b_wrapper->type == ENEMY_OBJ) {
      glm_vec3_sub(st_enemies[(size_t) a_wrapper->data].ent->translation,
                   st_enemies[(size_t) b_wrapper->data].ent->translation,
                   temp);
      temp[Y] = 0.0;
      glm_vec3_add(temp, st_enemies[(size_t) a_wrapper->data].nearby_enemies,
                   st_enemies[(size_t) a_wrapper->data].nearby_enemies);
      glm_vec3_negate(temp);
      glm_vec3_add(temp, st_enemies[(size_t) b_wrapper->data].nearby_enemies,
                   st_enemies[(size_t) b_wrapper->data].nearby_enemies);
    }

    // Display terminal ui if player close to terminal
    if ((a_wrapper->type == TERMINAL_OBJ && b_wrapper->type == PLAYER_OBJ) ||
        (a_wrapper->type == PLAYER_OBJ && b_wrapper->type == TERMINAL_OBJ)) {
      set_terminal_ui(1);
      continue;
    }

    // Display station part pickup prompt if player close to part
    if ((a_wrapper->type == PLAYER_OBJ && b_wrapper->type == ITEM_OBJ) ||
        (a_wrapper->type == ITEM_OBJ && b_wrapper->type == PLAYER_OBJ)) {
      set_item_prompt(1);
      continue;
    }

    // Switch to station mode upon collision with space station
    if ((a_wrapper->type == PLAYER_SHIP_OBJ &&
          b_wrapper->type == STATION_OBJ) ||
        (a_wrapper->type == STATION_OBJ &&
         b_wrapper->type == PLAYER_SHIP_OBJ)) {
      set_gamemode_station();
      return;
    }

    // Decrement player/enemy health upon collision with deadzones
    if (a_wrapper->type == DEAD_ZONE_OBJ && b_wrapper->type != DEAD_ZONE_OBJ) {
      target_wrapper = b_wrapper;
    } else if (a_wrapper->type != DEAD_ZONE_OBJ &&
               b_wrapper->type == DEAD_ZONE_OBJ) {
      target_wrapper = a_wrapper;
    } else {
      continue;
    }

    if (target_wrapper->type == PLAYER_SHIP_OBJ) {
      player_out_of_bounds = 1;
      decrement_player_health(10.0, 1.0);
    } else if (target_wrapper->type == ENEMY_SHIP_OBJ) {
      decrement_enemy_health((size_t) target_wrapper->data, 5.0, 1.0);
    } else if (target_wrapper->type == OBSTACLE_OBJ) {
      target_wrapper->to_delete = 1;
    }
  }

  if (player_out_of_bounds) {
    set_coords_warning();
  } else {
    stop_coords_warning();
  }
}

void prepare_object_movement() {
  prep_sim_movement(physics_sim);
  prep_sim_movement(combat_sim);
  prep_sim_movement(event_sim);
  prep_sim_movement(render_sim);
}

void update_object_movement() {
  update_sim_movement(physics_sim);
  update_sim_movement(combat_sim);
  update_sim_movement(event_sim);
  update_sim_movement(render_sim);
}

// ================================= HELPERS =================================

void decrement_player_shield(float damage, float timing) {
  if (mode == SPACE && !player_ship.invuln) {
    if (player_ship.cur_shield && damage) {
      sp_player_shield_dmg(NULL);
    }
    player_ship.cur_shield -= damage;
    if (player_ship.cur_shield <= 0.0) {
      player_health_dmg();
      player_ship.cur_health += player_ship.cur_shield;
      player_ship.cur_shield = 0.0;
    }
    if (player_ship.cur_health <= 0.0) {
      player_ship.cur_health = 0.0;
    } else {
      player_ship.invuln = 1;
      add_timer(timing, &player_ship.invuln, 0, NULL);
    }
  } else if (mode == STATION && !st_player.invuln) {
    st_player.cur_shield -= damage;
    if (st_player.cur_shield <= 0.0) {
      player_health_dmg();
      st_player.cur_health += st_player.cur_shield;
      st_player.cur_shield = 0.0;
    }
    if (st_player.cur_health <= 0.0) {
      st_player.cur_health = 0.0;
    } else {
      st_player.invuln = 1;
      add_timer(timing, &st_player.invuln, 0, NULL);
    }
  }
}

void decrement_player_health(float damage, float timing) {
  player_health_dmg();
  if (mode == SPACE && !player_ship.invuln) {
    player_ship.cur_health -= damage;
    if (player_ship.cur_health <= 0.0) {
      player_ship.cur_health = 0.0;
      /* End game */
      game_over();
    } else {
      player_ship.invuln = 1;
      add_timer(timing, &player_ship.invuln, 0, NULL);
    }
  } else if (mode == STATION && !st_player.invuln) {
    st_player.cur_health -= damage;
    if (st_player.cur_health <= 0.0) {
      st_player.cur_health = 0.0;
      /* End game */
      game_over();
    } else {
      st_player.invuln = 1;
      add_timer(timing, &st_player.invuln, 0, NULL);
    }
  }
}

void decrement_enemy_shield(size_t index, float damage, float timing) {
  if (mode == SPACE) {
    SHIP *enemy = sp_enemies + index;
    if (!enemy->invuln) {
      if (enemy->cur_shield && damage) {
        sp_enemy_shield_dmg((void *) index);
      }
      enemy->cur_shield -= damage;
      if (enemy->cur_shield <= 0.0) {
        enemy->cur_health += enemy->cur_shield;
        enemy->cur_shield = 0.0;
      }
      if (enemy->cur_health <= 0.0) {
        object_wrappers[(size_t) enemy->wrapper_offset].to_delete = 1;
      } else {
        enemy->invuln = 1;
        add_timer(timing, &enemy->invuln, 0, NULL);
      }
    }
  } else if (mode == STATION) {
    ST_ENEMY *enemy = st_enemies + index;
    if (!enemy->invuln) {
      enemy->cur_health -= damage;
      enemy->invuln = 1;
      enemy->cur_frame = 0;
      st_enemy_hurt_anim((void *) index);
    }
  }
}

void decrement_enemy_health(size_t index, float damage, float timing) {
  if (mode == SPACE) {
    SHIP *enemy = sp_enemies + index;
    if (!enemy->invuln) {
      enemy->cur_health -= damage;
      if (enemy->cur_health <= 0.0) {
        object_wrappers[(size_t) enemy->wrapper_offset].to_delete = 1;
      } else {
        enemy->invuln = 1;
        add_timer(timing, &enemy->invuln, 0, NULL);
      }
    }
  } else if (mode == STATION) {
    ST_ENEMY *enemy = st_enemies + index;
    if (!enemy->invuln) {
      enemy->cur_health -= damage;
      enemy->invuln = 1;
      enemy->cur_frame = 0;
      st_enemy_hurt_anim((void *) index);
    }
  }
}

void update_query_spheres() {
  prep_sim_movement(render_sim);
  if (mode == SPACE) {
    glm_vec3_copy(player_ship.ent->translation, render_sphere->translation);
    glm_vec3_copy(player_ship.ent->translation, sim_sphere->translation);
  } else if (mode == STATION) {
    glm_vec3_copy(camera.pos, render_sphere->translation);
    glm_vec3_copy(camera.pos, sim_sphere->translation);
  }
  update_sim_movement(render_sim);
}

