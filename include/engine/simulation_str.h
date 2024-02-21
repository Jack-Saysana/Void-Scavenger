#ifndef __ENGINE_SIMULATION_STR_H__
#define __ENGINE_SIMULATION_STR_H__

#include "./oct_tree_str.h"
#include "./entity_str.h"

typedef struct simulation_collider {
  ENTITY *entity;
  size_t collider_offset;
  size_t index;
  int status;
} SIM_COLLIDER;

typedef struct simulation {
  // Oct tree used for collision detection
  OCT_TREE *oct_tree;
  // Hash-map of moving colliders
  SIM_COLLIDER *moving_ledger;
  // Hash-map of colliders which "drive" movement
  SIM_COLLIDER *driving_ledger;
  // List corresponding to moving ledger used for linear traversal
  size_t *m_list;
  // List corresponding to driving ledger used for linear traversal
  size_t *d_list;

  size_t num_moving;
  size_t m_ledger_size;
  size_t m_list_size;
  size_t num_driving;
  size_t d_ledger_size;
  size_t d_list_size;

  // Magnitude of net acceleration caused by external forces
  vec3 forces;
} SIMULATION;

typedef struct collision_list {
  ENTITY *a_ent;
  ENTITY *b_ent;
  size_t a_offset;
  size_t b_offset;
  COLLIDER a_world_col;
  COLLIDER b_world_col;
  vec3 col_dir;
  vec3 col_point;
} COLLISION;

typedef struct collision_args {
  ENTITY *entity;
  vec3 *velocity;
  vec3 *ang_velocity;
  mat4 inv_inertia;
  versor rotation;
  vec3 center_of_mass;
  float inv_mass;
  int type;
} COL_ARGS;

#endif
