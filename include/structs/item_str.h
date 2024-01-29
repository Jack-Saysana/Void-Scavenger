#ifndef __ITEM_STR_H__
#define __ITEM_STR_H__

#include <structs/ship_str.h>

/*                              ITEM_STR.H

  Represents a pick-up-able item in station mode

*/

typedef enum part_type {
  PART_REACTOR,
  PART_HULL,
  PART_SHIELD,
  PART_WEAPON,
  PART_WING,
  PART_THRUSTER
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
  } data;
  PART_T type;
} ST_ITEM;

#endif
