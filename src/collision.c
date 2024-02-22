#include <collision.h>

/*                                COLLISION.C

  Queries and handles all collision events in both the space and station mode
  simulations. Handles physical, combat-based and trigger-based collisions.

*/

void handle_collisions() {
  // Update simulations
  update_query_spheres();
  prepare_object_movement();
  integrate_sim(physics_sim, sim_sphere->translation, SIM_DIST);
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
  SOBJ *a_wrapper = NULL;
  SOBJ *b_wrapper = NULL;
  ST_ENEMY *cur_enemy = NULL;
  for (size_t i = 0; i < num_cols; i++) {
    impulse_resolution(physics_sim, cols[i]);

    a_wrapper = object_wrappers + (size_t) cols[i].a_ent->data;
    b_wrapper = object_wrappers + (size_t) cols[i].b_ent->data;

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
  }
}

void handle_combat_collisions(COLLISION *cols, size_t num_cols) {
  SOBJ *proj_wrapper = NULL;
  SOBJ *target_wrapper = NULL;

  SOBJ *a_wrapper = NULL;
  SOBJ *b_wrapper = NULL;

  for (size_t i = 0; i < num_cols; i++) {
    a_wrapper = object_wrappers + (size_t) cols[i].a_ent->data;
    b_wrapper = object_wrappers + (size_t) cols[i].b_ent->data;

    if (a_wrapper->type == PROJ_OBJ && b_wrapper->type == PROJ_OBJ) {
      //start_proj_collision_anim((size_t) a_wrapper->data);
      //start_proj_collision_anim((size_t) b_wrapper->data);
      continue;
    } else if (a_wrapper->type == PROJ_OBJ) {
      proj_wrapper = a_wrapper;
      target_wrapper = b_wrapper;
    } else if (b_wrapper->type == PROJ_OBJ) {
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
      decrement_player_health(proj->damage, 0.1);
    } else if (proj->source == SRC_PLAYER &&
               (target_wrapper->type == ENEMY_OBJ ||
                target_wrapper->type == ENEMY_SHIP_OBJ)) {
      decrement_enemy_health((size_t) target_wrapper->data, proj->damage, 0.1);
    }

    start_proj_collision_anim((size_t) proj_wrapper->data);
  }
}

void handle_event_collisions(COLLISION *cols, size_t num_cols) {
  set_terminal_ui(0);
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

void decrement_player_health(float damage, float timing) {
  if (mode == SPACE && !player_ship.invuln) {
    player_ship.cur_health -= damage;
    if (player_ship.cur_health <= 0.0) {
      player_ship.cur_health = 0.0;
      fprintf(stderr, "END GAME\n");
    } else {
      player_ship.invuln = 1;
      add_timer(timing, &player_ship.invuln, 0, NULL);
    }
  } else if (mode == STATION && !st_player.invuln) {
    st_player.cur_health -= damage;
    if (st_player.cur_health <= 0.0) {
      st_player.cur_health = 0.0;
      fprintf(stderr, "END GAME\n");
    } else {
      st_player.invuln = 1;
      add_timer(timing, &st_player.invuln, 0, NULL);
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
      add_timer(0.03, st_enemy_hurt_anim, -1000, (void *) index);
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

