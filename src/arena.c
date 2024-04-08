#include <arena.h>

/*                              ARENA.C

    Handles the functionality behind adding in the arena into station mode
    and adding in the arena assets.

*/

// ==================== BUFFER INITIALIZATION AND CLEANUP ====================

int init_arena_buffer() {
  arena_obs = malloc(sizeof(ARENA) * BUFF_STARTING_LEN);
  if (arena_obs == NULL) {
    fprintf(stderr, "Error: Unable to allocate arena buffer\n");
    return -1;
  }
  num_arena = 0;
  arena_buff_len = BUFF_STARTING_LEN;

  return 0;
}

void free_arena_buffer() {
  free(arena_obs);
  arena_obs = NULL;
}

// ================== INDIVIDUAL INITIALIZATION AND CLEANUP ==================

size_t init_arena(vec3 pos, versor rotation, size_t type) {
  if (arena_obs == NULL) {
    fprintf(stderr, "Error: Inserting into a deallocated arena buffer\n");
    return INVALID_INDEX;
  }

  ARENA *arena = arena_obs + num_arena;
  arena->ent = init_arena_ent(type);
  if (arena->ent == NULL) {
    fprintf(stderr, "Error: Unable to alocate arena entity\n");
    return INVALID_INDEX;
  }
  arena->ent->type |= T_IMMUTABLE;

  arena->wrapper_offset = init_wrapper(ARENA_OBJ, arena->ent,
                                       (void *) num_arena);
  if (arena->wrapper_offset == INVALID_INDEX) {
    return INVALID_INDEX;
  }

  for (int i = 0; i < 4; i++) {
    arena->neighbors[i].index = INVALID_INDEX;
    arena->neighbors[i].type = -1;
  }

  /* Initialize arena entity data */
  glm_vec3_copy(pos, arena->ent->translation);
  glm_vec3_copy((vec3) GLM_VEC3_ZERO_INIT, arena->ent->ang_velocity);
  glm_vec3_copy((vec3) GLM_VEC3_ZERO_INIT, arena->ent->velocity);
  arena->ent->rotation[0] = rotation[0];
  arena->ent->rotation[1] = rotation[1];
  arena->ent->rotation[2] = rotation[2];
  arena->ent->rotation[3] = rotation[3];
  glm_vec3_copy((vec3) {1.0, 1.0, 1.0}, arena->ent->scale);

  if (++num_arena == arena_buff_len) {
    int status = double_buffer((void **) &arena_obs, &arena_buff_len,
                               sizeof(ARENA));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate arena buffer\n");
      return INVALID_INDEX;
    }
  }

  return num_arena - 1;
} 

void delete_arena(size_t index) {
  if (index >= num_arena) {
    return;
  }

  free_entity(arena_obs[index].ent);
  delete_wrapper(arena_obs[index].wrapper_offset);

  num_arena--;
}

int arena_insert_sim(size_t index) {
  if (sim_add_entity(physics_sim, arena_obs[index].ent, ALLOW_HURT_BOXES)) {
    return -1;
  }

  if (sim_add_entity(combat_sim, arena_obs[index].ent, ALLOW_HURT_BOXES)) {
    return -1;
  }

  if (sim_add_entity(render_sim, arena_obs[index].ent, ALLOW_DEFAULT)) {
    return -1;
  }

  if (sim_add_entity(event_sim, arena_obs[index].ent, ALLOW_DEFAULT)) {
    return -1;
  }
  return 0;
}

void sim_refresh_arena(size_t index) {
  ARENA *arena = arena_obs + index;
  COLLIDER *cur_col = NULL;
  for (size_t i = 0; i < arena->ent->model->num_colliders; i++) {
    cur_col = arena->ent->model->colliders + i;
    if (cur_col->category == DEFAULT) {
      refresh_collider(render_sim, arena->ent, i);
    } else if (cur_col->category == HURT_BOX) {
      refresh_collider(combat_sim, arena->ent, i);
    }
  }
}

void arena_remove_sim(size_t index) {
  sim_remove_entity(render_sim, arena_obs[index].ent);
  sim_remove_entity(combat_sim, arena_obs[index].ent);
  sim_remove_entity(physics_sim, arena_obs[index].ent);
  sim_remove_entity(event_sim, arena_obs[index].ent);
}

/* ================================= HELPERS =============================== */
void add_arena(int size, int **maze) {
  for (int i = 2; i < size + 2; i++) {
    for (int j = 2; j < size + 2; j++) {
      maze[i][j] = 9;
    }
  }
}
