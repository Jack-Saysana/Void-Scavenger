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
  // TODO allocate player inventory

  st_player.ent = init_player_ent();
  if (st_player.ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate player entity\n");
    return -1;
  }

  st_player.wrapper_offset = init_wrapper(PLAYER_OBJ, st_player.ent,
                                          (void *) &st_player);
  if (st_player.wrapper_offset == INVALID_INDEX) {
    return -1;
  }

  st_player.max_health = P_BASE_HEALTH;
  st_player.health = P_BASE_HEALTH;
  st_player.speed = P_BASE_SPEED;
  st_player.fire_rate = P_BASE_FIRERATE;

  return 0;
}

// De-allocate player resources at end of game
void free_player() {
  free_entity(st_player.ent);
  delete_wrapper(st_player.wrapper_offset);
}

// =============================== SPACE MODE ================================

// Initalize player ship struct at beginning of game
int init_player_ship() {
  memset(&player_ship, 0, sizeof(SHIP));

  player_ship.reactor.max_output = S_BASE_PWR_OUTPUT;
  player_ship.hull.max_health = S_BASE_HEALTH;
  player_ship.shield.max_shield = S_BASE_SHIELD;
  player_ship.shield.recharge_rate = S_BASE_SHIELD_RECHARGE;
  player_ship.shield.recharge_delay = S_BASE_SHIELD_DELAY;
  player_ship.shield.power_draw = S_BASE_PWR_DRAW;
  player_ship.weapon.type = BALLISTIC;
  player_ship.weapon.damage = S_BASE_DAMAGE;
  player_ship.weapon.fire_rate = S_BASE_FIRERATE;
  player_ship.weapon.max_power_draw = S_BASE_PWR_DRAW;
  player_ship.wing.max_ang_vel = S_BASE_ANG_VEL;
  player_ship.wing.max_ang_accel = S_BASE_ANG_ACCEL;
  player_ship.thruster.max_vel = S_BASE_VEL;
  player_ship.thruster.max_accel = S_BASE_ACCEL;
  player_ship.thruster.max_power_draw = S_BASE_PWR_DRAW;

  player_ship.ent = init_player_ship_ent();
  if (player_ship.ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate player ship entity\n");
    return -1;
  }
  player_ship.wrapper_offset = init_wrapper(PLAYER_SHIP_OBJ, player_ship.ent,
                                          (void *) &player_ship);
  if (player_ship.wrapper_offset == INVALID_INDEX) {
    return -1;
  }

  player_ship.cur_health = S_BASE_HEALTH;
  player_ship.cur_shield = S_BASE_SHIELD;

  return 0;
}

// De-allocate player ship resources at end of game
void free_player_ship() {
  free_entity(player_ship.ent);
  delete_wrapper(player_ship.wrapper_offset);
}

