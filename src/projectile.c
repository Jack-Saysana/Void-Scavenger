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
  projectiles = NULL;
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
  if (type == T_MELEE) {
    projectile->ent->scale[X] = 5.0;
    projectile->ent->scale[Y] = 2.0;
    projectile->ent->scale[Z] = 5.0;
  } else {
    vec3 scaler = {1.0,1.0,1.0};
    glm_vec3_scale_as(scaler,player_ship.weapon.bullet_size,scaler);
    glm_vec3_copy(scaler, projectile->ent->scale);
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
  projectile->damage = damage;
  projectile->collision = 0;

  num_projectiles++;
  if (num_projectiles == proj_buff_len) {
    int status = double_buffer((void **) &projectiles, &proj_buff_len,
                               sizeof(PROJ));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate projectile buffer\n");
      return INVALID_INDEX;
    }
  }

  // Audio
  if (mode == STATION) {
    if (source == SRC_PLAYER) {
      play_audio(STATION_MODE_WEAPON_WAV);
    }
  } else {
    if (source == SRC_PLAYER) {
      if (type == BALLISTIC) {
        play_audio(BALLISTIC_GUN_WAV);
      } else if (type == LASER) {
        play_audio(LASER_GUN_WAV);
      } else if (type == PLASMA) {
        play_audio(PLASMA_GUN_WAV);
      }
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
  update_timer_args(proj_collision_anim, (void *) num_projectiles,
                    (void *) index);
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

void sim_refresh_proj(size_t index) {
  PROJ *proj = projectiles + index;
  COLLIDER *cur_col = NULL;
  for (size_t i = 0; i < proj->ent->model->num_colliders; i++) {
    cur_col = proj->ent->model->colliders + i;
    if (cur_col->category == HIT_BOX) {
      refresh_collider(render_sim, proj->ent, i);
      refresh_collider(combat_sim, proj->ent, i);
    }
  }
}

// ============================= GENERAL HELPERS =============================

void integrate_projectiles() {
  for (size_t i = 0; i < num_projectiles; i++) {
    integrate_projectile(i);
  }
}

void integrate_projectile(size_t index) {
  vec3 movement = GLM_VEC3_ZERO_INIT;
  vec3 pos = GLM_VEC3_ZERO_INIT;
  PROJ *cur_proj = projectiles + index;
  glm_vec3_copy(cur_proj->ent->translation, pos);
  glm_vec3_scale(cur_proj->ent->velocity, DELTA_TIME, movement);
  glm_vec3_add(movement, cur_proj->ent->translation,
               cur_proj->ent->translation);

  cur_proj->range -= glm_vec3_distance(pos, cur_proj->ent->translation);
  glm_vec3_copy(cur_proj->ent->translation, pos);
  // Delete projectile if it exausts its range or exists space bounds
  if (cur_proj->range <= 0.0 ||
      pos[X] < -space_size || pos[X] > space_size ||
      pos[Y] < -space_size || pos[Y] > space_size ||
      pos[Z] < -space_size || pos[Z] > space_size) {
    object_wrappers[cur_proj->wrapper_offset].to_delete = 1;
  }
}

void start_proj_collision_anim(size_t index) {
  glm_vec3_zero(projectiles[index].ent->velocity);
  projectiles[index].collision = 1;
  add_timer(0.016, proj_collision_anim, -1000, (void *) index);
  if (mode == SPACE) {
    glm_vec3_copy((vec3) { 1.0, 1.0, 1.0 }, projectiles[index].ent->scale);
  } else {
    glm_vec3_copy((vec3) { 0.25, 0.25, 0.25 }, projectiles[index].ent->scale);
  }
}

void proj_collision_anim(void *arg) {
  PROJ *proj = projectiles + (size_t) arg;
  if (proj->ent == NULL) {
    return;
  }

  vec3 scale_inc = { 0.01, 0.01, 0.01 };
  glm_vec3_add(proj->ent->scale, scale_inc, proj->ent->scale);
  if ((mode == SPACE && proj->ent->scale[X] >= 1.5) ||
      (mode == STATION && proj->ent->scale[X] >= 0.3)) {
    object_wrappers[(size_t) proj->wrapper_offset].to_delete = 1;
  } else {
    add_timer(0.016, proj_collision_anim, -1000, arg);
  }
}
