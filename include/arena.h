#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cglm/cglm.h>
#include <const.h>
#include <global_vars.h>

/* ======================== INTERNALLY DEFINED FUNCTIONS ================== */

/* ======================== EXTERNALLY DEFINED FUNCTIONS ================== */
int double_buffer(void **, size_t *, size_t);
ENTITY *init_arena_ent(size_t);
size_t init_wrapper(SOBJ_T, ENTITY *, void *);
void delete_wrapper(size_t);

