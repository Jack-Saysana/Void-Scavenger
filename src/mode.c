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

  // Place player ship entity into simulations
  int status = player_ship_insert_sim();

  // Initialize and place space entity in simulation
  status = init_enemy_ship_buffer();
  if (status) {
    return -1;
  }

  status = init_space_obstacle_buffer();
  if (status) {
    return -1;
  }

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
    gen_rand_vec3(&ang_vel, 0.5);
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

  // Place render distance sphere in simulations
  sim_add_entity(render_sim, render_sphere, ALLOW_DEFAULT);

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

/*

Legend:
 * = Walkable
 X = Non-walkable
  
 Note: Diagrams are draw in the layout
 to which they are imported. Therefore,
 the way they are laid out in the game is
 based on this orientation.

  4-Way:
  |-----|
  |  *  |
  |* * *|
  |  *  |
  |-----|

  1-Way:
  |-----|
  |  *  |
  |X * X|
  |  X  |
  |-----|

  T-Junction:
  |-----|
  |  *  |
  |X * *|
  |  *  |
  |-----|

  Corridor:
  |-----|
  |  *  |
  |X * X|
  |  *  |
  |-----|

  Corner:
  |-----|
  |  *  |
  |X * *|
  |  X  |
  |-----|

*/
void create_station_corridors() {
  int **maze = gen_maze();
  /* Analyze the odd numbered indices to find corridor type */
  /* x = movement in OpenGL X-axis along maze */
  /* z = movement in OpenGL Z-axis along maze */
  /* x_pos = current position on X-axis */
  /* z_pos = current position on Z-axis */
  int up = 0;
  int down = 0;
  int left = 0;
  int right = 0;
  int type = -1; 
  int rotation = 0;
  for (int x = 1; x < maze_size - 1; x++) {
    for (int z = 1; z < maze_size - 1; z++) {
      /* Check above, below, left, and right */
      /* Outputs of macros are stored in up, down, left, and right */
      /* if up, down, left, or right == UP, output is 1, otherwise 0 */
      if (!maze[x][z]) {
        CHECK_UP(maze, x, z, up)
        CHECK_DOWN(maze, x, z, down)
        CHECK_LEFT(maze, x, z, left)
        CHECK_RIGHT(maze, x, z, right)
        if (up & down & left & right) {
          type = TYPE_FOUR_WAY;
          rotation = 0;
        } else if (up & ~down & ~left & ~right) {
          type = TYPE_ONE_WAY;
          rotation = 0;
        } else if (~up & down & ~left & ~right) {
          type = TYPE_ONE_WAY;
          rotation = 180;
        } else if (~up & ~down & left & ~right) {
          type = TYPE_ONE_WAY;
          rotation = 90;
        } else if (~up & ~down & ~left & right) {
          type = TYPE_ONE_WAY;
          rotation = 270;
        } else if (up & down & left & ~right) {
          type = TYPE_T_JUNCT;
          rotation = 180;
        } else if (~up & down & left & right) {
          type = TYPE_T_JUNCT;
          rotation = 270;
        } else if (up & down & ~left & right) {
          type = TYPE_T_JUNCT;
          rotation = 0;
        } else if (up & ~down & left & right) {
          type = TYPE_T_JUNCT;
          rotation = 90;
        } else if (up & down & ~left & ~right) {
          type = TYPE_CORRIDOR;
          rotation = 0;
        } else if (~up & ~down & left & right) {
          type = TYPE_CORRIDOR;
          rotation = 90;
        } else if (~up & down & left & ~right) {
          type = TYPE_CORNER;
          rotation = 180;
        } else if (~up & down & ~left & right) {
          type = TYPE_CORNER;
          rotation = 270;
        } else if (up & ~down & ~left & right) {
          type = TYPE_CORNER;
          rotation = 0;
        } else if (up & ~down & left & ~right) {
          type = TYPE_CORNER;
          rotation = 90;
        } else {
          fprintf(stderr, "Could not find a matching corridor layout for (%d, %d)!\n", x, z);
          continue;
        }
        versor rot;
        if (rotation == 90) {
          glm_quat_identity(rot);
        } else if (rotation == 180) {
          glm_quat_init(rot, 0.0, 1 / sqrt(2), 0.0, 1 / sqrt(2)); 
        } else if (rotation == 270) {
          glm_quat_init(rot, 0.0, 1.0, 0.0, 0.0);
        } else if (rotation == 0) {
          glm_quat_init(rot, 0.0, 1 / sqrt(2), 0.0, -1 / sqrt(2)); 
        }

        vec3 position = GLM_VEC3_ZERO_INIT;
        glm_vec3_copy((vec3) { ((float) x) * 5.0, 0.0,((float) z) * 5.0 }, position);       
        size_t index = init_corridor(position, rot, type); 
        corridor_insert_sim(index);
      }
    }
  }
  free_maze(maze);
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

void switch_game_modes() {
  if (mode == SPACE) {
    clear_space_mode();
    init_station_mode();
  } else {
    clear_station_mode();
    init_space_mode();
  }
}
