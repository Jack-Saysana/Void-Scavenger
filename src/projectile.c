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
                       S_WEAPON_T type, float damage) {
  if (projectiles == NULL) {
    fprintf(stderr, "Error: Inserting into a deallocated projectile buffer\n");
    return INVALID_INDEX;
  }

  PROJ *projectile = projectiles + num_projectiles;
  projectile->ent = init_proj_ent();
  if (projectile->ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate projectile entity\n");
    return INVALID_INDEX;
  }

  projectile->wrapper_offset = init_wrapper(PROJ_OBJ, projectile->ent,
                                           (void *) num_projectiles);
  if (projectile->wrapper_offset == INVALID_INDEX) {
    return -1;
  }

  // TODO initialize projectile data

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
  delete_wrapper(projectiles[index].wrapper_offset);

  num_projectiles--;
  if (index == num_projectiles) {
    return;
  }

  projectiles[index] = projectiles[num_enemies];
  SOBJ *wrapper = object_wrappers + projectiles[index].wrapper_offset;
  wrapper->data = (void *) index;
}

int projectile_insert_sim(size_t index) {
  int status = sim_add_entity(combat_sim, projectiles[index].ent,
                              ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, projectiles[index].ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  return 0;
}

// ========================== COLLECTIVE OPERATIONS ==========================

void integrate_projectiles() {
  // TODO Integrate projectile velocity
}
