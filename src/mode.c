#include <mode.h>

/*                                   MODE.C

  Implements the functionaility behind switching between station and space
  mode. This implies clearing and repopulating the simulation as well as
  reseting game state between levels.

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
  for (int i = 0; i < NUM_ASTEROIDS; i++) {
    gen_rand_vec3(&pos, 10.0);  
    gen_rand_vec3(&vel, 5.0);
    gen_rand_vec3(&ang_vel, 0.5);
    gen_rand_vec3(&scale, 3.0);
    size_t location = init_space_obstacle(TYPE_ASTEROID, pos, vel,
                                          ang_vel, scale);    
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

  // Reset wrapper buffer length
  num_wrappers = 0;
}

// ============================== STATION MODE ===============================

int init_station_mode() {
  // Initialize simulations
  physics_sim = init_sim(STATION_SIZE, STATION_DEPTH);
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
  status = init_station_obstacle_buffer();
  if (status) {
    return -1;
  }

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
