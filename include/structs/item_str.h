#ifndef __ITEM_STR_H__
#define __ITEM_STR_H__

#include <structs/ship_str.h>

/*                              ITEM_STR.H

  Represents a pick-up-able item in station mode

*/

typedef enum part_type {
  PART_REACTOR           = 2,
  PART_HULL              = 1,
  PART_SHIELD            = 3,
  PART_WEAPON_BALLISTIC  = 6,
  PART_WEAPON_LASER      = 7,
  PART_WEAPON_PLASMA     = 8,
  PART_WING              = 5,
  PART_THRUSTER          = 0,
} PART_T;

typedef struct item_ent {
  // Spatial data in station mode
  ENTITY *ent;
  // Offset of respective wrapper in the object_wrapper buffer
  size_t wrapper_offset;

  union {
    S_REACTOR reactor;
    S_HULL hull;
    S_SHIELD shield;
    S_WEAPON weapon;
    S_WING wing;
    S_THRUSTER thruster;
  } enhancements;
  PART_T type;
  int rarity;
} ST_ITEM;

#endif
