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
  /* Ensure coordinates are enabled */
  enable_coordinates();

  // Initialize proper render distances
  RENDER_DIST = SP_BASE_RENDER_DIST;
  glm_vec3_copy((vec3) { RENDER_DIST, RENDER_DIST, RENDER_DIST },
                render_sphere->scale);
  SIM_DIST = SP_BASE_SIM_DIST;
  glm_vec3_copy((vec3) { SIM_DIST, SIM_DIST, SIM_DIST }, sim_sphere->scale);
  update_perspective();

  // Initialize simulations
  physics_sim = init_sim(SPACE_SIZE, SPACE_DEPTH);
  combat_sim = init_sim(SPACE_SIZE, SPACE_DEPTH);
  render_sim = init_sim(SPACE_SIZE, SPACE_DEPTH);
  event_sim = init_sim(SPACE_SIZE, SPACE_DEPTH);

  int status = insert_dead_zones();
  if (status) {
    return -1;
  }

  // Initialize ship entity values
  reset_physics(player_ship.ent);

  // Place player ship entity into simulations
  status = player_ship_insert_sim();

  // Initialize and place space entities into simulation
  status = init_enemy_ship_buffer();
  if (status) {
    return -1;
  }

  SHIP *cur_enemy = NULL;
  size_t e_index = 0;
  srand(glfwGetTime());
  int num_enemies = BASE_NUM_ENEMIES + (rand() % 5) - 2;
  if (num_enemies > 0) {
    for (int i = 0; i < num_enemies; i++) {
      e_index = init_enemy_ship(0);
      cur_enemy = sp_enemies + e_index;
      gen_rand_vec3(&cur_enemy->ent->translation, 2.0 * SPACE_SIZE);
      cur_enemy->ent->translation[X] -= SPACE_SIZE;
      cur_enemy->ent->translation[Y] -= SPACE_SIZE;
      cur_enemy->ent->translation[Z] -= SPACE_SIZE;

      gen_rand_vec4(&cur_enemy->ent->rotation, 1.0);
      glm_quat_normalize(cur_enemy->ent->rotation);

      // TODO vary enemy ship parts
      sp_enemy_insert_sim(e_index);
    }
  }

  status = init_space_obstacle_buffer();
  if (status) {
    return -1;
  }

  // Place render distance sphere in simulations
  sim_add_entity(render_sim, render_sphere, ALLOW_DEFAULT);
  sim_add_entity(render_sim, sim_sphere, ALLOW_DEFAULT);

  // Initialize and place asteroid and enemies entities in simulation
  spawn_asteroids();
  spawn_space_debris();

  mode = SPACE;
  return 0;
}

void spawn_asteroids() {
  seed_random();
  vec3 pos = GLM_VEC3_ZERO_INIT;
  vec3 vel = GLM_VEC3_ZERO_INIT;
  vec3 ang_vel = GLM_VEC3_ZERO_INIT;
  vec3 scale = GLM_VEC3_ZERO_INIT;
  float mass = 0.0;
  for (int i = 0; i < NUM_ASTEROIDS; i++) {
    gen_rand_vec3(&pos, 10.0);
    gen_rand_vec3(&vel, 3.0);
    gen_rand_vec3(&ang_vel, 1.5);
    gen_rand_vec3(&scale, 3.0);
    float scale_fac = gen_rand_float(3.0) + 0.1;
    mass = 2.0 * scale_fac;
    scale[X] = scale_fac;
    scale[Y] = scale_fac;
    scale[Z] = scale_fac;
    size_t location = init_space_obstacle(TYPE_ASTEROID, pos, vel,
                                          ang_vel, scale, mass);
    space_obstacle_insert_sim(location);
  }
}

void spawn_space_debris() {
  /* TODO: implement space debris */
}

void clear_space_mode() {
  // Deallocate all simulations
  free_sim(physics_sim);
  free_sim(combat_sim);
  free_sim(render_sim);
  free_sim(event_sim);
  clear_dead_zones();

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
  free_space_obstacle_buffer();

  // Reset wrapper buffer length
  num_wrappers = 0;
}

// ============================== STATION MODE ===============================

int init_station_mode() {
  /* Turn off the coordinates */
  disable_coordinates();

  // Initialize proper render distances
  RENDER_DIST = ST_BASE_RENDER_DIST;
  glm_vec3_copy((vec3) {RENDER_DIST, RENDER_DIST, RENDER_DIST },
                render_sphere->scale);
  SIM_DIST = ST_BASE_SIM_DIST;
  glm_vec3_copy((vec3) {SIM_DIST, SIM_DIST, SIM_DIST }, sim_sphere->scale);
  update_perspective();

  // Initialize simulations
  physics_sim = init_sim(STATION_SIZE, STATION_DEPTH);
  sim_add_force(physics_sim, (vec3) { 0.0, -GRAVITY, 0.0 });
  combat_sim = init_sim(STATION_SIZE, STATION_DEPTH);
  render_sim = init_sim(STATION_SIZE, STATION_DEPTH);
  event_sim = init_sim(STATION_SIZE, STATION_DEPTH);

  int status = insert_dead_zones();
  if (status) {
    return -1;
  }

  // Initialize player entity values
  reset_physics(st_player.ent);
  glm_vec3_copy((vec3) { 2.5, 5.0, 2.5 }, st_player.ent->translation);
  glm_vec3_copy(st_player.ent->translation, camera.pos);

  // Place player entity in simulation
  status = player_insert_sim();
  if (status) {
    return -1;
  }

  // Place station entities in simulations
  status = init_enemy_buffer();
  if (status) {
    return -1;
  }

  // Place render and simulation distance sphere in simulations
  sim_add_entity(render_sim, render_sphere, ALLOW_DEFAULT);
  sim_add_entity(render_sim, sim_sphere, ALLOW_DEFAULT);

  status = init_station_obstacle_buffer();
  if (status) {
    return -1;
  }

  status = init_corridor_buffer();
  if (status) {
    return -1;
  }
  create_station_corridors();

  mode = STATION;
  return 0;
}

