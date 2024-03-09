#pragma once

#include <structs/ship_str.h>

/*
              STATION_SHIP_PART_STR.H
    Handles the ship parts which spawn on the
    space station when in station mode. Additional
    fields may be filled with more information
    as this matures.
*/

typedef struct station_ship_part {
  ENTITY *ent;
  // Offset of respective wrapper in the object_wrapper buffer
  size_t wrapper_offset;
  /* Denoted using the constants from const.h */
  int type;
  int rarity;
  union {
    S_REACTOR reactor;
    S_HULL hull;
    S_SHIELD shield;
    S_WEAPON weapon;
    S_WING wing;
    S_THRUSTER thruster;
  } enhancements;
} ST_SP;
