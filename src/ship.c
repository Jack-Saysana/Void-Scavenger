#include <ship.h>

/*                                SHIP.C

  Manages space-mode ships by providing helper functions used for movement
  and part management

*/

void ship_shoot() {
  if (player_ship.ship_stalled) {
    return;
  }
  /* update power usage*/
  use_power(player_ship.weapon.max_power_draw, TYPE_WEAPON, &player_ship);
  /* get ship vectors */
  vec3 ship_forward;
  glm_quat_rotatev(player_ship.ent->rotation, (vec3){-1.0, 0.0, 0.0}, ship_forward);
  glm_normalize(ship_forward);
  vec3 ship_side;
  glm_quat_rotatev(player_ship.ent->rotation, (vec3){0.0, 0.0, 1.0}, ship_side);
  glm_normalize(ship_side);
  vec3 ship_up;
  glm_quat_rotatev(player_ship.ent->rotation, (vec3){0.0, 1.0, 0.0}, ship_up);
  glm_normalize(ship_up);
  if (player_ship.weapon.num_barrels == 1) {
    vec3 gun_pos = GLM_VEC3_ZERO_INIT;
    glm_vec3_scale_as(ship_forward, S_BARREL_FORWARD_OFFSET_INNER, gun_pos);
    glm_vec3_add(player_ship.ent->translation, gun_pos, gun_pos);
    vec3 dir = GLM_VEC3_ZERO_INIT;
    glm_vec3_copy(ship_forward, dir);
    glm_vec3_rotate(dir, glm_rad(S_BARREL_UP_ANGLE), ship_side);
    size_t proj_index = init_projectile(gun_pos,
                                        dir,
                                        player_ship.weapon.proj_speed +
                                        player_ship.cur_speed,
                                        SRC_PLAYER,
                                        player_ship.weapon.type,
                                        player_ship.weapon.damage,
                                        player_ship.weapon.range,
                                        0);
    projectile_insert_sim(proj_index);
  } else if (player_ship.weapon.num_barrels == 2) {
    /* rotate left gun to converage */
    vec3 dir = GLM_VEC3_ZERO_INIT;
    glm_vec3_copy(ship_forward, dir);
    glm_vec3_rotate(dir, glm_rad(S_BARREL_UP_ANGLE), ship_side);
    glm_vec3_rotate(dir, glm_rad(S_BARREL_IN_ANGLE), ship_up);
    /* get left gun offset pos */
    vec3 gun_pos = GLM_VEC3_ZERO_INIT;
    glm_vec3_scale_as(ship_forward, S_BARREL_FORWARD_OFFSET, gun_pos);
    glm_vec3_add(player_ship.ent->translation, gun_pos, gun_pos);
    glm_vec3_add(gun_pos, ship_side, gun_pos);
    /* spawn left projectile*/
    size_t proj_index = init_projectile(gun_pos,
                                        dir,
                                        player_ship.weapon.proj_speed +
                                        player_ship.cur_speed,
                                        SRC_PLAYER,
                                        player_ship.weapon.type,
                                        player_ship.weapon.damage,
                                        player_ship.weapon.range,
                                        0);
    projectile_insert_sim(proj_index);
    /* get right gun offset pos */
    glm_vec3_negate(ship_side);
    glm_vec3_scale_as(ship_forward, S_BARREL_FORWARD_OFFSET, gun_pos);
    glm_vec3_add(player_ship.ent->translation, gun_pos, gun_pos);
    glm_vec3_add(gun_pos, ship_side, gun_pos);
    /* rotate right gun to converage */
    glm_vec3_rotate(dir, glm_rad((-2.0 * S_BARREL_IN_ANGLE)), ship_up);
    /* spawn right projectile*/
    proj_index = init_projectile(gun_pos,
                                  dir,
                                  player_ship.weapon.proj_speed +
                                  player_ship.cur_speed,
                                  SRC_PLAYER,
                                  player_ship.weapon.type,
                                  player_ship.weapon.damage,
                                  player_ship.weapon.range,
                                  0);
    projectile_insert_sim(proj_index);
  } else if (player_ship.weapon.num_barrels == 3) {
    vec3 gun_pos = GLM_VEC3_ZERO_INIT;
    glm_vec3_scale_as(ship_forward, S_BARREL_FORWARD_OFFSET, gun_pos);
    glm_vec3_add(player_ship.ent->translation, gun_pos, gun_pos);
    vec3 dir = GLM_VEC3_ZERO_INIT;
    glm_vec3_copy(ship_forward, dir);
    glm_vec3_rotate(dir, glm_rad(S_BARREL_UP_ANGLE), ship_side);
    size_t proj_index = init_projectile(gun_pos,
                                        dir,
                                        player_ship.weapon.proj_speed +
                                        player_ship.cur_speed,
                                        SRC_PLAYER,
                                        player_ship.weapon.type,
                                        player_ship.weapon.damage,
                                        player_ship.weapon.range,
                                        0);
    projectile_insert_sim(proj_index);
    /* rotate left gun to converage */
    glm_vec3_rotate(dir, glm_rad(S_BARREL_IN_ANGLE_OUTER), ship_up);
    /* get left gun offset pos */
    glm_vec3_scale_as(ship_forward, S_BARREL_FORWARD_OFFSET_OUTER, gun_pos);
    glm_vec3_add(player_ship.ent->translation, gun_pos, gun_pos);
    vec3 side_offset = GLM_VEC3_ZERO_INIT;
    glm_vec3_copy(ship_side, side_offset);
    glm_vec3_scale_as(side_offset, S_BARREL_SIDE_OFFSET_OUTER, side_offset);
    glm_vec3_add(gun_pos, side_offset, gun_pos);
    vec3 down_offset = GLM_VEC3_ZERO_INIT;
    glm_vec3_scale_as(ship_up, S_BARREL_DOWN_OFFSET_OUTER, down_offset);
    glm_vec3_add(gun_pos, down_offset, gun_pos);
    /* spawn left projectile*/
    proj_index = init_projectile(gun_pos,
                                  dir,
                                  player_ship.weapon.proj_speed +
                                  player_ship.cur_speed,
                                  SRC_PLAYER,
                                  player_ship.weapon.type,
                                  player_ship.weapon.damage,
                                  player_ship.weapon.range,
                                  0);
    projectile_insert_sim(proj_index);
    /* get right gun offset pos */
    glm_vec3_negate(side_offset);
    glm_vec3_scale_as(ship_forward, S_BARREL_FORWARD_OFFSET_OUTER, gun_pos);
    glm_vec3_add(player_ship.ent->translation, gun_pos, gun_pos);
    glm_vec3_add(gun_pos, side_offset, gun_pos);
    glm_vec3_add(gun_pos, down_offset, gun_pos);
    /* rotate right gun to converage */
    glm_vec3_rotate(dir, glm_rad((-2.0 * S_BARREL_IN_ANGLE_OUTER)), ship_up);
    /* spawn right projectile*/
    proj_index = init_projectile(gun_pos,
                                  dir,
                                  player_ship.weapon.proj_speed +
                                  player_ship.cur_speed,
                                  SRC_PLAYER,
                                  player_ship.weapon.type,
                                  player_ship.weapon.damage,
                                  player_ship.weapon.range,
                                  0);
    projectile_insert_sim(proj_index);
  } else {
    /* rotate left gun to converage */
    vec3 dir = GLM_VEC3_ZERO_INIT;
    glm_vec3_copy(ship_forward, dir);
    glm_vec3_rotate(dir, glm_rad(S_BARREL_UP_ANGLE), ship_side);
    glm_vec3_rotate(dir, glm_rad(S_BARREL_IN_ANGLE), ship_up);
    /* get left gun offset pos */
    vec3 gun_pos = GLM_VEC3_ZERO_INIT;
    glm_vec3_scale_as(ship_forward, S_BARREL_FORWARD_OFFSET, gun_pos);
    glm_vec3_add(player_ship.ent->translation, gun_pos, gun_pos);
    vec3 side_offset = GLM_VEC3_ZERO_INIT;
    glm_vec3_copy(ship_side, side_offset);
    glm_vec3_scale_as(side_offset, S_BARREL_DOWN_OFFSET_DOUBLE, side_offset);
    glm_vec3_add(gun_pos, side_offset, gun_pos);
    vec3 down_offset = GLM_VEC3_ZERO_INIT;
    glm_vec3_scale_as(ship_up, (-1.0*S_BARREL_DOWN_OFFSET_DOUBLE), down_offset);
    glm_vec3_add(gun_pos, down_offset, gun_pos);
    /* spawn bottom left projectile*/
    size_t proj_index = init_projectile(gun_pos,
                                        dir,
                                        player_ship.weapon.proj_speed +
                                        player_ship.cur_speed,
                                        SRC_PLAYER,
                                        player_ship.weapon.type,
                                        player_ship.weapon.damage,
                                        player_ship.weapon.range,
                                        0);
    projectile_insert_sim(proj_index);
    glm_vec3_negate(down_offset);
    glm_vec3_add(gun_pos, down_offset, gun_pos);
    /* spawn top left projectile*/
    proj_index = init_projectile(gun_pos,
                                  dir,
                                  player_ship.weapon.proj_speed +
                                  player_ship.cur_speed,
                                  SRC_PLAYER,
                                  player_ship.weapon.type,
                                  player_ship.weapon.damage,
                                  player_ship.weapon.range,
                                  0);
    projectile_insert_sim(proj_index);
    /* get right gun offset pos */
    glm_vec3_negate(side_offset);
    glm_vec3_scale_as(ship_forward, S_BARREL_FORWARD_OFFSET, gun_pos);
    glm_vec3_add(player_ship.ent->translation, gun_pos, gun_pos);
    glm_vec3_add(gun_pos, side_offset, gun_pos);
    /* rotate right gun to converage */
    glm_vec3_rotate(dir, glm_rad((-2.0 * S_BARREL_IN_ANGLE)), ship_up);
    /* spawn top right projectile*/
    proj_index = init_projectile(gun_pos,
                                  dir,
                                  player_ship.weapon.proj_speed +
                                  player_ship.cur_speed,
                                  SRC_PLAYER,
                                  player_ship.weapon.type,
                                  player_ship.weapon.damage,
                                  player_ship.weapon.range,
                                  0);
    projectile_insert_sim(proj_index);
    glm_vec3_negate(down_offset);
    glm_vec3_add(gun_pos, down_offset, gun_pos);
    /* spawn bottom right projectile*/
    proj_index = init_projectile(gun_pos,
                                  dir,
                                  player_ship.weapon.proj_speed +
                                  player_ship.cur_speed,
                                  SRC_PLAYER,
                                  player_ship.weapon.type,
                                  player_ship.weapon.damage,
                                  player_ship.weapon.range,
                                  0);
    projectile_insert_sim(proj_index);
  }
}

