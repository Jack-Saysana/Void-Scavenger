#include <globals.h>

/*                                  GLOBALS.C

  Defines all common global variables across the game.

*/

CAM camera;

SIMULATION *space_sim = NULL;
SIMULATION *station_sim = NULL;

PLAYER st_player;
SHIP player_ship;

SOBJ *object_wrappers = NULL;
size_t num_wrappers = 0;
size_t wrapper_buff_size = 0;

ST_ENEMY *st_enemies = NULL;
SHIP *sp_enemies = NULL;
size_t num_enemies = 0;
size_t enemy_buff_len = 0;

PROJ *projectiles = NULL;
size_t num_projectiles = 0;
size_t proj_buff_len = 0;

ST_ITEM *items = NULL;
size_t num_items = 0;
size_t item_buff_len = 0;

ST_OBSTACLE *st_obs = NULL;
SP_OBSTACLE *sp_obs = NULL;
size_t num_obstacles = 0;
size_t obs_buff_len = 0;
