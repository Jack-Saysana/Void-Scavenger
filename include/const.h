#ifndef __CONST_H__
#define __CONST_H__

// Tick Constants
#define TICK_RATE (0.05)      // 1/20 sec

// Player constants
#define P_BASE_HEALTH (100.0)
#define P_BASE_SHIELD (100.0)
#define P_BASE_SPEED (7.5)
#define P_BASE_FIRERATE (0.1)
#define P_BASE_SHIELD_RECHARGE (5.0)
#define P_BASE_SHIELD_DELAY (2.0)
#define P_BASE_MAX_EXP (100.0)
#define P_BASE_DAMAGE (10.0)
#define P_LEVEL_SCALE (50.0)
#define P_BASE_JUMP (5.0)

// Ship constants
#define S_BASE_PWR_OUTPUT (100.0)
#define S_BASE_REACTOR_RECHARGE (10.0)
#define S_BASE_STALL_TIME (10.0)
#define S_BASE_HEALTH (100.0)
#define S_BASE_SHIELD (100.0)
#define S_BASE_SHIELD_RECHARGE (7.5)
#define S_BASE_SHIELD_DELAY (7.5)
#define S_BASE_PWR_DRAW (7.5)
#define S_BASE_DAMAGE (50.0)
#define S_BASE_FIRERATE (0.1)
#define S_BASE_FIRERATE_LASER (0.3)
#define S_BASE_WEAPON_PWR_DRAW (2.5)
#define S_BASE_NUM_BARRELS (2)
#define S_BASE_BULLET_SIZE (1.0)
#define S_BASE_PROJ_SPEED (100.0)
#define S_E_BASE_PROJ_SPEED (300.0)
#define S_BASE_RANGE (500.0)
#define S_BASE_ANG_VEL (0.25)
#define S_BASE_ANG_ACCEL (0.25)
#define S_BASE_VEL (10.0)
#define S_BASE_ACCEL (5.0)
#define S_BASE_THRUSTER_PWR_DRAW (5.0)

//Base ship parts
#define S_BASE_PART_HULL        ((S_HULL){S_BASE_HEALTH})
#define S_BASE_PART_REACTOR     ((S_REACTOR){S_BASE_PWR_OUTPUT, \
                                S_BASE_REACTOR_RECHARGE, S_BASE_STALL_TIME})
#define S_BASE_PART_SHIELD      ((S_SHIELD){S_BASE_SHIELD,\
                                S_BASE_SHIELD_RECHARGE, S_BASE_SHIELD_DELAY,\
                                S_BASE_PWR_DRAW})
#define S_BASE_PART_WEAPON      ((S_WEAPON){BALLISTIC, S_BASE_DAMAGE,\
                                S_BASE_FIRERATE, S_BASE_WEAPON_PWR_DRAW,\
                                S_BASE_PROJ_SPEED, S_BASE_RANGE,\
                                S_BASE_BULLET_SIZE, S_BASE_NUM_BARRELS})
#define S_BASE_PART_WING        ((S_WING){S_BASE_ANG_VEL, S_BASE_ANG_ACCEL})
#define S_BASE_PART_THRUSTER    ((S_THRUSTER){S_BASE_VEL, S_BASE_ACCEL,\
                                S_BASE_THRUSTER_PWR_DRAW})

//Ship Enemy Type Constants
#define S_E_HEALTH_TYPE_BASE_HEALTH (160.0)
#define S_E_HEALTH_TYPE_BASE_SHIELD (40.0)
#define S_E_SHIELD_TYPE_BASE_HEALTH (40.0)
#define S_E_SHIELD_TYPE_BASE_SHIELD (160.0)
#define S_E_HEALTH_TYPE_HEALTH_MODIFIER (45.0)
#define S_E_HEALTH_TYPE_SHIELD_MODIFIER (5.0)
#define S_E_SHIELD_TYPE_HEALTH_MODIFIER (5.0)
#define S_E_SHIELD_TYPE_SHIELD_MODIFIER (45.0)
#define S_E_STANDARD_TYPE_HEALTH_MODIFIER (25.0)
#define S_E_STANDARD_TYPE_SHIELD_MODIFIER (25.0)
#define S_E_MID_SPEED_BASE_VEL (20.0)
#define S_E_MID_SPEED_BASE_ACCEL (6.0)
#define S_E_HIGH_SPEED_BASE_VEL (30.0)
#define S_E_HIGH_SPEED_BASE_ACCEL (7.0)
#define S_E_ULTRA_SPEED_BASE_VEL (40.0)
#define S_E_ULTRA_SPEED_BASE_ACCEL (8.0)
#define S_E_STALL_TIME (3.5)


