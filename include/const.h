#ifndef __CONST_H__
#define __CONST_H__

// Player constants
#define P_BASE_HEALTH (100.0)
#define P_BASE_SHIELD (100.0)
#define P_BASE_SPEED (10.0)
#define P_BASE_FIRERATE (0.1)
#define P_BASE_MAX_EXP (100.0)
#define P_LEVEL_SCALE (50.0)

// Ship constants
#define S_BASE_PWR_OUTPUT (100.0)
#define S_BASE_HEALTH (100.0)
#define S_BASE_SHIELD (100.0)
#define S_BASE_SHIELD_RECHARGE (5.0)
#define S_BASE_SHIELD_DELAY (2.0)
#define S_BASE_PWR_DRAW (25.0)
#define S_BASE_DAMAGE (100.0)
#define S_BASE_FIRERATE (0.1)
#define S_BASE_PROJ_SPEED (100.0)
#define S_BASE_RANGE (500.0)
#define S_BASE_ANG_VEL (0.25)
#define S_BASE_ANG_ACCEL (0.25)
#define S_BASE_VEL (10.0)
#define S_BASE_ACCEL (5.0)
#define S_E_HEALTH_TYPE_BASE_HEALTH (160.0)
#define S_E_HEALTH_TYPE_BASE_SHIELD (40.0)
#define S_E_SHIELD_TYPE_BASE_HEALTH (40.0)
#define S_E_SHIELD_TYPE_BASE_SHIELD (160.0)
#define S_E_MID_SPEED_BASE_VEL (20.0)
#define S_E_MID_SPEED_BASE_ACCEL (6.0)
#define S_E_HIGH_SPEED_BASE_VEL (30.0)
#define S_E_HIGH_SPEED_BASE_ACCEL (7.0)
#define S_E_ULTRA_SPEED_BASE_VEL (40.0)
#define S_E_ULTRA_SPEED_BASE_ACCEL (8.0)

// Station Ship Parts Constants
#define NUM_STATION_SHIP_PART_TYPES (6)
#define TYPE_THRUSTER               (0)
#define TYPE_HULL                   (1)
#define TYPE_REACTOR                (2)
#define TYPE_SHIELD                 (3)
#define TYPE_WEAPON                 (4)
#define TYPE_WING                   (5)
#define TYPE_WEAPON_BALLISTIC       (6)
#define TYPE_WEAPON_LASER           (7)
#define TYPE_WEAPON_PLASMA          (8)
#define NOT_WEAPON (8008135)
#define W_BALLISTIC  (0)
#define W_LASER      (1)
#define W_PLASMA     (2)
#define GOLD_RARITY   (0)
#define PURPLE_RARITY (1)
#define GREEN_RARITY  (2)
#define BLUE_RARITY   (3)
#define WHITE_RARITY  (4)
#define RARITY_LEVELS (5)
#define RARITY_ERR    (-1)

// Enemy Constants
#define NUM_ALIEN_TYPES (2)
#define NUM_ALIEN_SHIP_TYPES (3)
#define NUM_ALIEN_ATTACK_TYPES (7)
#define NUM_ALIEN_MOV_TYPES (4)
#define E_ANIM_HURT (0)
#define E_ANIM_SHOOTING (1)
#define E_ANIM_STANDING (2)
#define E_ANIM_WALK (3)

#define BRUTE (0)
#define NORMAL (1)

#define STANDARD_BALLISTIC (0)
#define HEALTH_BALLISTIC (1)
#define SHIELD_BALLISTIC (2)
#define STANDARD_PLASMA (3)
#define STANDARD_LASER (4)
#define HEALTH_LASER (5)
#define SHIELD_PLASMA (6)

#define E_LOW_SPEED (0)
#define E_MID_SPEED (1)
#define E_HIGH_SPEED (2)
#define E_ULTRA_SPEED (3)


#define E_BASE_HEALTH_NORMAL (100.0)
#define E_BASE_HEALTH_BRUTE (150.0)
#define E_BASE_SPEED_NORMAL (3.0)
#define E_BASE_SPEED_BRUTE (1.75)
#define E_BASE_FIRERATE_NORMAL (0.05)
#define E_BASE_FIRERATE_BRUTE (0.1)
#define E_BASE_XP (20.0)
#define E_BRUTE_XP (30.0)
#define E_LEVEL_SCALE (10.0)
#define E_XP_RANGE (4.0)
#define E_TYPE_UPDATE_0 (1.0)
#define E_TYPE_UPDATE_1 (4.0)
#define E_TYPE_UPDATE_2 (6.0)
#define E_ATTACK_TYPE_TIER_0 (0.0)
#define E_ATTACK_TYPE_TIER_1 (2.0)
#define E_ATTACK_TYPE_TIER_2 (4.0)
#define E_ATTACK_TYPE_TIER_3 (6.0)
#define E_BASE_NUM_TYPES (2)

// Projectile Constants
#define NUM_PROJ_TYPES (2)

#define SHIP_PROJ (0)
#define STAT_PROJ (1)

// Simulation constants
#define BASE_SPACE_SIZE (256.0)
#define SPACE_DEPTH (8)
#define STATION_SIZE (80.0)
#define STATION_DEPTH (6)
#define ST_BASE_RENDER_DIST (14.0)
#define ST_BASE_SIM_DIST (16.0)
#define SP_BASE_RENDER_DIST (500.0)
#define SP_BASE_SIM_DIST (256.0)
#define BASE_NUM_ENEMIES (5)

// Asteroid constants
#define NUM_ASTEROIDS (30)
#define NUM_ASTEROID_TYPES (5)
#define TYPE_ASTEROID (0)

// Corridor constants
#define NUM_CORRIDOR_TYPES (5)
#define TYPE_ONE_WAY (0)
#define TYPE_FOUR_WAY (1)
#define TYPE_CORNER (2)
#define TYPE_T_JUNCT (3)
#define TYPE_CORRIDOR (4)
#define NEIGHBOR_POS_X (0)
#define NEIGHBOR_NEG_X (1)
#define NEIGHBOR_POS_Z (2)
#define NEIGHBOR_NEG_Z (3)

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

// Misc. Combat Constants
#define BASE_COLLISION_DAMAGE_VEL (30.0)
#define BASE_COLLISION_DAMAGE     (50.0)

// Targeting System consts
#define MAX_TARGET_DIST (100.0)

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

#define INVALID_FRAME (0xFFFFFFFF)

#endif
