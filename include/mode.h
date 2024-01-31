#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>


// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void spawn_asteroids();
void spawn_space_debris();

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void reset_physics(ENTITY *);

int init_enemy_buffer();
int init_enemy_ship_buffer();

void free_enemy_buffer();
void free_enemy_ship_buffer();

int player_insert_sim();
int player_ship_insert_sim();

int init_space_obstacle_buffer();
int init_station_obstacle_buffer();
void free_space_obstacle_buffer();
void free_station_obstacle_buffer();
size_t init_space_obstacle(int, vec3, vec3, vec3, vec3);
size_t init_station_obstacle(vec3, vec3);
int space_obstacle_insert_sim(size_t);

void gen_rand_vec3(vec3 *, float);
void seed_random();

