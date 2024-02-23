#include <stdio.h>
#include <string.h>
#include <cglm/cglm.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void sp_enemy_pathfind(size_t);
void st_enemy_pathfind(size_t);
void st_enemy_walk_cycle(void *);
void st_enemy_hurt_anim(void *);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

size_t init_wrapper(SOBJ_T, ENTITY *, void *);
void delete_wrapper(size_t);

ENTITY *init_alien_ent(size_t);
ENTITY *init_alien_ship_ent(size_t);

void update_timer_memory(void *, void *);
int add_timer(float, void *, int, void *);
void update_timer_args(void *, void *, void *);
