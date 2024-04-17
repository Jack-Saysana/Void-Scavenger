#include <player.h>

/*                                  PLAYER.C

  Handles common logic behind manipulating and managing player data. This
  includes movement, inventory management and skill management

*/

// =============================== STATION MODE ==============================

// Initialize player struct at beginning of game
int init_player() {
  memset(&st_player, 0, sizeof(PLAYER));

  // TODO allocate player skills

  // Allocate player inventory
  st_player.inventory = (I_SLOT *) (malloc(sizeof(I_SLOT) * i_size));
  reset_inventory();

  st_player.ent = init_player_ent();
  if (st_player.ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate player entity\n");
    return -1;
  }
  st_player.ent->type |= T_DRIVING;
  st_player.ent->inv_mass = 1.0;
  st_player.wrapper_offset = INVALID_INDEX;

  st_player.max_health = P_BASE_HEALTH;
  st_player.cur_health = P_BASE_HEALTH;
  st_player.cur_level = 0;
  st_player.skill_points = 0;
  st_player.max_shield = P_BASE_SHIELD;
  st_player.speed = P_BASE_SPEED;
  st_player.jump = P_BASE_JUMP;
  st_player.fire_rate = P_BASE_FIRERATE;
  st_player.shield_recharge_rate = P_BASE_SHIELD_RECHARGE;
  st_player.shield_recharge_delay = P_BASE_SHIELD_DELAY;
  st_player.damage = P_BASE_DAMAGE;
  st_player.max_experience = P_BASE_MAX_EXP;
  st_player.invuln = 0;

  st_player.total_levels_completed = 0;
  st_player.total_enemies_defeated = 0;
  st_player.total_ships_defeated = 0;
  st_player.total_distance_flown = 0.0;
  st_player.total_distance_walked = 0.0;
  st_player.total_damage_dealt = 0.0;
  st_player.total_damage_taken = 0.0;
  st_player.total_experience = 0.0;

  return 0;
}

void reset_st_player_state() {
  st_player.cur_health = st_player.max_health;
  st_player.cur_shield = st_player.max_shield;
  st_player.invuln = 0;
  st_player.recharging_shield = 0;
}

void reset_inventory() {
  for (size_t i = 0; i < i_size; i++) {
    memset(&st_player.inventory[i], 0, sizeof(I_SLOT));
    st_player.inventory[i].type = I_SLOT_EMPTY;
  }
}

void reset_equipped_parts() {
  equipped_hull.data.hull = S_BASE_PART_HULL;
  equipped_hull.type = I_SLOT_HULL;
  equipped_hull.rarity = WHITE_RARITY;
  equipped_hull.weapon_type = NOT_WEAPON;

  equipped_reactor.data.reactor = S_BASE_PART_REACTOR;
  equipped_reactor.type = I_SLOT_REACTOR;
  equipped_reactor.rarity = WHITE_RARITY;
  equipped_reactor.weapon_type = NOT_WEAPON;

  equipped_shield.data.shield = S_BASE_PART_SHIELD;
  equipped_shield.type = I_SLOT_SHIELD;
  equipped_shield.rarity = WHITE_RARITY;
  equipped_shield.weapon_type = NOT_WEAPON;

  equipped_weapon.data.weapon = S_BASE_PART_WEAPON;
  equipped_weapon.type = I_SLOT_WEAPON;
  equipped_weapon.rarity = WHITE_RARITY;
  equipped_weapon.weapon_type = W_BALLISTIC;

  equipped_wing.data.wing = S_BASE_PART_WING;
  equipped_wing.type = I_SLOT_WING;
  equipped_wing.rarity = WHITE_RARITY;
  equipped_wing.weapon_type = NOT_WEAPON;

  equipped_thruster.data.thruster = S_BASE_PART_THRUSTER;
  equipped_thruster.type = I_SLOT_THRUSTER;
  equipped_thruster.rarity = WHITE_RARITY;
  equipped_thruster.weapon_type = NOT_WEAPON;
}

