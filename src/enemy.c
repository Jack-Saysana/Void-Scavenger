#include <enemy.h>

/*                                 ENEMY.C

  Handles all common logic behind managing enemies in both station and space
  mode. This includes pathfinding, and spawning.

*/

// ==================== BUFFER INITIALIZATION AND CLEANUP ====================

int init_enemy_buffer() {
  st_enemies = malloc(sizeof(ST_ENEMY) * BUFF_STARTING_LEN);
  if (st_enemies == NULL) {
    fprintf(stderr, "Error: Unable to allocate station enemy buffer\n");
    return -1;
  }
  num_enemies = 0;
  enemy_buff_len = BUFF_STARTING_LEN;

  return 0;
}

void free_enemy_buffer() {
  free(st_enemies);
  st_enemies = NULL;
}

int init_enemy_ship_buffer() {
  sp_enemies = malloc(sizeof(SHIP) * BUFF_STARTING_LEN);
  if (sp_enemies == NULL) {
    fprintf(stderr, "Error: Unable to allocate space enemy buffer\n");
    return -1;
  }
  num_enemies = 0;
  enemy_buff_len = BUFF_STARTING_LEN;

  return 0;
}

void free_enemy_ship_buffer() {
  free(sp_enemies);
  sp_enemies = NULL;
}

// =============================== STATION MODE ==============================

size_t init_enemy(size_t index) {
  if (st_enemies == NULL) {
    fprintf(stderr, "Error: inserting into deallocated enemy buffer\n");
    return INVALID_INDEX;
  }
  if (index >= NUM_ALIEN_TYPES) {
    fprintf(stderr, "error: invalid enemy type\n");
    return INVALID_INDEX;
  }

  ST_ENEMY *new_enemy = st_enemies + num_enemies;
  new_enemy->ent = init_alien_ent(index);
  if (new_enemy->ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate enemy entity\n");
    return INVALID_INDEX;
  }
  new_enemy->ent->type |= T_DRIVING;
  new_enemy->ent->inv_mass = 1.0;

  new_enemy->wrapper_offset = init_wrapper(ENEMY_OBJ, new_enemy->ent,
                                           (void *) num_enemies);
  if (new_enemy->wrapper_offset == INVALID_INDEX) {
    return -1;
  }
  new_enemy->target_corridor = INVALID_INDEX;
  glm_vec3_zero(new_enemy->nearby_enemies);

  if (index == BRUTE) {
    new_enemy->max_health = E_BASE_HEALTH_BRUTE;
    new_enemy->cur_health = E_BASE_HEALTH_BRUTE;
    new_enemy->cur_speed = E_BASE_SPEED_BRUTE;
    new_enemy->fire_rate = E_BASE_FIRERATE_BRUTE;
    new_enemy->weapon_type = RANGED;
  } else {
    new_enemy->max_health = E_BASE_HEALTH_NORMAL;
    new_enemy->cur_health = E_BASE_HEALTH_NORMAL;
    new_enemy->cur_speed = E_BASE_SPEED_NORMAL;
    new_enemy->fire_rate = E_BASE_FIRERATE_NORMAL;
    new_enemy->weapon_type = RANGED;
  }
  new_enemy->invuln = 0;
  new_enemy->cur_frame = INVALID_FRAME;

  num_enemies++;
  if (num_enemies == enemy_buff_len) {
    int status = double_buffer((void **) &st_enemies, &enemy_buff_len,
                               sizeof(ST_ENEMY));
    if (status) {
      fprintf(stderr, "error: unable to reallocate enemy buffer\n");
      return -1;
    }
  }

  return num_enemies - 1;
}

void delete_enemy(size_t index) {
  if (index >= num_enemies) {
    return;
  }

  update_timer_memory(&st_enemies[index].invuln, NULL);
  update_timer_args(st_enemy_walk_cycle, (void *) index,
                    (void *) INVALID_INDEX);
  update_timer_args(st_enemy_hurt_anim, (void *) index,
                    (void *) INVALID_INDEX);
  free_entity(st_enemies[index].ent);
  delete_wrapper(st_enemies[index].wrapper_offset);

  num_enemies--;
  if (index == num_enemies) {
    return;
  }

  st_enemies[index] = st_enemies[num_enemies];
  update_timer_memory(&st_enemies[num_enemies].invuln,
                      &st_enemies[index].invuln);
  update_timer_args(st_enemy_walk_cycle, (void *) num_enemies,
                    (void *) index);
  update_timer_args(st_enemy_hurt_anim, (void *) num_enemies,
                    (void *) index);
  SOBJ *wrapper = object_wrappers + st_enemies[index].wrapper_offset;
  wrapper->data = (void *) index;
}