// ================================ HELPERS ==================================

float calc_power_usage(SHIP *ship) {
  float thruster_usage = ship->thruster.max_power_draw *
                         (ship->cur_speed / ship->thruster.max_vel);
  return thruster_usage + ship->shield.power_draw;
}


void use_power(float pwr_draw, int type, SHIP * ship) {
  float delay_time;
  float new_pwr_draw;
  if (type == TYPE_WEAPON) {
    new_pwr_draw = pwr_draw * S_WEAPON_PWR_USE_FACTOR;
    delay_time = pwr_draw;
  } else if (type == TYPE_THRUSTER) {
    new_pwr_draw = pwr_draw * DELTA_TIME * 
                   ship->thruster.max_accel * S_THRUSTER_PWR_USE_FACTOR;
    delay_time = pwr_draw * S_THRUSTER_PWR_DELAY_FACTOR;
  } else if (type == TYPE_SHIELD) {
    new_pwr_draw = pwr_draw * TICK_RATE;
    delay_time = pwr_draw * S_SHIELD_PWR_DELAY_FACTOR;
  } else {
    return;
  }
  ship->cur_power_use += new_pwr_draw;
  if (ship->cur_power_use >= ship->reactor.max_output) {
    //initiate stall
    ship->cur_power_use = ship->reactor.max_output;
    if (ship == &player_ship) {
      stall_ship(ship);
    } else {
      ship->ship_stalled = 1;
      add_timer(S_E_STALL_TIME, destall_enemy_ship, -1000, ship);
    }
  }
  if (ship->reactor_can_recharge == 1) {
    ship->reactor_can_recharge = 0;
  } else {
    //delete previous disable reactor timer
    update_timer_memory((void*) &ship->reactor_can_recharge, NULL);
  }
  add_timer(delay_time, (void *) &ship->reactor_can_recharge, 1, NULL);
}