void clear_station_mode() {
  // Deallocate all simulations
  free_sim(physics_sim);
  free_sim(combat_sim);
  free_sim(render_sim);
  free_sim(event_sim);
  clear_dead_zones();

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
  for (size_t i = 0; i < num_corridors; i++) {
    free_entity(cd_obs[i].ent);
  }
  num_enemies = 0;
  num_projectiles = 0;
  num_items = 0;
  num_obstacles = 0;
  num_corridors = 0;

  free_enemy_buffer();
  free_corridor_buffer();
  free_station_obstacle_buffer();

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
        delete_enemy(i);
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
        space_obstacle_remove_sim(i);
        delete_space_obstacle(i);
        i--;
      }
    } else {
      cur_wrapper = object_wrappers + st_obs[i].wrapper_offset;
      if (cur_wrapper->to_delete) {
        // Delete obstacle
        station_obstacle_remove_sim(i);
        delete_station_obstacle(i);
        i--;
      }
    }
  }
  for (size_t i = 0; i < num_corridors; i++) {
    cur_wrapper = object_wrappers + cd_obs[i].wrapper_offset;
    if (cur_wrapper->to_delete) {
      corridor_remove_sim(i);
      delete_corridor(i);
      i--;
    }
  }

  return 0;
}

void refresh_objects() {
  for (size_t i = 0; i < num_wrappers; i++) {
    if (object_wrappers[i].to_refresh) {
      refresh_wrapper(i);
      object_wrappers[i].to_refresh = 0;
    }
  }
}

void switch_game_modes() {
  if (mode == SPACE) {
    clear_space_mode();
    init_station_mode();
  } else {
    clear_station_mode();
    init_space_mode();
  }
}

// ============================= GENERAL HELPERS =============================

int insert_dead_zones() {
  float max_extent = 0.0;
  if (mode == SPACE) {
    max_extent = SPACE_SIZE;
  } else {
    max_extent = STATION_SIZE;
  }

  mat3 rot_mats[6] = {
    GLM_MAT3_IDENTITY_INIT,
    { { -1.0, 0.0, 0.0}, { 0.0, -1.0, 0.0 }, { 0.0, 0.0, 1.0 } },
    { { 0.0, 1.0, 0.0}, { -1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } },
    { { 0.0, -1.0, 0.0}, { 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } },
    { { 1.0, 0.0, 0.0}, { 0.0, 0.0, 1.0 }, { 0.0, -1.0, 0.0 } },
    { { 1.0, 0.0, 0.0}, { 0.0, 0.0, -1.0 }, { 0.0, 1.0, 0.0 } },
  };

  vec3 scales[6] = {
    { max_extent * 3.0, max_extent, max_extent * 3.0 },
    { max_extent * 3.0, max_extent, max_extent * 3.0 },
    { max_extent, max_extent, max_extent * 3.0 },
    { max_extent, max_extent, max_extent * 3.0 },
    { max_extent, max_extent, max_extent },
    { max_extent, max_extent, max_extent }
  };

  int status = 0;
  for (int i = 0; i < 6; i++) {
    dead_zones[i] = init_dead_zone_ent();
    init_wrapper(DEAD_ZONE_OBJ, dead_zones[i], NULL);

    if (i == TOP) {
      glm_vec3_copy((vec3) { 0.0, max_extent, 0.0 },
                    dead_zones[TOP]->translation);
    } else if (i == BOTTOM) {
      glm_vec3_copy((vec3) { 0.0, -max_extent, 0.0 },
                    dead_zones[BOTTOM]->translation);
    } else if (i == LEFT) {
      glm_vec3_copy((vec3) { -max_extent, 0.0, 0.0 },
                    dead_zones[LEFT]->translation);
    } else if (i == RIGHT) {
      glm_vec3_copy((vec3) { max_extent, 0.0, 0.0 },
                    dead_zones[RIGHT]->translation);
    } else if (i == FORWARD) {
      glm_vec3_copy((vec3) { 0.0, 0.0, max_extent },
                    dead_zones[FORWARD]->translation);
    } else if (i == BACK) {
      glm_vec3_copy((vec3) { 0.0, 0.0, -max_extent },
                    dead_zones[BACK]->translation);
    }
    glm_mat3_quat(rot_mats[i], dead_zones[i]->rotation);
    glm_vec3_copy(scales[i], dead_zones[i]->scale);

    status = sim_add_entity(event_sim, dead_zones[i], ALLOW_DEFAULT);
    if (status) {
      return -1;
    }

    status = sim_add_entity(render_sim, dead_zones[i], ALLOW_DEFAULT);
    if (status) {
      return -1;
    }
  }

  return 0;
}

void clear_dead_zones() {
  for (int i = 0; i < 6; i++) {
    delete_wrapper((size_t) dead_zones[i]->data);
    free_entity(dead_zones[i]);
  }
}