int st_enemy_insert_sim(size_t index) {
  int status = sim_add_entity(physics_sim, st_enemies[index].ent,
                              ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(combat_sim, st_enemies[index].ent,
                          ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, st_enemies[index].ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(event_sim, st_enemies[index].ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  return 0;
}

void st_enemy_remove_sim(size_t index) {
  sim_remove_entity(physics_sim, st_enemies[index].ent);
  sim_remove_entity(combat_sim, st_enemies[index].ent);
  sim_remove_entity(render_sim, st_enemies[index].ent);
  sim_remove_entity(event_sim, st_enemies[index].ent);
}

void sim_refresh_st_enemy(size_t index) {
  ST_ENEMY *enemy = st_enemies + index;
  COLLIDER *cur_col = NULL;
  for (size_t i = 0; i < enemy->ent->model->num_colliders; i++) {
    cur_col = enemy->ent->model->colliders + i;
    if (cur_col->category == DEFAULT) {
      refresh_collider(physics_sim, enemy->ent, i);
      refresh_collider(render_sim, enemy->ent, i);
      refresh_collider(event_sim, enemy->ent, i);
    } else if (cur_col->category == HURT_BOX) {
      refresh_collider(combat_sim, enemy->ent, i);
    }
  }
}

void spawn_st_enemy(vec3 pos, int type) {
  size_t index = init_enemy(type);
  glm_vec3_copy(pos, st_enemies[index].ent->translation);
  glm_vec3_copy((vec3) { 0.0, 0.01, 0.0 }, st_enemies[index].ent->velocity);
  st_enemy_insert_sim(index);
}

// =============================== SPACE MODE ================================

size_t init_enemy_ship(int index) {
  if (sp_enemies == NULL) {
    fprintf(stderr, "Error: inserting into deallocated enemy buffer\n");
    return INVALID_INDEX;
  }
  if (index >= NUM_ALIEN_SHIP_TYPES) {
    fprintf(stderr, "error: invalid enemy type\n");
    return INVALID_INDEX;
  }

  SHIP *new_enemy = sp_enemies + num_enemies;
  memset(new_enemy, 0, sizeof(SHIP));

  new_enemy->ent = init_alien_ship_ent(index);
  if (new_enemy->ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate enemy entity\n");
    return INVALID_INDEX;;
  }
  new_enemy->ent->type |= T_DRIVING;
  new_enemy->ent->inv_mass = 1.0;

  new_enemy->wrapper_offset = init_wrapper(ENEMY_SHIP_OBJ, new_enemy->ent,
                                           (void *) num_enemies);
  if (new_enemy->wrapper_offset == INVALID_INDEX) {
    return -1;
  }

  new_enemy->reactor.max_output = S_BASE_PWR_OUTPUT;
  new_enemy->hull.max_health = S_BASE_HEALTH;
  new_enemy->shield.max_shield = S_BASE_SHIELD;
  new_enemy->shield.recharge_rate = S_BASE_SHIELD_RECHARGE;
  new_enemy->shield.recharge_delay = S_BASE_SHIELD_DELAY;
  new_enemy->shield.power_draw = S_BASE_PWR_DRAW;
  new_enemy->weapon.type = BALLISTIC;
  new_enemy->weapon.damage = S_BASE_DAMAGE;
  new_enemy->weapon.fire_rate = S_BASE_FIRERATE;
  new_enemy->weapon.max_power_draw = S_BASE_PWR_DRAW;
  new_enemy->wing.max_ang_vel = S_BASE_ANG_VEL;
  new_enemy->wing.max_ang_accel = S_BASE_ANG_ACCEL;
  new_enemy->thruster.max_vel = S_BASE_VEL;
  new_enemy->thruster.max_accel = S_BASE_ACCEL;
  new_enemy->thruster.max_power_draw = S_BASE_PWR_DRAW;

  new_enemy->cur_health = new_enemy->hull.max_health;
  new_enemy->cur_shield = new_enemy->shield.max_shield;
  new_enemy->invuln = 0;

  num_enemies++;
  if (num_enemies == enemy_buff_len) {
    int status = double_buffer((void **) &sp_enemies, &enemy_buff_len,
                               sizeof(SHIP));
    if (status) {
      fprintf(stderr, "Error: unable to reallocate enemy buffer\n");
      return -1;
    }
  }

  return num_enemies - 1;
}

void delete_enemy_ship(size_t index) {
  if (index >= num_enemies) {
    return;
  }

  // Clear target UI If deleted enemy is currently targeted
  if (index == get_target_ship_index()) {
    set_target_ship_index(INVALID_INDEX);
  }

  update_timer_memory(&sp_enemies[index].invuln, NULL);
  free_entity(sp_enemies[index].ent);
  delete_wrapper(sp_enemies[index].wrapper_offset);

  num_enemies--;
  if (index == num_enemies) {
    return;
  }

  sp_enemies[index] = sp_enemies[num_enemies];
  update_timer_memory(&st_enemies[num_enemies].invuln,
                      &st_enemies[index].invuln);
  SOBJ *wrapper = object_wrappers + sp_enemies[index].wrapper_offset;
  wrapper->data = (void *) index;

  // Update target UI
  if (num_enemies == get_target_ship_index()) {
    set_target_ship_index(index);
  }
}

int sp_enemy_insert_sim(size_t index) {
  int status = sim_add_entity(physics_sim, sp_enemies[index].ent,
                              ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(combat_sim, sp_enemies[index].ent,
                          ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, sp_enemies[index].ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(event_sim, sp_enemies[index].ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  return 0;
}

void sp_enemy_remove_sim(size_t index) {
  sim_remove_entity(physics_sim, sp_enemies[index].ent);
  sim_remove_entity(combat_sim, sp_enemies[index].ent);
  sim_remove_entity(render_sim, sp_enemies[index].ent);
  sim_remove_entity(event_sim, sp_enemies[index].ent);
}

void sim_refresh_sp_enemy(size_t index) {
  SHIP *enemy = sp_enemies + index;
  COLLIDER *cur_col = NULL;
  for (size_t i = 0; i < enemy->ent->model->num_colliders; i++) {
    cur_col = enemy->ent->model->colliders + i;
    if (cur_col->category == DEFAULT) {
      refresh_collider(render_sim, enemy->ent, i);
      refresh_collider(event_sim, enemy->ent, i);
    } else if (cur_col->category == HURT_BOX) {
      refresh_collider(physics_sim, enemy->ent, i);
      refresh_collider(combat_sim, enemy->ent, i);
    }
  }
}

void spawn_sp_enemy(vec3 pos, versor rot, int type) {
  size_t index = init_enemy_ship(type);
  glm_vec3_copy(pos, sp_enemies[index].ent->translation);
  glm_quat_copy(rot, sp_enemies[index].ent->rotation);
  sp_enemy_insert_sim(index);
}

// ================================ BEHAVIOR =================================

void enemy_behavior() {
  for (size_t i = 0; i < num_enemies; i++) {
    if (mode == SPACE) {
      sp_enemy_pathfind(i);
    } else if (mode == STATION) {
      st_enemy_pathfind(i);
    }
  }
}

void sp_enemy_pathfind(size_t index) {
  SHIP *enemy = sp_enemies + index;
  vec3 e_pos = GLM_VEC3_ZERO_INIT;
  glm_vec3_copy(enemy->ent->translation, e_pos);

  vec3 forward = { -1.0, 0.0, 0.0 };
  glm_quat_rotatev(enemy->ent->rotation, forward, forward);
  vec3 up = { 0.0, 1.0, 0.0 };
  glm_quat_rotatev(enemy->ent->rotation, up, up);
  vec3 side = GLM_VEC3_ZERO_INIT;
  glm_vec3_cross(forward, up, side);
  glm_vec3_normalize(side);

  // TODO Actually calculate turning radius
  float turning_rad = 70.0;

  // Steer ship away from arena edges
  vec3 target_dir = { 0.0, 0.0, 0.0 };
  float target_speed = enemy->thruster.max_vel;
  if (e_pos[X] >= space_size - turning_rad) {
    target_dir[X] = (space_size - turning_rad) - e_pos[X];
  } else if (e_pos[X] <= turning_rad - space_size) {
    target_dir[X] = (turning_rad - space_size) - e_pos[X];
  }
  if (e_pos[Y] >= space_size - turning_rad) {
    target_dir[Y] = (space_size - turning_rad) - e_pos[Y];
  } else if (e_pos[Y] <= turning_rad - space_size) {
    target_dir[Y] = (turning_rad - space_size) - e_pos[Y];
  }
  if (e_pos[Z] >= space_size - turning_rad) {
    target_dir[Z] = (space_size - turning_rad) - e_pos[Z];
  } else if (e_pos[Z] <= turning_rad - space_size) {
    target_dir[Z] = (turning_rad - space_size) - e_pos[Z];
  }
  // Slow down ship as it approaches a collision
  float speed_modifier = glm_vec3_norm(target_dir);
  if (speed_modifier) {
    speed_modifier = 5.0 / fabs(speed_modifier);
    if (speed_modifier < 1.0) {
      target_speed *= speed_modifier;
    }
  }
  glm_vec3_normalize(target_dir);

  float alignment = glm_vec3_dot(target_dir, forward);
  if ((target_dir[X] || target_dir[Y] || target_dir[Z]) &&
       alignment < 0.9) {
    // Goal: Steer the ship using roll such that it's up, forward, and target
    // vector are co-planar, then steer using pitch such that it's forward
    // vector matches it's forward vector. This will create a "realistic"
    // looking turning style

    vec3 temp = GLM_VEC3_ZERO_INIT;
    // Three vectors a, b and c are coplanar if (a * (b x c)) == 0
    glm_vec3_cross(forward, up, temp);
    float rolling = glm_vec3_dot(target_dir, temp);
    enemy->cur_ang_speed = enemy->wing.max_ang_vel;
    if (rolling < -0.1 || rolling > 0.1) {
      // Steer using roll
      enemy->cur_ang_speed += enemy->wing.max_ang_accel * DELTA_TIME;
      if (enemy->cur_ang_speed > enemy->wing.max_ang_vel) {
        enemy->cur_ang_speed = enemy->wing.max_ang_vel;
      }

      glm_vec3_scale_as(forward, enemy->cur_ang_speed,
                        enemy->ent->ang_velocity);
    } else {
      // Steer using pitch
      enemy->cur_ang_speed += enemy->wing.max_ang_accel * DELTA_TIME;
      if (enemy->cur_ang_speed > enemy->wing.max_ang_vel) {
        enemy->cur_ang_speed = enemy->wing.max_ang_vel;
      }

      glm_vec3_cross(forward, target_dir, temp);
      glm_vec3_normalize(temp);
      if (glm_vec3_dot(temp, side) > 0.0) {
        glm_vec3_scale_as(side, enemy->cur_ang_speed,
                          enemy->ent->ang_velocity);
      } else {
        glm_vec3_scale_as(side, -enemy->cur_ang_speed,
                          enemy->ent->ang_velocity);
      }
    }
  } else {
    enemy->cur_ang_speed -= enemy->wing.max_ang_accel * DELTA_TIME;
    if (enemy->cur_ang_speed < 0.0) {
      enemy->cur_ang_speed = 0.0;
    }
    glm_vec3_scale_as(enemy->ent->ang_velocity, enemy->cur_ang_speed,
                      enemy->ent->ang_velocity);
  }

  if (enemy->cur_speed < target_speed) {
    enemy->cur_speed += enemy->thruster.max_accel * DELTA_TIME;
    if (enemy->cur_speed < 0.0) {
      enemy->cur_speed = 0.0;
    }
  } else if (enemy->cur_speed > target_speed) {
    enemy->cur_speed -= enemy->thruster.max_accel * DELTA_TIME;
    if (enemy->cur_speed > enemy->thruster.max_vel) {
      enemy->cur_speed = enemy->thruster.max_vel;
    }
  }
  glm_vec3_scale_as(forward, enemy->cur_speed, enemy->ent->velocity);
}

void st_enemy_pathfind(size_t index) {
  ST_ENEMY *enemy = st_enemies + index;
  if (enemy->invuln) {
    return;
  }
  vec3 forward = GLM_VEC3_ZERO_INIT;
  vec3 enemy_pos_2d = { enemy->ent->translation[X], 0.0,
                        enemy->ent->translation[Z] };
  vec3 nearby_enemies = GLM_VEC3_ZERO_INIT;
  glm_vec3_normalize_to(enemy->nearby_enemies, nearby_enemies);
  glm_vec3_zero(enemy->nearby_enemies);
  enemy->ent->velocity[X] = 0.0;
  enemy->ent->velocity[Z] = 0.0;
  glm_vec3_zero(enemy->ent->ang_velocity);
  if (enemy->target_corridor == INVALID_INDEX) {
    enemy->cur_frame = INVALID_FRAME;
    update_timer_args(st_enemy_walk_cycle, (void *) index,
                      (void *) INVALID_INDEX);
    return;
  }

  glm_quat_rotatev(enemy->ent->rotation, (vec3) { -1.0, 0.0, 0.0 }, forward);
  if (enemy->cur_frame == INVALID_FRAME) {
    enemy->cur_frame = 0;
    add_timer(0.016, st_enemy_walk_cycle, -1000, (void *) index);
  }

  // Calculate direction of targeted corridor
  CORRIDOR *cd = cd_obs + enemy->target_corridor;
  vec3 cd_pos_2d = { cd->ent->translation[X], 0.0, cd->ent->translation[Z] };
  float to_cd_center = glm_vec3_distance(enemy_pos_2d, cd_pos_2d);
  vec3 target_cd_dir = GLM_VEC3_ZERO_INIT;
  if (to_cd_center > 1.0) {
    glm_vec3_sub(cd_pos_2d, enemy_pos_2d, target_cd_dir);
  } else {
    // Search for new target corridor (in the future this will be some sort of
    // pathfinding algorithm)
    for (int i = 0; i < 4; i++) {
      if (cd->neighbors[i] != INVALID_INDEX) {
        enemy->target_corridor = cd->neighbors[i];
        break;
      }
    }
  }

  vec3 target_dir = GLM_VEC3_ZERO_INIT;
  glm_vec3_add(nearby_enemies, target_cd_dir, target_dir);
  glm_vec3_normalize(target_dir);

  float alignment = glm_vec3_dot(target_dir, forward);
  if (alignment >= 0.75) {
    glm_vec3_scale_as(forward, enemy->cur_speed, enemy->ent->velocity);
  }
  if (alignment < 0.9) {
    vec3 test_dir = GLM_VEC3_ZERO_INIT;
    glm_vec3_cross(forward, target_dir, test_dir);
    glm_vec3_normalize(test_dir);
    if (glm_vec3_dot(test_dir, (vec3) { 0.0, 1.0, 0.0 }) > 0.0) {
      glm_vec3_copy((vec3) { 0.0, 3.0, 0.0 }, enemy->ent->ang_velocity);
    } else {
      glm_vec3_copy((vec3) { 0.0, -3.0, 0.0 }, enemy->ent->ang_velocity);
    }
  }
}

// ================================= ANIMATION ===============================

void st_enemy_walk_cycle(void *args) {
  size_t index = (size_t) args;
  if (index == INVALID_INDEX) {
    return;
  }

  ST_ENEMY *enemy = st_enemies + index;
  if (enemy->invuln) {
    return;
  }
  size_t duration = enemy->ent->model->animations[E_ANIM_WALK].duration;
  animate(enemy->ent, E_ANIM_WALK, enemy->cur_frame);
  enemy->cur_frame = (enemy->cur_frame + 1) % duration;

  add_timer(0.016, st_enemy_walk_cycle, -1000, args);
}

void st_enemy_hurt_anim(void *args) {
  size_t index = (size_t) args;
  if (index == INVALID_INDEX) {
    return;
  }

  ST_ENEMY *enemy = st_enemies + index;
  size_t duration = enemy->ent->model->animations[E_ANIM_HURT].duration;
  animate(enemy->ent, E_ANIM_HURT, enemy->cur_frame);

  if (enemy->cur_frame < duration) {
    enemy->cur_frame++;
    add_timer(0.03, st_enemy_hurt_anim, -1000, args);
  } else {
    if (enemy->cur_health <= 0.0) {
      object_wrappers[enemy->wrapper_offset].to_delete = 1;;
    } else {
      enemy->cur_frame = INVALID_FRAME;
      enemy->invuln = 0;
    }
  }
}

