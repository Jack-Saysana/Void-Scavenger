#include <stdio.h>
#include <string.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

size_t init_wrapper(SOBJ_T, ENTITY *, void *);
void delete_wrapper(size_t);

ENTITY *init_alien_ent(size_t);
ENTITY *init_alien_ship_ent(size_t);
