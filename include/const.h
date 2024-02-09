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
#define SPACE_SIZE (1024.0)
#define SPACE_DEPTH (9)
#define STATION_SIZE (1024.0)
#define STATION_DEPTH (9)
#define RENDER_DIST (10.0)

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

// Station obstacle constants
#define NUM_STATION_OBSTACLE_TYPES (20)
#define TYPE_AMMO_CRATE_0          (0)
#define TYPE_AMMO_CRATE_1          (1)
#define TYPE_CRATE_0               (2)
#define TYPE_CRATE_1               (3)
#define TYPE_CRYO_BED              (4)
#define TYPE_HEALTH_CRATE_0        (5)
#define TYPE_HEALTH_CRATE_1        (6)
#define TYPE_MEDICAL_ARMS          (7)
#define TYPE_OXYGEN_TANK_0         (8)
#define TYPE_PLANT_VASE            (9)
#define TYPE_SHIELD_CRATE_0        (10)
#define TYPE_SHIELD_CRATE_1        (11)
#define TYPE_TOILET                (12)
#define TYPE_BIG_BUG               (13)
#define TYPE_HOSE_0                (14)
#define TYPE_HOSE_1                (15)
#define TYPE_HOSE_2                (16)
#define TYPE_HOSE_3                (17)
#define TYPE_STOOL                 (18)
#define TYPE_TABLE                 (19)
#define STATION_SMALL_OBJS         (9)
#define STATION_LARGE_OBJS         (11)

// Misc
#define X (0)
#define Y (1)
#define Z (2)
#define W (3)


#endif
