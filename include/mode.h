#include <stdio.h>
#include <cglm/cglm.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

static ENTITY *dead_zones[6] = { NULL };

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void spawn_asteroids();
void spawn_space_debris();
int insert_dead_zones();
void clear_dead_zones();

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

size_t init_wrapper(SOBJ_T, ENTITY *, void *);
void delete_wrapper(size_t);

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

void delete_space_obstacle(size_t);
void space_obstacle_remove_sim(size_t);

void delete_station_obstacle(size_t);
void station_obstacle_remove_sim(size_t);

void refresh_wrapper(size_t);

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

// Dead zone placement
ENTITY *init_dead_zone_ent();