//Ship Part Generation
#define GOLD_POOL (50)
#define PURPLE_POOL (40)
#define GREEN_POOL (30)
#define BLUE_POOL (20)
#define WHITE_POOL (10)
#define HULL_NUM_STATS (1)
#define HULL_HEALTH_MODIFIER (5.0)
#define HULL_HEALTH_MIN (100.0) //BASE = 100
#define REACTOR_NUM_STATS (3)
#define REACTOR_MAX_POWER_OUTPUT_MODIFIER (10.0)
#define REACTOR_MAX_POWER_OUTPUT_MIN (75.0) //BASE = 100
#define REACTOR_RECHARGE_RATE_MODIFIER (0.5)
#define REACTOR_RECHARGE_RATE_MIN (7.5) //BASE = 10
#define REACTOR_STALL_TIME_MODIFIER (-0.15)
#define REACTOR_STALL_TIME_MIN (9.0) //BASE 10.0
#define SHIELD_NUM_STATS (4)
#define SHIELD_MAX_SHIELD_MODIFIER (5.0)
#define SHIELD_MAX_SHIELD_MIN (75.0) //BASE = 100
#define SHIELD_RECHARGE_RATE_MODIFIER (0.25)
#define SHIELD_RECHARGE_RATE_MIN (5.0) //BASE = 7.5
#define SHIELD_RECHARGE_DELAY_MODIFIER (-0.25)
#define SHIELD_RECHARGE_DELAY_MIN (10.0) //BASE = 7.5
#define SHIELD_POWER_DRAW_MODIFIER (-0.25)
#define SHIELD_POWER_DRAW_MIN (10.0) //BASE = 7.5
#define WEAPON_NUM_STATS (7)
#define WEAPON_DAMAGE_MODIFIER (5.0)
#define WEAPON_DAMAGE_MIN (30.0) //BASE = 50
#define WEAPON_FIRE_RATE_MODIFIER (-0.005)
#define WEAPON_FIRE_RATE_MIN (0.2) //BASE = 0.1
#define WEAPON_FIRE_RATE_MIN_LASER (0.4)// BASE_LASER = 0.3
#define WEAPON_POWER_DRAW_MODIFIER (-0.05)
#define WEAPON_POWER_DRAW_MIN (3.0) //BASE = 2.5
#define WEAPON_PROJ_SPEED_MODIFIER (2.5)
#define WEAPON_PROJ_SPEED_MIN (75.0) //BASE = 100
#define WEAPON_RANGE_MODIFIER (5.0)
#define WEAPON_RANGE_MIN (450) //BASE = 500
#define WEAPON_BULLET_SIZE_MODIFIER (0.05)
#define WEAPON_BULLET_SIZE_MIN (0.5) //BASE = 1.0
#define WEAPON_NUM_BARRELS_MODIFIER (0.1)
#define WEAPON_NUM_BARRELS_MIN (1.0) //BASE 2
#define WING_NUM_STATS (2)
#define WING_ANG_VEL_MODIFIER (0.005)
#define WING_ANG_VEL_MIN (0.15) //BASE = 0.25
#define WING_ANG_ACCEL_MODIFIER (0.005)
#define WING_ANG_ACCEL_MIN (0.15) //BASE = 0.25
#define THRUSTER_NUM_STATS (3)
#define THRUSTER_MAX_VEL_MODIFIER (0.25)
#define THRUSTER_MAX_VEL_MIN (7.5) //BASE = 10.0
#define THRUSTER_MAX_ACCEL_MODIFIER (0.2)
#define THRUSTER_MAX_ACCEL_MIN (3.5) //BASE = 5.0
#define THRUSTER_MAX_POWER_DRAW_MODIFIER (-0.05)
#define THRUSTER_MAX_POWER_DRAW_MIN (6.5) //BASE = 5.0
#define MAX_NUM_STATS (10)

