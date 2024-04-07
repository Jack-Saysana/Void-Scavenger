#ifndef __CORRIDOR_STR_H__
#define __CORRIDOR_STR_H__

#include <structs/station_neighbors.h>

typedef struct corridor {
  ENTITY *ent;
  // Offset of respective wrapper in the object_wrapper buffer
  size_t wrapper_offset;
  STATION_NEIGHBORS neighbors[4];
} CORRIDOR;

#endif