void reactor_recharge(SHIP * ship) {
  if (ship->cur_power_use > 0.0 && ship->reactor_can_recharge
      && !ship->ship_stalled) {
    ship->cur_power_use -= TICK_RATE * ship->reactor.recharge_rate;
    if (ship->cur_power_use <= 0.0) {
      ship->cur_power_use = 0.0;
    }
  }
}

void recharge_ship_shield(SHIP *ship) {
  if (ship->recharging_shield && !ship->ship_stalled) {
    use_power(ship->shield.power_draw, TYPE_SHIELD, ship);
    ship->cur_shield += ship->shield.recharge_rate * TICK_RATE;
    if (ship->cur_shield >= ship->shield.max_shield) {
      ship->recharging_shield = 0;
      ship->cur_shield = ship->shield.max_shield;
    }
  }
}

void ship_shield_recharge_delay(void *args) {
  if (args == ((void *) INVALID_INDEX)) {
    return;
  }

  SHIP *ship = (SHIP *) args;
  if (ship != &player_ship) {
    ship = sp_enemies + (size_t) args;
  }

  ship->recharging_shield = 1;
}

void destall_ship(SHIP * ship) {
  ship->ship_stalled = 0;
  end_stallwarning();
  add_timer(0.25, reset_stallwarning, -1000, NULL);
  ship->cur_power_use = ship->reactor.max_output * S_REACTOR_DESTALL_MIN;
}

void stall_ship(SHIP * ship) {
  ship->ship_stalled = 1;
  start_stallwarning();
  add_timer(ship->reactor.stall_time, destall_ship, -1000, ship);
}

void destall_enemy_ship(SHIP * ship) {
  ship->ship_stalled = 0;
  ship->cur_power_use = 0.0;
}