#ifndef __GLOBAL_VARS_H__
#define __GLOBAL_VARS_H__

#include <engine/engine.h>
#include <structs/camera_str.h>
#include <structs/player_str.h>
#include <structs/ship_str.h>
#include <structs/enemy_str.h>
#include <structs/projectile_str.h>
#include <structs/item_str.h>
#include <structs/obstacle_str.h>
#include <structs/corridor_str.h>
#include <structs/obj_wrapper_str.h>

// Insert common global variables below
// Text Font Vars
extern F_GLYPH *fixed_sys;

// Current game mode
typedef enum game_mode {
  STATION,
  SPACE
} GAME_MODE;
extern GAME_MODE mode;

// Game camera
extern CAM camera;

// Used for determining which entities should be rendered in a given scene
extern ENTITY *render_sphere;

extern SIMULATION *physics_sim;
extern SIMULATION *combat_sim;
extern SIMULATION *render_sim;
extern SIMULATION *event_sim;

extern PLAYER st_player;
extern SHIP player_ship;

// Buffer of wrapper structs
extern SOBJ *object_wrappers;
extern size_t num_wrappers;
extern size_t wrapper_buff_size;

// Currently active enemies
extern ST_ENEMY *st_enemies;
extern SHIP *sp_enemies;
extern size_t num_enemies;
extern size_t enemy_buff_len;

// Currently active projectiles
extern PROJ* projectiles;
extern size_t num_projectiles;
extern size_t proj_buff_len;

// Currently active pick-upable items
extern ST_ITEM* items;
extern size_t num_items;
extern size_t item_buff_len;

// Currently active obstacles
extern ST_OBSTACLE* st_obs;
extern SP_OBSTACLE* sp_obs;
extern size_t num_obstacles;
extern size_t obs_buff_len;

// Currently active station corridors
extern CORRIDOR *cd_obs;
extern size_t num_corridors;
extern size_t corridor_buff_len;
extern int maze_size;

#endif
