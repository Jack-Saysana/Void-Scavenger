#ifndef __OBJ_WRAPPER_STR_H__
#define __OBJ_WRAPPER_STR_H__

/*                               OBJ_WRAPPER_STR.H

  Defines a wrapper for objects which are linked to ENTITYs. Needed so that the
  types of different objects can be properly categorized when working with
  differently typed entities, such as during collision detection.

*/

typedef enum simulation_obj_type {
  PLAYER_OBJ,
  PLAYER_SHIP_OBJ,
  ENEMY_OBJ,
  ENEMY_SHIP_OBJ,
  PROJ_OBJ,
  ITEM_OBJ,
  OBSTACLE_OBJ,
  CORRIDOR_OBJ,
  DEAD_ZONE_OBJ,
  STATION_OBJ,
  TERMINAL_OBJ,
  ARENA_OBJ,
} SOBJ_T;

typedef struct {
  // Entity who points to this object wrapper
  ENTITY *entity;
  // Pointer (or offset) leading to linked game object (player, enemy, etc...)
  void *data;
  SOBJ_T type;
  // Flag indicating whether the wrapper, its entity and its game object should
  // be deleted at the end of the frame
  int to_delete;
  // Flag indicating whether the entity attached to the wrapper should be have
  // its state refreshed in the various game simulations
  int to_refresh;
} SOBJ;

#endif
