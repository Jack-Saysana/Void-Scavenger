#include <stdio.h>
#include <engine/engine.h>
#include <const.h>
#include <cglm/cglm.h>
#include <global_vars.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void integrate_projectile(size_t);
void proj_collision_anim(void *);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

ENTITY *init_proj_ent(size_t);

size_t init_wrapper(SOBJ_T, ENTITY *, void *);
void delete_wrapper(size_t);

void add_timer(float, void *, int, void *);
void update_timer_args(void *, void *, void *);
