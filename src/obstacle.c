#include <obstacle.h>
/*                                OBSTACLE.C

  Handles the initialization of obstacle game objects. Also implements
  the integration and insertion of obstacles in simulations.

*/

// ==================== BUFFER INITIALIZATION AND CLEANUP ====================

/*
  Must only be called when the station mode obstacles
  buffer has been freed (uses the same variables)
*/
int init_space_obstacle_buffer() {
  sp_obs = malloc(sizeof(SP_OBSTACLE) * BUFF_STARTING_LEN);
  if (sp_obs == NULL) {
    fprintf(stderr, "Error: Unable to allocate obstacle buffer\n");
    return -1;
  }
  num_obstacles = 0;
  obs_buff_len = BUFF_STARTING_LEN;

  return 0;
}

/*
  Must only be called when the space mode obstacles
  buffer has been freed (uses the same variables)
*/
int init_station_obstacle_buffer() {
  st_obs = malloc(sizeof(ST_OBSTACLE) * BUFF_STARTING_LEN);
  if (st_obs == NULL) {
    fprintf(stderr, "Error: Unable to allocate obstacle buffer\n");
    return -1;
  }
  num_obstacles = 0;
  obs_buff_len = BUFF_STARTING_LEN;

  return 0;
}

void free_space_obstacle_buffer() {
  free(sp_obs);
}

void free_station_obstacle_buffer() {
  free(st_obs);
}

// ================== INDIVIDUAL INITIALIZATION AND CLEANUP ==================

size_t init_space_obstacle(vec3 pos, vec3 velocity, vec3 angular_vel) {
  if (sp_obs == NULL) {
    fprintf(stderr, "Error: Inserting into a deallocated obstacle buffer\n");
    return INVALID_INDEX;
  }

  SP_OBSTACLE *obstacle = sp_obs + num_obstacles;
  obstacle->ent = init_obstacle_ent();
  if (obstacle->ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate obstacle entity\n");
    return INVALID_INDEX;
  }

  obstacle->wrapper_offset = init_wrapper(OBSTACLE_OBJ, obstacle->ent,
                                           (void *) num_obstacles);
  if (obstacle->wrapper_offset == INVALID_INDEX) {
    return -1;
  }

  glm_vec3_copy(velocity, obstacle->ent->velocity);
  glm_vec3_copy(angular_vel, obstacle->ent->ang_velocity);
  glm_vec3_copy(pos, obstacle->ent->translation);

  num_obstacles++;
  if (num_obstacles == obs_buff_len) {
    int status = double_buffer((void **) &sp_obs, &obs_buff_len,
                               sizeof(SP_OBSTACLE));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate obstacle buffer\n");
      return INVALID_INDEX;
    }
  }

  return num_obstacles - 1;
}

size_t init_station_obstacle(vec3 pos) {
  if (st_obs == NULL) {
    fprintf(stderr, "Error: Inserting into a deallocated obstacle buffer\n");
    return INVALID_INDEX;
  }

  ST_OBSTACLE *obstacle = st_obs + num_obstacles;
  obstacle->ent = init_obstacle_ent();
  if (obstacle->ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate obstacle entity\n");
    return INVALID_INDEX;
  }

  obstacle->wrapper_offset = init_wrapper(OBSTACLE_OBJ, obstacle->ent,
                                           (void *) num_obstacles);
  if (obstacle->wrapper_offset == INVALID_INDEX) {
    return -1;
  }

  glm_vec3_copy((vec3) { 0.0, 0.0, 0.0 }, obstacle->ent->ang_velocity);
  glm_vec3_copy((vec3) { 0.0, 0.0, 0.0 }, obstacle->ent->velocity);
  glm_vec3_copy(pos, obstacle->ent->translation);

  num_obstacles++;
  if (num_obstacles == obs_buff_len) {
    int status = double_buffer((void **) &st_obs, &obs_buff_len,
                               sizeof(SP_OBSTACLE));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate obstacle buffer\n");
      return INVALID_INDEX;
    }
  }

  return num_obstacles - 1;
}

void delete_space_obstacle(size_t index) {
  if (index >= num_obstacles) {
    return;
  }

  free_entity(sp_obs[index].ent);
  delete_wrapper(sp_obs[index].wrapper_offset);

  num_obstacles--;
}

int space_obstacle_insert_sim(size_t index) {
  int status = sim_add_entity(physics_sim, sp_obs[index].ent,
                              ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, sp_obs[index].ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  return 0;
}

int station_obstacle_insert_sim(size_t index) {
  int status = sim_add_entity(physics_sim, st_obs[index].ent,
                              ALLOW_DEFAULT);
 
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, st_obs[index].ent,
                           ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  return 0;
}
