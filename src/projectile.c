#include <projectile.h>

/*                                PROJECTILE.C

  Handles the initialization of projectile game objects. Also implements
  the integration and insertion of projectiles in simulations.

*/

// ==================== BUFFER INITIALIZATION AND CLEANUP ====================

int init_projectile_buffer() {
  projectiles = malloc(sizeof(PROJ) * BUFF_STARTING_LEN);
  if (projectiles == NULL) {
    fprintf(stderr, "Error: Unable to allocate projectile buffer\n");
    return -1;
  }
  num_projectiles = 0;
  proj_buff_len = BUFF_STARTING_LEN;

  return 0;
}

void free_projectile_buffer() {
  free(projectiles);
}

// ================== INDIVIDUAL INITIALIZATION AND CLEANUP ==================

size_t init_projectile(vec3 pos, vec3 dir, float speed, PROJ_SOURCE source,
                       S_WEAPON_T type, float damage, float range,
                       size_t index) {
  if (projectiles == NULL) {
    fprintf(stderr, "Error: Inserting into a deallocated projectile buffer\n");
    return INVALID_INDEX;
  }

  PROJ *projectile = projectiles + num_projectiles;
  projectile->ent = init_proj_ent(index);
  if (projectile->ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate projectile entity\n");
    return INVALID_INDEX;
  }

  projectile->wrapper_offset = init_wrapper(PROJ_OBJ, projectile->ent,
                                           (void *) num_projectiles);
  if (projectile->wrapper_offset == INVALID_INDEX) {
    return -1;
  }

  glm_vec3_copy(pos, projectile->ent->translation);
  glm_quat_from_vecs((vec3) { 0.0, 1.0, 0.0 }, dir, projectile->ent->rotation);
  glm_vec3_scale_as(dir, speed, projectile->ent->velocity);
  projectile->source = source;
  projectile->type = type;
  projectile->range = range;

  num_projectiles++;
  if (num_projectiles == proj_buff_len) {
    int status = double_buffer((void **) &projectiles, &proj_buff_len,
                               sizeof(PROJ));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate projectile buffer\n");
      return INVALID_INDEX;
    }
  }

  return num_projectiles - 1;
}

void delete_projectile(size_t index) {
  if (index >= num_projectiles) {
    return;
  }

  free_entity(projectiles[index].ent);
  projectiles[index].ent = NULL;
  delete_wrapper(projectiles[index].wrapper_offset);
  projectiles[index].wrapper_offset = INVALID_INDEX;

  num_projectiles--;
  if (index == num_projectiles) {
    return;
  }

  projectiles[index] = projectiles[num_projectiles];
  SOBJ *wrapper = object_wrappers + projectiles[index].wrapper_offset;
  wrapper->data = (void *) index;
}

int projectile_insert_sim(size_t index) {
  int status = sim_add_entity(combat_sim, projectiles[index].ent,
                              ALLOW_HIT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, projectiles[index].ent,
                          ALLOW_HIT_BOXES);
  if (status) {
    return -1;
  }

  return 0;
}

void projectile_remove_sim(size_t index) {
  sim_remove_entity(combat_sim, projectiles[index].ent);
  sim_remove_entity(render_sim, projectiles[index].ent);
}

// ========================== COLLECTIVE OPERATIONS ==========================

void integrate_projectiles() {
  vec3 movement = GLM_VEC3_ZERO_INIT;
  vec3 old_pos = GLM_VEC3_ZERO_INIT;
  PROJ *cur_proj = NULL;
  for (size_t i = 0; i < num_projectiles; i++) {
    cur_proj = projectiles + i;
    glm_vec3_copy(cur_proj->ent->translation, old_pos);
    glm_vec3_scale(cur_proj->ent->velocity, DELTA_TIME, movement);
    glm_vec3_add(movement, cur_proj->ent->translation,
                 cur_proj->ent->translation);

    cur_proj->range -= glm_vec3_distance(old_pos, cur_proj->ent->translation);
    if (cur_proj->range <= 0.0) {
      object_wrappers[cur_proj->wrapper_offset].to_delete = 1;
    }
  }
}
