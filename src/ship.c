#include <ship.h>

/*                                SHIP.C

  Manages space-mode ships by providing helper functions used for movement
  and part management

*/

float calc_power_usage(SHIP *ship) {
  float thruster_usage = ship->thruster.max_power_draw *
                         (ship->cur_speed / ship->thruster.max_vel);
  return thruster_usage + ship->shield.power_draw;
}
