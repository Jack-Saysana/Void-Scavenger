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
  mode = SPACE;
  set_st_waypoint_enabled(1);
  reset_dmg_ui_state();
  reset_camera(&camera);
  /* Ensure coordinates are enabled */
  enable_coordinates();

  /* Re-enable shooting (if not already) */
  enable_shooting();

  /*Enemy can shoot on */

  // Initialize proper render distances
  RENDER_DIST = SP_BASE_RENDER_DIST;
  glm_vec3_copy((vec3) { RENDER_DIST, RENDER_DIST, RENDER_DIST },
                render_sphere->scale);
  SIM_DIST = SP_BASE_SIM_DIST;
  glm_vec3_copy((vec3) { SIM_DIST, SIM_DIST, SIM_DIST }, sim_sphere->scale);
  update_perspective();

  // Initialize simulations
  physics_sim = init_sim(space_size, SPACE_DEPTH);
  combat_sim = init_sim(space_size, SPACE_DEPTH);
  render_sim = init_sim(space_size, SPACE_DEPTH);
  event_sim = init_sim(space_size, SPACE_DEPTH);

  int status = insert_dead_zones();
  if (status) {
    return -1;
  }

  status = insert_sp_station();
  if (status) {
    return -1;
  }

  // Initialize ship entity values
  reset_physics(player_ship.ent);
  player_ship.wrapper_offset = init_wrapper(PLAYER_SHIP_OBJ, player_ship.ent,
                                            (void *) &player_ship);
  player_ship.cur_speed = 0.0;

  // Place player ship entity into simulations
  status = player_ship_insert_sim();

  // Initialize and place space entities into simulation
  status = init_enemy_ship_buffer();
  if (status) {
    return -1;
  }

  srand(glfwGetTime());
  vec3 pos = GLM_VEC3_ZERO_INIT;
  versor rot = GLM_QUAT_IDENTITY_INIT;
  int num_enemies = BASE_NUM_ENEMIES + (rand() % 5) - 2; //TODO update amount of enemeies based on level
  //int num_enemies = 1; //TODO update amount of enemeies based on level
  int e_attack_type_range = 0;
  int e_mov_type_range = 0;
  if (st_player.total_levels_completed > E_TYPE_UPDATE_2) {
    e_attack_type_range = 6;
    e_mov_type_range = 3;
  } else if (st_player.total_levels_completed > E_TYPE_UPDATE_1) {
    e_attack_type_range = 4;
    e_mov_type_range = 2;
  } else if (st_player.total_levels_completed > E_TYPE_UPDATE_0) {
    e_attack_type_range = 2;
    e_mov_type_range = 1;
  }
  int attack_types_picked[E_BASE_NUM_TYPES];
  int mov_types_picked[E_BASE_NUM_TYPES];
  for (int i = 0; i < E_BASE_NUM_TYPES; i++) {
    attack_types_picked[i] = gen_rand_int(e_attack_type_range + 1);
    mov_types_picked[i] = gen_rand_int(e_mov_type_range + 1);
    printf("\nPicked Attack_type %d, Mov Type %d\n", attack_types_picked[i], mov_types_picked[i]);
  }
  if (num_enemies > 0) {
    for (int i = 0; i < num_enemies; i++) {
      gen_rand_vec3(&pos, 2.0 * space_size);
      pos[X] -= space_size;
      pos[Y] -= space_size;
      pos[Z] -= space_size;

      gen_rand_vec4(&rot, 1.0);
      glm_quat_normalize(rot);
      int attack_picker = gen_rand_int(E_BASE_NUM_TYPES);
      int mov_picker = gen_rand_int(E_BASE_NUM_TYPES);
      spawn_sp_enemy(pos, rot, attack_types_picked[attack_picker], mov_types_picked[mov_picker]);
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
    gen_rand_vec3_plus_minus(&pos, space_size);
    gen_rand_vec3_plus_minus(&vel, 5.0);
    gen_rand_vec3_plus_minus(&ang_vel, 1.5);
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
  clear_sp_station();

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
  mode = STATION;
  reset_camera(&camera);
  set_st_waypoint_enabled(0);
  reset_dmg_ui_state();
  /* Turn off the coordinates */
  disable_coordinates();

  /* Re-enable shooting (if not already) */
  enable_shooting();

  /* Clear inventory */
  // reset_inventory();

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
  st_player.wrapper_offset = init_wrapper(PLAYER_OBJ, st_player.ent,
                                          (void *) &st_player);
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

  status = init_items_buffer();
  if (status) {
    return -1;
  }

  status = init_corridor_buffer();
  if (status) {
    return -1;
  }
  create_station_corridors();

  // Place player entity in simulation
  status = player_insert_sim();
  if (status) {
    return -1;
  }

  return 0;
}

void clear_station_mode() {
  // Deallocate all simulations
  free_sim(physics_sim);
  free_sim(combat_sim);
  free_sim(render_sim);
  free_sim(event_sim);
  clear_dead_zones();
  clear_st_terminal();

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
  free_items_buffer();

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
  if (mode == STATION) {
    for (size_t i = 0; i < num_items; i++) {
      cur_wrapper = object_wrappers + items[i].wrapper_offset;
      if (cur_wrapper->to_delete) {
        // Delete item
        item_remove_sim(i);
        delete_item(i);
        i--;
      }
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

void refresh_sim_distances() {
  glm_vec3_copy((vec3) {RENDER_DIST, RENDER_DIST, RENDER_DIST },
                render_sphere->scale);
  glm_vec3_copy((vec3) {SIM_DIST, SIM_DIST, SIM_DIST }, sim_sphere->scale);
  update_perspective();

  sim_remove_entity(render_sim, render_sphere);
  sim_remove_entity(render_sim, sim_sphere);
  sim_add_entity(render_sim, render_sphere, ALLOW_DEFAULT);
  sim_add_entity(render_sim, sim_sphere, ALLOW_DEFAULT);
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
    max_extent = space_size;
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

int insert_sp_station() {
  sp_station = init_station_ent();
  init_wrapper(STATION_OBJ, sp_station, NULL);

  gen_rand_vec3(&sp_station->translation, 2.0 * (space_size - 100.0));
  glm_vec3_sub(sp_station->translation, (vec3) { space_size - 100.0,
               space_size - 100.0, space_size - 100.0 },
               sp_station->translation);
  for (int i = 0; i < 3; i++) {
    if (sp_station->translation[i] > 0.0) {
      sp_station->translation[i] += 50.0;
    } else {
      sp_station->translation[i] -= 50.0;
    }
  }
  fprintf(stderr, "Station location: (%f, %f, %f)\n",
          sp_station->translation[X], sp_station->translation[Y],
          sp_station->translation[Z]);

  int status = sim_add_entity(physics_sim, sp_station, ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(combat_sim, sp_station, ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(event_sim, sp_station, ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, sp_station, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  return 0;
}

void clear_sp_station() {
  delete_wrapper((size_t) sp_station->data);
  free_entity(sp_station);
}

int spawn_st_terminal(vec3 position, versor rotation) {
  st_terminal = init_terminal_ent();
  init_wrapper(TERMINAL_OBJ, st_terminal, NULL);

  st_terminal->type |= T_IMMUTABLE;
  glm_vec3_copy(position, st_terminal->translation);
  glm_quat_copy(rotation, st_terminal->rotation);

  int status = sim_add_entity(physics_sim, st_terminal, ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(combat_sim, st_terminal, ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(event_sim, st_terminal, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, st_terminal, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  return 0;
}

void clear_st_terminal() {
  delete_wrapper((size_t) st_terminal->data);
  free_entity(st_terminal);
}

ENTITY **get_dead_zones() {
  if (mode == SPACE) {
    return dead_zones;
  }
  return NULL;
}

void get_sp_station_pos(vec3 dest) {
  glm_vec3_copy(sp_station->translation, dest);
}