//STAT CAPS
#define THRUSTER_PWR_DRAW_CAP (0.25)
#define SHIELD_RECHARGE_DELAY_CAP (2.0)
#define SHIELD_PWR_DRAW_CAP (2.0)
#define WEAPON_FIRERATE_CAP (0.01)
#define WEAPON_PWR_DRAW_CAP (0.25)
#define WEAPON_NUM_BARRELS_CAP (4.0)
#define REACTOR_STALL_TIME_CAP (2.0)

//Ship Barrel Placment numers
#define S_BARREL_UP_ANGLE (-1.5)
#define S_BARREL_IN_ANGLE (-0.3125)
#define S_BARREL_IN_ANGLE_OUTER (-0.625)
#define S_BARREL_FORWARD_OFFSET (7.0)
#define S_BARREL_FORWARD_OFFSET_OUTER (5.0)
#define S_BARREL_FORWARD_OFFSET_INNER (10.0)
#define S_BARREL_SIDE_OFFSET_OUTER (8.5)
#define S_BARREL_DOWN_OFFSET_OUTER (-2.0)
#define S_BARREL_DOWN_OFFSET_DOUBLE (1.5)

//Ship Power Constants
#define S_THRUSTER_PWR_USE_FACTOR (0.75)
#define S_THRUSTER_PWR_DELAY_FACTOR (0.25)
#define S_WEAPON_PWR_USE_FACTOR (0.5)
#define S_SHIELD_PWR_DELAY_FACTOR (0.75)
#define S_REACTOR_DESTALL_MIN (0.25)
#define S_THRUSTER_REVERSE_FACTOR (0.5)

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
#define MAX_SP_AGRO_RANGE (512.0)
#define MIN_SP_FOLLOW_RANGE (100.0)
#define SP_OBJ_AVOIDANCE_THRESHOLD (0.7071)
#define SP_AVOID_BOUNDS_PRIORITY (100.0)
#define SP_AVOID_OBSTACLE_PRIORITY (2.0)
#define SP_CHASE_PRIORITY (1.0)
#define SP_SHOT_DELAY (2.5)

#define NUM_ALIEN_TYPES (2)
#define NUM_ALIEN_SHIP_TYPES (3)
#define NUM_ALIEN_ATTACK_TYPES (7)
#define NUM_ALIEN_MOV_TYPES (4)
#define ST_E_BASE_PROJ_SPEED (10.0)
#define ST_E_BASE_PROJ_DAMAGE (10.0)
#define ST_E_BASE_PROJ_RANGE (100.0)
#define E_ANIM_HURT_MELEE (0)
#define E_ANIM_HURT_RANGED (1)
#define E_ANIM_SHOOTING (2)
#define E_ANIM_STANDING_MELEE (3)
#define E_ANIM_STANDING_RANGED (4)
#define E_ANIM_SWINGING (5)
#define E_ANIM_WALK_MELEE (6)
#define E_ANIM_WALK_RANGED (7)
#define E_MELEE (0)
#define E_RANGED (1)
#define E_RANDOM (2)

// Audio Tracks and Constants
#define BALLISTIC_GUN_WAV           (0)
#define LASER_GUN_WAV               (1)
#define PLASMA_GUN_WAV              (2)
#define STATION_MODE_WEAPON_WAV     (3)
#define SPACESHIP_EXPLOSION_WAV     (4)
#define SHIELD_STATION_MODE_HIT_WAV (5)
#define SPACESHIP_HULL_HIT_WAV      (6)
#define WORLD_EXIT_WAV              (7)
#define PLAYER_DEATH_1_WAV          (8)
#define PLAYER_DEATH_2_WAV          (9)
#define PLAYER_HURT_1_WAV           (10)
#define PLAYER_HURT_2_WAV           (11)
#define PLAYER_HURT_3_WAV           (12)
#define PLAYER_HURT_4_WAV           (13)
#define ALIEN_NORMAL_TALKING_WAV    (14)
#define ALIEN_NORMAL_DEATH_WAV      (15)
#define ALIEN_BRUTE_TALKING_WAV     (16)
#define ALIEN_BRUTE_DEATH_WAV       (17)
#define SHIP_SINE_WAVE              (18)
#define SHIP_TRI_WAVE_1             (19)
#define SHIP_TRI_WAVE_2             (20)
#define MAIN_THEME                  (21)
#define SPACE_THEME                 (22)
#define STATION_THEME               (23)

