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

  new_enemy->max_health = E_BASE_HEALTH;
  new_enemy->cur_health = E_BASE_HEALTH;
  new_enemy->speed = E_BASE_SPEED;
  new_enemy->fire_rate = E_BASE_FIRERATE;
  new_enemy->weapon_type = RANGED;
  new_enemy->invuln = 0;

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
  free_entity(st_enemies[index].ent);
  delete_wrapper(st_enemies[index].wrapper_offset);

  num_enemies--;
  if (index == num_enemies) {
    return;
  }

  st_enemies[index] = st_enemies[num_enemies];
  update_timer_memory(&st_enemies[num_enemies].invuln,
                      &st_enemies[index].invuln);
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