void reset_player() {
  st_player.max_health = P_BASE_HEALTH;
  st_player.cur_health = P_BASE_HEALTH;
  st_player.max_shield = P_BASE_SHIELD;
  st_player.speed = P_BASE_SPEED;
  st_player.jump = P_BASE_JUMP;
  st_player.fire_rate = P_BASE_FIRERATE;
  st_player.max_experience = P_BASE_MAX_EXP;
  st_player.invuln = 0;

  st_player.total_levels_completed = 0;
  st_player.total_enemies_defeated = 0;
  st_player.total_ships_defeated = 0;
  st_player.total_distance_flown = 0.0;
  st_player.total_distance_walked = 0.0;
  st_player.total_damage_dealt = 0.0;
  st_player.total_damage_taken = 0.0;
  st_player.total_experience = 0.0;

  player_ship.hull = S_BASE_PART_HULL;
  player_ship.reactor = S_BASE_PART_REACTOR;
  player_ship.shield = S_BASE_PART_SHIELD;
  player_ship.weapon = S_BASE_PART_WEAPON;
  player_ship.wing = S_BASE_PART_WING;
  player_ship.thruster = S_BASE_PART_THRUSTER;

  player_ship.cur_health = S_BASE_HEALTH;
  player_ship.cur_shield = S_BASE_SHIELD;
  player_ship.cur_power_use = 0.0;
  player_ship.reactor_can_recharge = 1;
  player_ship.ship_stalled = 0;

  reset_inventory();
  reset_equipped_parts();
}

// De-allocate player resources at end of game
void free_player() {
  if (st_player.inventory) {
    free(st_player.inventory);
  }
  free_entity(st_player.ent);
  delete_wrapper(st_player.wrapper_offset);
}

