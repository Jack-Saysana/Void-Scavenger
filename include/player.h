#include <stdio.h>
#include <string.h>
#include <cglm/cglm.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void sp_player_shield_dmg(void *);
void reset_inventory();

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

size_t init_wrapper(SOBJ_T, ENTITY *, void *);
void delete_wrapper(size_t);

ENTITY *init_player_ent();
ENTITY *init_player_ship_ent();

int add_timer(float, void *, int, void *);
void recharge_ship_shield(SHIP *);
size_t init_projectile(vec3, vec3, float, PROJ_SOURCE, S_WEAPON_T, float,
                       float, size_t);
int projectile_insert_sim(size_t);
