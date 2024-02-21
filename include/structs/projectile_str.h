#ifndef __PROJECTILE_STR_H__
#define __PROJECTILE_STR_H__

#include <structs/ship_str.h>

/*                              PROJECTILE_STR.H

  Represents a projectile either in space or station mode

*/

typedef enum projectile_source {
  SRC_ENEMY,
  SRC_PLAYER
} PROJ_SOURCE;

typedef struct projectile {
  ENTITY *ent;
  // Offset of respective wrapper in the object_wrapper buffer
  size_t wrapper_offset;

  PROJ_SOURCE source;
  S_WEAPON_T type;
  float damage;
  // Max distance the projectile can continue to travel before despawning
  float range;
  // Flag denoting if projectile is currently in its collision animation
  int collision;
} PROJ;

#endif
