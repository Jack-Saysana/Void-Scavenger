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
                                        SIM_DIST);
  // Physics collision resolution will move objects in the scene, so we must
  // prepare the game simulations for potential movement
  prepare_object_movement();
  handle_physics_collisions(physics_collisions, num_p_col);
  update_object_movement();

  COLLISION *combat_collisions = NULL;
  size_t num_c_col = get_sim_collisions(combat_sim, &combat_collisions,
                                        sim_sphere->translation,
                                        SIM_DIST);
  handle_combat_collisions(combat_collisions, num_c_col);

  COLLISION *event_collisions = NULL;
  size_t num_e_col = get_sim_collisions(event_sim, &event_collisions,
                                        sim_sphere->translation,
                                        SIM_DIST);
  handle_combat_collisions(event_collisions, num_e_col);

  free(physics_collisions);
  free(combat_collisions);
  free(event_collisions);
}

void handle_physics_collisions(COLLISION *cols, size_t num_cols) {
  for (size_t i = 0; i < num_cols; i++) {
    impulse_resolution(physics_sim, cols[i]);

    object_wrappers[(size_t) cols[i].a_ent->data].to_refresh = 1;
    object_wrappers[(size_t) cols[i].b_ent->data].to_refresh = 1;
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
      a_wrapper->to_delete = 1;
      b_wrapper->to_delete = 1;
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
    if (proj->source == SRC_ENEMY && (target_wrapper->type == PLAYER_OBJ ||
        target_wrapper->type == PLAYER_SHIP_OBJ)) {
      decrement_player_health(proj->damage);
    } else if (proj->source == SRC_PLAYER &&
               (target_wrapper->type == ENEMY_OBJ ||
                target_wrapper->type == ENEMY_SHIP_OBJ)) {
      decrement_enemy_health((size_t) target_wrapper->data, proj->damage);
    }

    proj_wrapper->to_delete = 1;
  }
}

void handle_event_collisions(COLLISION *cols, size_t num_cols) {
  SOBJ *target_wrapper = NULL;

  SOBJ *a_wrapper = NULL;
  SOBJ *b_wrapper = NULL;
  for (size_t i = 0; i < num_cols; i++) {
    a_wrapper = object_wrappers + (size_t) cols[i].a_ent->data;
    b_wrapper = object_wrappers + (size_t) cols[i].b_ent->data;

    if (a_wrapper->type == DEAD_ZONE_OBJ && b_wrapper->type != DEAD_ZONE_OBJ) {
      target_wrapper = b_wrapper;
    } else if (a_wrapper->type != DEAD_ZONE_OBJ &&
               b_wrapper->type == DEAD_ZONE_OBJ) {
      target_wrapper = a_wrapper;
    } else {
      continue;
    }

    if (target_wrapper->type == PLAYER_SHIP_OBJ) {
      decrement_player_health(10.0);
    } else if (target_wrapper->type == ENEMY_SHIP_OBJ) {
      decrement_enemy_health((size_t) target_wrapper->data, 10.0);
    } else if (target_wrapper->type == OBSTACLE_OBJ) {
      target_wrapper->to_delete = 1;
    }
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

void decrement_player_health(float damage) {
  if (mode == SPACE && !player_ship.invuln) {
    player_ship.cur_health -= damage;
    if (player_ship.cur_health <= 0.0) {
      fprintf(stderr, "END GAME\n");
    } else {
      player_ship.invuln = 1;
      add_timer(1.0, &player_ship.invuln, 0);
    }
  } else if (mode == STATION && !st_player.invuln) {
    st_player.cur_health -= damage;
    if (st_player.cur_health <= 0.0) {
      fprintf(stderr, "END GAME\n");
    } else {
      st_player.invuln = 1;
      add_timer(1.0, &st_player.invuln, 0);
    }
  }
}

void decrement_enemy_health(size_t index, float damage) {
  if (mode == SPACE) {
    SHIP *enemy = sp_enemies + index;
    if (!enemy->invuln) {
      enemy->cur_health -= damage;
      if (enemy->cur_health <= 0.0) {
        object_wrappers[(size_t) enemy->wrapper_offset].to_delete = 1;
      } else {
        enemy->invuln = 1;
        add_timer(1.0, &enemy->invuln, 0);
      }
    }
  } else if (mode == STATION) {
    ST_ENEMY *enemy = st_enemies + index;
    if (!enemy->invuln) {
      enemy->cur_health -= damage;
      if (enemy->cur_health <= 0.0) {
        object_wrappers[(size_t) enemy->wrapper_offset].to_delete = 1;
      } else {
        enemy->invuln = 1;
        add_timer(1.0, &enemy->invuln, 0);
      }
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

