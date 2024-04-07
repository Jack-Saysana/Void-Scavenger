#pragma once

typedef struct station_neighbors {
  size_t index;
  /* 0 for CORRIDOR type, 1 for ARENA type */
  int type;
} STATION_NEIGHBORS;