#define INVALID_SOURCE              (-1)
#define SOURCE_PAUSED               (0)
#define SOURCE_PLAYING              (1)
#define BASE_SINE_FREQUENCY         (150.0)
#define BASE_TRIANGLE_FREQUENCY     (49.0)
#define MAX_SHIP_VELOCITY_TONE      (10.0)
#define MAX_TONE                    (100.0)
#define MAX_GAIN_DIST               (25.0)

// Station Eneemy Types
#define BRUTE (0)
#define NORMAL (1)

//Space Enemy Types
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
#define E_HEALTH_MODIFIER_NORMAL (25.0)
#define E_HEALTH_MODIFIER_BRUTE (30.0)
#define E_LEVEL_SCALE_CAP (10.0)
#define E_BASE_SPEED_NORMAL (3.0)
#define E_BASE_SPEED_BRUTE (1.75)
#define E_BASE_FIRERATE_NORMAL (0.2)
#define E_BASE_FIRERATE_BRUTE (0.5)
#define E_BASE_FIRERATE_MELEE (0.5)
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
#define BASE_SPACE_SIZE (1024.0)
#define SPACE_DEPTH (10)
#define STATION_SIZE (80.0)
#define STATION_DEPTH (6)
#define ST_BASE_RENDER_DIST (40.0)
#define ST_BASE_SIM_DIST (32.0)
#define SP_BASE_RENDER_DIST (2000.0)
#define SP_BASE_SIM_DIST (2000.0)
#define BASE_NUM_ENEMIES (5)
#define ST_GRAVITY (12.0)

// Asteroid constants
#define NUM_ASTEROIDS (30)
#define NUM_ASTEROID_TYPES (5)
#define TYPE_ASTEROID (0)

// Corridor constants
#define NUM_CORRIDOR_TYPES (14)
#define TYPE_ONE_WAY (0)
#define TYPE_FOUR_WAY (1)
#define TYPE_CORNER (2)
#define TYPE_T_JUNCT (3)
#define TYPE_CORRIDOR (4)
#define CORNER_DOUBLE_ENTRANCE     (5)
#define CORNER_SINGLE_ENTRANCE     (6)
#define CORNER_SINGLE_ENTRANCE_ALT (7)
#define DOUBLE_CORNER              (8)
#define FLAT_DOOR                  (9)
#define FLAT_DOOR_NEST             (10)
#define FLAT_WALL                  (11)
#define FLAT_WALL_NEST             (12)
#define MID_FLOOR                  (13)
#define NEIGHBOR_POS_X (0)
#define NEIGHBOR_NEG_X (1)
#define NEIGHBOR_POS_Z (2)
#define NEIGHBOR_NEG_Z (3)

#define NEIGHBOR_TOP_LEFT (0)
#define NEIGHBOR_TOP (1)
#define NEIGHBOR_TOP_RIGHT (2)
#define NEIGHBOR_LEFT (3)
#define NEIGHBOR_RIGHT (4)
#define NEIGHBOR_BOTTOM_LEFT (5)
#define NEIGHBOR_BOTTOM (6)
#define NEIGHBOR_BOTTOM_RIGHT (7)

#define SEARCHABLE_TL (0x1)
#define SEARCHABLE_T  (0x2)
#define SEARCHABLE_TR (0x4)
#define SEARCHABLE_L  (0x8)
#define SEARCHABLE_R  (0x10)
#define SEARCHABLE_BL (0x20)
#define SEARCHABLE_B  (0x40)
#define SEARCHABLE_BR (0x80)
#define SEARCHABLE_ALL (0xFF)

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
#define BASE_COLLISION_DAMAGE_VEL (7.0)
#define BASE_COLLISION_DAMAGE     (50.0)

// Targeting System consts
#define MAX_TARGET_DIST (512.0)

// Pathfinding consts
#define ST_ENEMY_SEARCH_DEPTH (4)
#define ST_ENEMY_RANGE_MIN (10.0)
#define ST_ENEMY_RANGE_MAX (15.0)

// Misc
#define X (0)
#define Y (1)
#define Z (2)
#define W (3)

#define FUNCTION_PTR (-1000)

#define TOP (0)
#define BOTTOM (1)
#define LEFT (2)
#define RIGHT (3)
#define FORWARD (4)
#define BACK (5)

#define INVALID_FRAME (0xFFFFFFFF)

#define POSITIVE (0)
#define NEGATIVE (1)

#define NUM_PARTICLES (1000)

#endif
