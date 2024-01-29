#ifndef __OBSTACLE_STR_H__
#define __OBSTACLE_STR_H__

/*                            OBSTACLE_STR.H

  Represents an obstacle in either space or station mode, such as an asteroid,
  box for cover, etc...

  *NOTE: These structs will have to get filled out as obstacles are fleshed out
  Right now, they are simply wrappers for entity data, since obstacles really
  only need to exist in the simulation

*/

typedef struct space_obstacle {
  ENTITY *ent;
  // Offset of respective wrapper in the object_wrapper buffer
  size_t wrapper_offset;
} SP_OBSTACLE;

typedef struct station_obstacle {
  ENTITY *ent;
  // Offset of respective wrapper in the object_wrapper buffer
  size_t wrapper_offset;
} ST_OBSTACLE;

#endif
