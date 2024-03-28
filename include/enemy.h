#include <stdio.h>
#include <string.h>
#include <cglm/cglm.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void st_enemy_walk_cycle(void *);
void st_enemy_hurt_anim(void *);
void sp_enemy_shield_dmg(void *);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

size_t init_wrapper(SOBJ_T, ENTITY *, void *);
void delete_wrapper(size_t);

ENTITY *init_alien_ent(size_t);
ENTITY *init_alien_ship_ent(size_t);

void update_timer_memory(void *, void *);
int add_timer(float, void *, int, void *);
void update_timer_args(void *, void *, void *);

size_t get_target_ship_index();
void set_target_ship_index(size_t);

void sp_enemy_pathfind(size_t);
void st_enemy_pathfind(size_t);

int gen_rand_int(int);
void ship_shield_recharge_delay(void *);
void recharge_ship_shield(SHIP *);