// Insert station mode player into global simulations
int player_insert_sim() {
  int status = sim_add_entity(physics_sim, st_player.ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(combat_sim, st_player.ent, ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, st_player.ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(event_sim, st_player.ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  return 0;
}

void player_remove_sim() {
  sim_remove_entity(physics_sim, st_player.ent);
  sim_remove_entity(combat_sim, st_player.ent);
  sim_remove_entity(event_sim, st_player.ent);
}

void sim_refresh_player() {
  COLLIDER *cur_col = NULL;
  for (size_t i = 0; i < st_player.ent->model->num_colliders; i++) {
    cur_col = st_player.ent->model->colliders + i;
    if (cur_col->category == DEFAULT) {
      refresh_collider(physics_sim, st_player.ent, i);
      refresh_collider(event_sim, st_player.ent, i);
    } else if (cur_col->category == HURT_BOX) {
      refresh_collider(combat_sim, st_player.ent, i);
    }
  }
}

// =============================== SPACE MODE ================================

// Initalize player ship struct at beginning of game
int init_player_ship() {
  memset(&player_ship, 0, sizeof(SHIP));

  player_ship.hull = S_BASE_PART_HULL;
  player_ship.reactor = S_BASE_PART_REACTOR;
  player_ship.shield = S_BASE_PART_SHIELD;
  player_ship.weapon = S_BASE_PART_WEAPON;
  player_ship.wing = S_BASE_PART_WING;
  player_ship.thruster = S_BASE_PART_THRUSTER;
  

  player_ship.ent = init_player_ship_ent();
  if (player_ship.ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate player ship entity\n");
    return -1;
  }
  player_ship.ent->type |= T_DRIVING;
  player_ship.ent->inv_mass = 1.0;
  player_ship.wrapper_offset = INVALID_INDEX;

  player_ship.cur_health = player_ship.hull.max_health;
  player_ship.cur_shield = player_ship.shield.max_shield;
  player_ship.cur_power_use = 0.0;
  player_ship.invuln = 0;
  player_ship.recharging_shield = 0;
  player_ship.reactor_can_recharge = 1;
  player_ship.ship_stalled = 0;

  return 0;
}

// De-allocate player ship resources at end of game
void free_player_ship() {
  free_entity(player_ship.ent);
  delete_wrapper(player_ship.wrapper_offset);
}

// Insert space mode player into global simulations
int player_ship_insert_sim() {
  int status = sim_add_entity(physics_sim, player_ship.ent, ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(combat_sim, player_ship.ent, ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, player_ship.ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(event_sim, player_ship.ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  return 0;
}

void player_ship_remove_sim() {
  sim_remove_entity(physics_sim, player_ship.ent);
  sim_remove_entity(combat_sim, player_ship.ent);
  sim_remove_entity(event_sim, player_ship.ent);
  sim_remove_entity(render_sim, player_ship.ent);
}

void reset_sp_player_state() {
  player_ship.cur_health = player_ship.hull.max_health;
  player_ship.cur_shield = player_ship.shield.max_shield;
  player_ship.invuln = 0;
  player_ship.recharging_shield = 0;
  player_ship.render_shield = 0;
}

void sim_refresh_player_ship() {
  COLLIDER *cur_col = NULL;
  for (size_t i = 0; i < player_ship.ent->model->num_colliders; i++) {
    cur_col = player_ship.ent->model->colliders + i;
    if (cur_col->category == DEFAULT) {
      refresh_collider(event_sim, player_ship.ent, i);
    } else if (cur_col->category == HURT_BOX) {
      refresh_collider(physics_sim, player_ship.ent, i);
      refresh_collider(combat_sim, player_ship.ent, i);
    }
  }
}

// =============================== HELPERS ================================

void recharge_player_shield() {
  if (mode == SPACE) {
    recharge_ship_shield(&player_ship);
  } else if (mode == STATION) {
    if (st_player.recharging_shield) {
      st_player.cur_shield += st_player.shield_recharge_rate * DELTA_TIME;
      if (st_player.cur_shield >= st_player.max_shield) {
        st_player.recharging_shield = 0;
        st_player.cur_shield = st_player.max_shield;
      }
    }
  }
}

void reactor_recharge_player() {
  if (mode == SPACE) {
    reactor_recharge(&player_ship);
  }
}

void get_player_coordinates(vec3 coords) {
  if (mode == SPACE) {
    glm_vec3_copy(player_ship.ent->translation, coords);
  } else if (mode == STATION) {
    glm_vec3_copy(st_player.ent->translation, coords);
  }
}

void get_player_gun_mat(mat4 dest) {
  mat4 to_player_space = GLM_MAT4_IDENTITY_INIT;
  glm_rotate(to_player_space, glm_rad(camera.pitch),
             (vec3) { 0.0, 0.0, 1.0 });
  glm_translate(to_player_space, (vec3) { -0.3, -0.25, 0.0 });
  mat4 temp = GLM_MAT4_IDENTITY_INIT;
  glm_mat4_ins3((mat3) {
    { 0.0, 0.0, 1.0 },
    { -1.0, 0.0, 0.0 },
    { 0.0, -1.0, 0.0 }
  }, temp);
  glm_mat4_transpose(temp);
  glm_mat4_mul(to_player_space, temp, to_player_space);

  glm_mat4_identity(dest);
  glm_translate(dest, camera.pos);
  glm_quat_rotate(dest, st_player.ent->rotation, dest);
  glm_scale(dest, st_player.ent->scale);
  glm_mat4_mul(dest, to_player_space, dest);
}

void player_ship_thrust_move() {
  if (mode == SPACE) {
    vec3 ship_forward;
    glm_quat_rotatev(player_ship.ent->rotation, (vec3){-1.0, 0.0, 0.0},
                     ship_forward);
    glm_normalize(ship_forward);
    glm_vec3_scale(ship_forward, player_ship.cur_speed, ship_forward);
    glm_vec3_copy(ship_forward, player_ship.ent->velocity);
    /* Slow down rotation speed each frame */
    glm_vec3_scale(player_ship.ent->ang_velocity, 0.99,
                  player_ship.ent->ang_velocity);
  }
}


// ================================= ANIMATION ===============================

void sp_player_shield_dmg(void *args) {
  if (player_ship.render_shield < 1.0) {
    player_ship.render_shield += 0.05;
    if (player_ship.render_shield > 1.0) {
      player_ship.render_shield = 1.0;
    }
    add_timer(0.03, sp_player_shield_dmg, -1000, NULL);
  } else {
    player_ship.render_shield = 0.0;
  }
}

// =================================== MISC ==================================
