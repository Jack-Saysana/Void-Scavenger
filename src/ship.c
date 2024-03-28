#include <ship.h>

/*                                SHIP.C

  Manages space-mode ships by providing helper functions used for movement
  and part management

*/

// ================================ HELPERS ==================================

float calc_power_usage(SHIP *ship) {
  float thruster_usage = ship->thruster.max_power_draw *
                         (ship->cur_speed / ship->thruster.max_vel);
  return thruster_usage + ship->shield.power_draw;
}

void recharge_ship_shield(SHIP *ship) {
  if (ship->recharging_shield) {
    ship->cur_shield += ship->shield.recharge_rate * DELTA_TIME;
    if (ship->cur_shield >= ship->shield.max_shield) {
      ship->recharging_shield = 0;
      ship->cur_shield = ship->shield.max_shield;
    }
  }
}

void ship_shield_recharge_delay(void *args) {
  if (!args || (size_t) args == INVALID_INDEX) {
    return;
  }

  SHIP *ship = (SHIP *) args;
  if (ship != &player_ship) {
    ship = sp_enemies + (size_t) args;
  }

  ship->recharging_shield = 1;
}
