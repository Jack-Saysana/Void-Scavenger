#pragma once

typedef struct station_neighbors {
  size_t index;
  /* 0 for CORRIDOR type, 1 for ARENA type, -1 for invalid */
  int type;
} STATION_NEIGHBORS;
