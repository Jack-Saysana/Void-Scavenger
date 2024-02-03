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
  ENV_OBJ,
  ITEM_OBJ,
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
} SOBJ;

#endif
