#ifndef __SHIP_STR_H__
#define __SHIP_STR_H__

/*                                SHIP_STR.H

  Manages a ship (either player or enemy) in the game's space mode. Each ship
  tracks its part list, as well as spatial/physical information.

*/

typedef enum ship_weap_type {
  BALLISTIC,
  LASER,
  PLASMA,
} S_WEAPON_T;

typedef struct reactor_t {
  float max_output;
  float recharge_rate;
  float stall_time;
} S_REACTOR;

typedef struct hull_t {
  float max_health;
} S_HULL;

typedef struct shield_t {
  float max_shield;
  float recharge_rate;
  float recharge_delay;
  float power_draw;
} S_SHIELD;

typedef struct weapon_t {
  S_WEAPON_T type;
  float damage;
  float fire_rate;
  float max_power_draw;
  float proj_speed;
  float range;
  float bullet_size;
  int num_barrels;
} S_WEAPON;

typedef struct wing_t {
  float max_ang_vel;
  float max_ang_accel;
} S_WING;

typedef struct thruster_t {
  float max_vel;
  float max_accel;
  float max_power_draw;
} S_THRUSTER;

typedef struct ship_t {
  S_REACTOR reactor;
  S_HULL hull;
  S_SHIELD shield;
  S_WEAPON weapon;
  S_WING wing;
  S_THRUSTER thruster;

  // Entity in space simulation
  ENTITY *ent;
  // Offset of respective wrapper in the object_wrapper buffer
  size_t wrapper_offset;

  float cur_health;
  float cur_shield;
  float cur_speed;
  float cur_power_use;
  // Flag denoting if the ship is current invulnerable to damage
  int invuln;
  int recharging_shield;
  int reactor_can_recharge;
  int ship_stalled;

  int e_can_shoot;
  // Float denoting the current opacity of the ship's shield
  float render_shield;
} SHIP;

#endif
