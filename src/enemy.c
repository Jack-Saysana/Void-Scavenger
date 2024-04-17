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
  new_enemy->cur_corridor = INVALID_INDEX;
  glm_vec3_zero(new_enemy->nearby_enemies);

  if (index == BRUTE) {
    new_enemy->max_health = E_BASE_HEALTH_BRUTE;
    new_enemy->cur_health = E_BASE_HEALTH_BRUTE;
    new_enemy->cur_speed = E_BASE_SPEED_BRUTE;
    new_enemy->fire_rate = E_BASE_FIRERATE_BRUTE;
    new_enemy->amount_xp = E_BRUTE_XP;
  } else {
    new_enemy->max_health = E_BASE_HEALTH_NORMAL;
    new_enemy->cur_health = E_BASE_HEALTH_NORMAL;
    new_enemy->cur_speed = E_BASE_SPEED_NORMAL;
    new_enemy->fire_rate = E_BASE_FIRERATE_NORMAL;
    new_enemy->amount_xp = E_BASE_XP;
  }
  if (gen_rand_int(2)) {
    new_enemy->weapon_type = MELEE;
    new_enemy->fire_rate = E_BASE_FIRERATE_MELEE;
  } else {
    new_enemy->weapon_type = RANGED;
  }
  new_enemy->invuln = 0;
  new_enemy->can_shoot = 1;
  new_enemy->cur_frame = INVALID_FRAME;
  new_enemy->dropped_xp = 0;

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
  update_timer_memory(&st_enemies[index].can_shoot, NULL);
  update_timer_args(st_enemy_walk_cycle, (void *) index,
                    (void *) INVALID_INDEX);
  update_timer_args(st_enemy_hurt_anim, (void *) index,
                    (void *) INVALID_INDEX);
  update_timer_args(st_enemy_shoot_anim, (void *) index,
                    (void *) INVALID_INDEX);
  update_timer_args(st_enemy_swing_anim, (void *) index,
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
  update_timer_memory(&st_enemies[num_enemies].can_shoot,
                      &st_enemies[index].can_shoot);
  update_timer_args(st_enemy_walk_cycle, (void *) num_enemies,
                    (void *) index);
  update_timer_args(st_enemy_hurt_anim, (void *) num_enemies,
                    (void *) index);
  update_timer_args(st_enemy_shoot_anim, (void *) num_enemies,
                    (void *) index);
  update_timer_args(st_enemy_swing_anim, (void *) num_enemies,
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

size_t init_enemy_ship(int index, int mov_type) {
  if (sp_enemies == NULL) {
    fprintf(stderr, "Error: inserting into deallocated enemy buffer\n");
    return INVALID_INDEX;
  }
  if (index >= NUM_ALIEN_ATTACK_TYPES || mov_type >= NUM_ALIEN_MOV_TYPES) {
    fprintf(stderr, "error: invalid enemy type\n");
    return INVALID_INDEX;
  }

  SHIP *new_enemy = sp_enemies + num_enemies;
  memset(new_enemy, 0, sizeof(SHIP));
  if (index == STANDARD_BALLISTIC || index == STANDARD_LASER || index == STANDARD_PLASMA) {
    new_enemy->ent = init_alien_ship_ent(STANDARD_BALLISTIC);
  } else if (index == HEALTH_BALLISTIC || index == HEALTH_LASER) {
    new_enemy->ent = init_alien_ship_ent(HEALTH_BALLISTIC);
  } else {
    new_enemy->ent = init_alien_ship_ent(SHIELD_BALLISTIC);
  }
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

  if (index == STANDARD_BALLISTIC) {
    new_enemy->weapon.type = BALLISTIC;
    new_enemy->hull.max_health = S_BASE_HEALTH;
    new_enemy->shield.max_shield = S_BASE_SHIELD;
  } else if (index == HEALTH_BALLISTIC) {
    new_enemy->weapon.type = BALLISTIC;
    new_enemy->hull.max_health = S_E_HEALTH_TYPE_BASE_HEALTH;
    new_enemy->shield.max_shield = S_E_HEALTH_TYPE_BASE_SHIELD;
  } else if (index == SHIELD_BALLISTIC) {
    new_enemy->weapon.type = BALLISTIC;
    new_enemy->hull.max_health = S_E_SHIELD_TYPE_BASE_HEALTH;
    new_enemy->shield.max_shield = S_E_SHIELD_TYPE_BASE_SHIELD;
  } else if (index == STANDARD_PLASMA) {
    new_enemy->weapon.type = PLASMA;
    new_enemy->hull.max_health = S_BASE_HEALTH;
    new_enemy->shield.max_shield = S_BASE_SHIELD;
  } else if (index == STANDARD_LASER) {
    new_enemy->weapon.type = LASER;
    new_enemy->hull.max_health = S_BASE_HEALTH;
    new_enemy->shield.max_shield = S_BASE_SHIELD;
  } else if (index == HEALTH_LASER) {
    new_enemy->weapon.type = LASER;
    new_enemy->hull.max_health = S_E_HEALTH_TYPE_BASE_HEALTH;
    new_enemy->shield.max_shield = S_E_HEALTH_TYPE_BASE_SHIELD;
  } else if (index == SHIELD_PLASMA) {
    new_enemy->weapon.type = PLASMA;
    new_enemy->hull.max_health = S_E_SHIELD_TYPE_BASE_HEALTH;
    new_enemy->shield.max_shield = S_E_SHIELD_TYPE_BASE_SHIELD;
  }

  if (mov_type == E_LOW_SPEED) {
    new_enemy->thruster.max_vel = S_BASE_VEL;
    new_enemy->thruster.max_accel = S_BASE_ACCEL;
  } else if (mov_type == E_MID_SPEED) {
    new_enemy->thruster.max_vel = S_E_MID_SPEED_BASE_VEL;
    new_enemy->thruster.max_accel = S_E_MID_SPEED_BASE_ACCEL;
  } else if (mov_type == E_HIGH_SPEED) {
    new_enemy->thruster.max_vel = S_E_HIGH_SPEED_BASE_VEL;
    new_enemy->thruster.max_accel = S_E_HIGH_SPEED_BASE_ACCEL;
  } else if (mov_type == E_ULTRA_SPEED) {
    new_enemy->thruster.max_vel = S_E_ULTRA_SPEED_BASE_VEL;
    new_enemy->thruster.max_accel = S_E_ULTRA_SPEED_BASE_ACCEL;
  }

  new_enemy->reactor.max_output = S_BASE_PWR_OUTPUT;
  new_enemy->shield.recharge_rate = S_BASE_SHIELD_RECHARGE;
  new_enemy->shield.recharge_delay = S_BASE_SHIELD_DELAY;
  new_enemy->shield.power_draw = S_BASE_PWR_DRAW;
  new_enemy->weapon.damage = S_BASE_DAMAGE;
  new_enemy->weapon.fire_rate = S_BASE_FIRERATE;
  new_enemy->weapon.max_power_draw = S_BASE_PWR_DRAW;
  new_enemy->weapon.proj_speed = S_BASE_PROJ_SPEED;
  new_enemy->weapon.range = S_BASE_RANGE;
  new_enemy->wing.max_ang_vel = S_BASE_ANG_VEL;
  new_enemy->wing.max_ang_accel = S_BASE_ANG_ACCEL;
  new_enemy->thruster.max_power_draw = S_BASE_PWR_DRAW;

  new_enemy->cur_health = new_enemy->hull.max_health;
  new_enemy->cur_shield = new_enemy->shield.max_shield;
  new_enemy->recharging_shield = 0;
  new_enemy->invuln = 0;
  new_enemy->e_can_shoot = 1;

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
  update_timer_memory(&sp_enemies[index].e_can_shoot, NULL);
  update_timer_args(sp_enemy_shield_dmg, (void *) index,
                    (void *) INVALID_INDEX);
  update_timer_args(ship_shield_recharge_delay, (void *) index,
                    (void *) INVALID_INDEX);
  free_entity(sp_enemies[index].ent);
  delete_wrapper(sp_enemies[index].wrapper_offset);

  num_enemies--;
  if (index == num_enemies) {
    return;
  }

  sp_enemies[index] = sp_enemies[num_enemies];
  update_timer_memory(&sp_enemies[num_enemies].invuln,
                      &sp_enemies[index].invuln);
  update_timer_memory(&sp_enemies[num_enemies].e_can_shoot,
                      &sp_enemies[index].e_can_shoot);
  update_timer_args(sp_enemy_shield_dmg, (void *) num_enemies,
                    (void *) index);
  update_timer_args(ship_shield_recharge_delay, (void *) num_enemies,
                    (void *) index);
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

void spawn_sp_enemy(vec3 pos, versor rot, int type, int mov_type) {
  size_t index = init_enemy_ship(type, mov_type);
  glm_vec3_copy(pos, sp_enemies[index].ent->translation);
  glm_quat_copy(rot, sp_enemies[index].ent->rotation);
  sp_enemy_insert_sim(index);
}

// ================================ BEHAVIOR =================================

void enemy_behavior() {
  if (mode != SPACE && mode != STATION) {
    return;
  }

  COLLISION *sim_enemies = NULL;
  size_t sim_num = 0;
  if (mode == SPACE) {
    sim_num = sim_get_nearby(render_sim, &sim_enemies,
                             player_ship.ent->translation, SIM_DIST);
  } else if (mode == STATION) {
    sim_num = sim_get_nearby(render_sim, &sim_enemies,
                             st_player.ent->translation, SIM_DIST);
  }

  SOBJ *wrapper = NULL;
  for (size_t i = 0; i < sim_num; i++) {
    wrapper = object_wrappers + (size_t) sim_enemies[i].b_ent->data;
    if (mode == SPACE && wrapper->type == ENEMY_SHIP_OBJ) {
      recharge_ship_shield(sp_enemies + (size_t) wrapper->data);
      sp_enemy_pathfind((size_t) wrapper->data);
    } else if (mode == STATION && wrapper->type == ENEMY_OBJ) {
      st_enemy_pathfind((size_t) wrapper->data);
    }
  }
  free(sim_enemies);
}

// ================================= ANIMATION ===============================

void st_enemy_walk_cycle(void *args) {
  size_t index = (size_t) args;
  if (index == INVALID_INDEX) {
    return;
  }

  ST_ENEMY *enemy = st_enemies + index;
  if (enemy->invuln || glm_vec3_norm(enemy->ent->velocity) <= 0.01) {
    return;
  }

  size_t duration = 0;
  if (enemy->weapon_type == RANGED) {
    duration = enemy->ent->model->animations[E_ANIM_WALK_RANGED].duration;
    animate(enemy->ent, E_ANIM_WALK_RANGED, enemy->cur_frame);
  } else {
    duration = enemy->ent->model->animations[E_ANIM_WALK_MELEE].duration;
    animate(enemy->ent, E_ANIM_WALK_MELEE, enemy->cur_frame);
  }
  enemy->cur_frame = (enemy->cur_frame + 1) % duration;

  add_timer(0.016, st_enemy_walk_cycle, -1000, args);
}

void st_enemy_hurt_anim(void *args) {
  size_t index = (size_t) args;
  if (index == INVALID_INDEX) {
    return;
  }

  ST_ENEMY *enemy = st_enemies + index;
  size_t duration = 0;
  if (enemy->weapon_type == RANGED) {
    duration = enemy->ent->model->animations[E_ANIM_HURT_RANGED].duration;
    animate(enemy->ent, E_ANIM_HURT_RANGED, enemy->cur_frame);
  } else {
    duration = enemy->ent->model->animations[E_ANIM_HURT_MELEE].duration;
    animate(enemy->ent, E_ANIM_HURT_MELEE, enemy->cur_frame);
  }

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

void st_enemy_shoot_anim(void *args) {
  size_t index = (size_t) args;
  if (index == INVALID_INDEX) {
    return;
  }

  ST_ENEMY *enemy = st_enemies + index;
  size_t duration = 0;
  duration = enemy->ent->model->animations[E_ANIM_SHOOTING].duration;
  animate(enemy->ent, E_ANIM_SHOOTING, enemy->cur_frame);

  if (enemy->cur_frame < duration) {
    enemy->cur_frame++;
    add_timer(0.02, st_enemy_shoot_anim, -1000, args);
  } else {
    enemy->cur_frame = INVALID_FRAME;
  }
}

void st_enemy_swing_anim(void *args) {
  size_t index = (size_t) args;
  if (index == INVALID_INDEX) {
    return;
  }

  ST_ENEMY *enemy = st_enemies + index;
  size_t duration = 0;
  duration = enemy->ent->model->animations[E_ANIM_SWINGING].duration;
  animate(enemy->ent, E_ANIM_SWINGING, enemy->cur_frame);

  if (enemy->cur_frame < duration) {
    enemy->cur_frame++;
    add_timer(0.02, st_enemy_swing_anim, -1000, args);
  } else {
    enemy->cur_frame = INVALID_FRAME;
  }
}

void sp_enemy_shield_dmg(void *args) {
  size_t index = (size_t) args;
  if (index == INVALID_INDEX) {
    return;
  }

  SHIP *enemy = sp_enemies + index;
  if (enemy->render_shield < 1.0) {
    enemy->render_shield += 0.05;
    if (enemy->render_shield > 1.0) {
      enemy->render_shield = 1.0;
    }
    add_timer(0.03, sp_enemy_shield_dmg, -1000, args);
  } else {
    enemy->render_shield = 0.0;
  }
}

