#ifndef __OCT_TREE_STR_H__
#define __OCT_TREE_STR_H__

#include "./entity_str.h"

typedef enum {
  X_Y_Z = 0,
  X_Y_negZ = 1,
  X_negY_Z = 2,
  X_negY_negZ = 3,
  negX_Y_Z = 4,
  negX_Y_negZ = 5,
  negX_negY_Z = 6,
  negX_negY_negZ = 7,
  MULTIPLE = -1
} OCTANT;

typedef struct physics_object {
  //COLLIDER add_state;
  ENTITY *entity;
  size_t collider_offset;
  // Index of
  size_t node_offset;
  // Index of next PHYS_OBJ residing in the same node in data_buffer
  size_t next_offset;
  // Index of prev PHYS_OBJ residing in the same node in data_buffer
  size_t prev_offset;
  //int birthmark;
} PHYS_OBJ;

typedef struct oct_tree_node {
  // Index of first PHYS_OBJ residing at the current node in data-buffer
  size_t head_offset;
  // Index of last PHYS_OBJ residing at the current node in data_buffer
  size_t tail_offset;
  // Index of first child node in node_buffer. Other 7 children follow
  // immediately after
  //int next_offset;
  size_t next_offset;
  int empty;
} OCT_NODE;

typedef struct oct_tree {
  OCT_NODE *node_buffer;
  PHYS_OBJ *data_buffer;
  size_t node_buff_len;
  size_t node_buff_size;
  size_t data_buff_len;
  size_t data_buff_size;
//  unsigned int type;
  float max_extent;
  unsigned int max_depth;
} OCT_TREE;

typedef struct collision_result {
  PHYS_OBJ **list;
  size_t list_len;
  size_t list_buff_size;
} COLLISION_RES;

#endif
