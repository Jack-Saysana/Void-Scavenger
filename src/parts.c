#include <parts.h>

/*
  Init parts_list globaly, call by ?

  Return
    0 if successful
    otherwise unsuccessful
*/
int init_parts_list() {
  for (int i = 0; i < MAX_LIST; i++) {
    generate_parts((I_SLOT_ID)(i % 6), parts_list[i]);
  }
  return 0;
}

/*
  Generate a equippable part to I_SLOT slot
  The I_SLOT.data stores the attribute of the generated part
  The I_SLOT.type stores the type of the generated part

  Args
    I_SLOT_ID enum_poarts
      The enum I_SLOT_ID of the equippable part to be generate
    
  Return
    0 if successful
    otherwise unsuccessful
*/
int generate_parts(I_SLOT_ID parts_type, I_SLOT slot) {
  slot.type = parts_type;
  switch (parts_type) {
    case I_SLOT_REACTOR:
      slot.data.reactor.max_output = (rand() % 100) + 100;
      break;
    case I_SLOT_HULL:
      slot.data.hull.max_health = (rand() % 100) + 100;
      break;
    case I_SLOT_SHIELD:
      slot.data.shield.max_shield = (rand() % 100) + 100;
      slot.data.shield.power_draw = (rand() % 100) + 100;
      slot.data.shield.recharge_delay = (rand() % 100) + 100;
      slot.data.shield.recharge_rate = (rand() % 100) + 100;
      break;
    case I_SLOT_WEAPON:
      switch((rand() % 3)) {
        case 0:
          slot.data.weapon.type = BALLISTIC;
          break;
        case 1:
          slot.data.weapon.type = LASER;
          break;
        case 2:
          slot.data.weapon.type = PLASMA;
          break;
      }
      slot.data.weapon.damage = (rand() % 100) + 100;
      slot.data.weapon.fire_rate = (rand() % 100) + 100;
      slot.data.weapon.max_power_draw = (rand() % 100) + 100;
      slot.data.weapon.proj_speed = (rand() % 100) + 100;
      slot.data.weapon.range = (rand() % 100) + 100;
      break;
    case I_SLOT_WING:
      slot.data.wing.max_ang_accel = (rand() % 100) + 100;
      slot.data.wing.max_ang_vel = (rand() % 100) + 100;
      break;
    case I_SLOT_THRUSTER:
      slot.data.thruster.max_accel = (rand() % 100) + 100;
      slot.data.thruster.max_power_draw = (rand() % 100) + 100;
      slot.data.thruster.max_vel = (rand() % 100) + 100;
      break;
    default:
      break;
  }
  return 0;
}
