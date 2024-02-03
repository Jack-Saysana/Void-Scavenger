#include <mode.h>

/*                                   MODE.C

  Implements the functionaility behind switching between station and space
  mode. This implies clearing and repopulating the simulation as well as
  reseting game state between levels. Also implements helper functions for
  tracking the overarching game state of each mode and managing each mode's
  resources accordingly.

*/

// ================================ SPACE MODE ===============================

int init_space_mode() {
  // Initialize simulations
  physics_sim = init_sim(SPACE_SIZE, SPACE_DEPTH);
  combat_sim = init_sim(SPACE_SIZE, SPACE_DEPTH);
  render_sim = init_sim(SPACE_SIZE, SPACE_DEPTH);
  event_sim = init_sim(SPACE_SIZE, SPACE_DEPTH);

  // Initialize ship entity values
  reset_physics(player_ship.ent);
  //player_ship.ent->translation[Z] = -5.0;
  // Place player ship entity into simulations
  int status = player_ship_insert_sim();

  // Initialize and place station entity in simulation
  status = init_enemy_ship_buffer();
  if (status) {
    return -1;
  }

  // Initialize and place asteroid and enemies entities in simulation

  mode = SPACE;
  return 0;
}

void clear_space_mode() {
  // Deallocate all simulations
  free_sim(physics_sim);
  free_sim(combat_sim);
  free_sim(render_sim);
  free_sim(event_sim);

  // Free non-player entities
  for (size_t i = 0; i < num_enemies; i++) {
    free_entity(sp_enemies[i].ent);
  }
  for (size_t i = 0; i < num_projectiles; i++) {
    free_entity(projectiles[i].ent);
  }
  for (size_t i = 0; i < num_obstacles; i++) {
    free_entity(sp_obs[i].ent);
  }
  num_enemies = 0;
  num_projectiles = 0;
  num_obstacles = 0;

  free_enemy_ship_buffer();

  // Reset wrapper buffer length
  num_wrappers = 0;
}

// ============================== STATION MODE ===============================

int init_station_mode() {
  // Initialize simulations
  physics_sim = init_sim(STATION_SIZE, STATION_DEPTH);
  sim_add_force(physics_sim, (vec3) { 0.0, -GRAVITY, 0.0 });
  combat_sim = init_sim(STATION_SIZE, STATION_DEPTH);
  render_sim = init_sim(STATION_SIZE, STATION_DEPTH);
  event_sim = init_sim(STATION_SIZE, STATION_DEPTH);

  // Initialize player entity values
  reset_physics(st_player.ent);

  // Place player entity in simulation
  int status = player_insert_sim();

  // Place station entities in simulations
  status = init_enemy_buffer();
  if (status) {
    return -1;
  }

  for (int i = 0; i < 3; i++) {
    ENTITY *ent = init_test_ent();
    ent->type |= T_IMMUTABLE;
    ent->translation[X] = i * 5.0;
    sim_add_entity(physics_sim, ent, ALLOW_HURT_BOXES);
    sim_add_entity(render_sim, ent, ALLOW_DEFAULT);
  }

  // Place render distance sphere in simulations
  sim_add_entity(render_sim, render_sphere, ALLOW_DEFAULT);

  mode = STATION;
  return 0;
}

void clear_station_mode() {
  // Deallocate all simulations
  free_sim(physics_sim);
  free_sim(combat_sim);
  free_sim(render_sim);
  free_sim(event_sim);

  // Free non-player entities
  for (size_t i = 0; i < num_enemies; i++) {
    free_entity(st_enemies[i].ent);
  }
  for (size_t i = 0; i < num_projectiles; i++) {
    free_entity(projectiles[i].ent);
  }
  for (size_t i = 0; i < num_items; i++) {
    free_entity(items[i].ent);
  }
  for (size_t i = 0; i < num_obstacles; i++) {
    free_entity(st_obs[i].ent);
  }
  num_enemies = 0;
  num_projectiles = 0;
  num_items = 0;
  num_obstacles = 0;

  free_enemy_buffer();

  // Reset wrapper buffer length
  num_wrappers = 0;
}

// ========================= GENERAL GAME MANAGEMENT =========================

int delete_stale_objects() {
  SOBJ *cur_wrapper = NULL;
  for (size_t i = 0; i < num_enemies; i++) {
    if (mode == SPACE) {
      cur_wrapper = object_wrappers + sp_enemies[i].wrapper_offset;
      if (cur_wrapper->to_delete) {
        sp_enemy_remove_sim(i);
        delete_enemy_ship(i);
        i--;
      }
    } else {
      cur_wrapper = object_wrappers + st_enemies[i].wrapper_offset;
      if (cur_wrapper->to_delete) {
        st_enemy_remove_sim(i);
        delete_enemy_ship(i);
        i--;
      }
    }
  }
  for (size_t i = 0; i < num_projectiles; i++) {
    cur_wrapper = object_wrappers + projectiles[i].wrapper_offset;
    if (cur_wrapper->to_delete) {
      projectile_remove_sim(i);
      delete_projectile(i);
      i--;
    }
  }
  for (size_t i = 0; i < num_items; i++) {
    cur_wrapper = object_wrappers + items[i].wrapper_offset;
    if (cur_wrapper->to_delete) {
      // Delete item
    }
  }
  for (size_t i = 0; i < num_obstacles; i++) {
    if (mode == SPACE) {
      cur_wrapper = object_wrappers + sp_obs[i].wrapper_offset;
      if (cur_wrapper->to_delete) {
        // Delete obstacle
      }
    } else {
      cur_wrapper = object_wrappers + st_obs[i].wrapper_offset;
      if (cur_wrapper->to_delete) {
        // Delete obstacle
      }
    }
  }

  return 0;
}
