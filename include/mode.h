#include <stdio.h>
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

size_t init_enemy_ship(size_t);
int sp_enemy_insert_sim(size_t);

void delete_enemy(size_t);
void st_enemy_remove_sim(size_t);

void delete_enemy_ship(size_t);
void sp_enemy_remove_sim(size_t);

void delete_projectile(size_t);
void projectile_remove_sim(size_t);

/* Obstacles for station and space mode */
int init_space_obstacle_buffer();
int init_station_obstacle_buffer();
void free_space_obstacle_buffer();
void free_station_obstacle_buffer();
size_t init_space_obstacle(int, vec3, vec3, vec3, vec3, float);
size_t init_station_obstacle(vec3, vec3, float);
int space_obstacle_insert_sim(size_t);

/* Corridors for the station itself */
int init_corridor_buffer();

/* Generation of asteroid positioning, speed, dir, etc... */
void gen_rand_vec3(vec3 *, float);
float gen_rand_float(float);
void seed_random();

void disable_coordinates();
void enable_coordinates();
