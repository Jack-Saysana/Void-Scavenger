#ifndef __CORRIDOR_STR_H__
#define __CORRIDOR_STR_H__

typedef struct corridor {
  ENTITY *ent;
  // Offset of respective wrapper in the object_wrapper buffer
  size_t wrapper_offset;
  size_t neighbors[8];
} CORRIDOR;

#endif
