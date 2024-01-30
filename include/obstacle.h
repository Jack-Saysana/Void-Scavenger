#include <stdio.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

ENTITY *init_obstacle_ent();

size_t init_wrapper(SOBJ_T, ENTITY *, void *);
void delete_wrapper(size_t);
