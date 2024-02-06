#ifndef __CONST_H__
#define __CONST_H__

// Player constants
#define P_BASE_HEALTH (100.0)
#define P_BASE_SPEED (1.0)
#define P_BASE_FIRERATE (0.1)

// Ship constants
#define S_BASE_PWR_OUTPUT (100.0)
#define S_BASE_HEALTH (100.0)
#define S_BASE_SHIELD (25.0)
#define S_BASE_SHIELD_RECHARGE (5.0)
#define S_BASE_SHIELD_DELAY (2.0)
#define S_BASE_PWR_DRAW (25.0)
#define S_BASE_DAMAGE (10.0)
#define S_BASE_FIRERATE (0.1)
#define S_BASE_ANG_VEL (10.0)
#define S_BASE_ANG_ACCEL (5.0)
#define S_BASE_VEL (10.0)
#define S_BASE_ACCEL (5.0)

// Enemy Constants
#define NUM_ALIEN_TYPES (2)
#define NUM_ALIEN_SHIP_TYPES (2)

#define BRUTE (0)
#define NORMAL (1)

#define E_BASE_HEALTH (100.0)
#define E_BASE_SPEED (1.0)
#define E_BASE_FIRERATE (0.1)

// Projectile Constants
#define NUM_PROJ_TYPES (2)

#define SHIP_PROJ (0)
#define STAT_PROJ (1)

// Simulation constants
#define SPACE_SIZE (32.0)
#define SPACE_DEPTH (4)
#define STATION_SIZE (32.0)
#define STATION_DEPTH (4)
#define RENDER_DIST (128.0)

// Asteroid constants
#define NUM_ASTEROIDS (10)
#define NUM_ASTEROID_TYPES (5)
#define TYPE_ASTEROID (0)

// Corridor constants
#define NUM_CORRIDOR_TYPES (5)
#define TYPE_ONE_WAY (0)
#define TYPE_FOUR_WAY (1)
#define TYPE_CORNER (2)
#define TYPE_T_JUNCT (3)
#define TYPE_CORRIDOR (4)

// Misc
#define X (0)
#define Y (1)
#define Z (2)
#define W (3)

#define TOP (0)
#define BOTTOM (1)
#define LEFT (2)
#define RIGHT (3)
#define FORWARD (4)
#define BACK (5)

#endif
