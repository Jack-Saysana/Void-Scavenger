#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void reset_physics(ENTITY *);

int init_enemy_buffer();
int init_enemy_ship_buffer();

void free_enemy_buffer();
void free_enemy_ship_buffer();

int player_insert_sim();
int player_ship_insert_sim();

size_t init_enemy_ship(size_t);
int sp_enemy_insert_sim(size_t);

void delete_enemy(size_t);
void st_enemy_remove_sim(size_t);

void delete_enemy_ship(size_t);
void sp_enemy_remove_sim(size_t);

void delete_projectile(size_t);
void projectile_remove_sim(size_t);

ENTITY *init_test_ent();
