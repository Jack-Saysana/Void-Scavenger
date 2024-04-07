#pragma once

#include <structs/station_neighbors.h>

typedef struct arena {
  ENTITY *ent;
  // Offset of respective wrapper in the object_wrapper buffer
  size_t wrapper_offset;
  STATION_NEIGHBORS neighbors[4];
} ARENA;
