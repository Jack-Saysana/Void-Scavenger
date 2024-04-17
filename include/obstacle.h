#include <stdio.h>
#include <pthread.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

#define AMOUNT_MOVE_TOWARDS_ORIGIN (10.0)

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

int space_obstacle_insert_sim(size_t);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

ENTITY *init_obstacle_ent();
ENTITY *init_station_obstacle_ent(size_t);

size_t init_wrapper(SOBJ_T, ENTITY *, void *);
void delete_wrapper(size_t);

/* Generation of asteroid positioning, speed, dir, etc... */
int gen_rand_int(int);
void gen_rand_vec3(vec3 *, float);
void gen_rand_vec4(vec4 *, float);
float gen_rand_float(float);

void add_timer(float, void *, int);
