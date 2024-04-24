#include <stdio.h>
#include <string.h>
#include <cglm/cglm.h>
#include <pthread.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

static ENTITY *dead_zones[6] = { NULL };
static ENTITY *sp_station = NULL;
static ENTITY *st_terminal = NULL;
static int attack_types_picked[E_BASE_NUM_TYPES] = { 0, 0 };
static int mov_types_picked[E_BASE_NUM_TYPES] = { 0, 0 };

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void spawn_asteroids();
void spawn_space_debris();
int insert_dead_zones();
void clear_dead_zones();
int insert_sp_station();
void clear_sp_station();
void clear_st_terminal();

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

void spawn_sp_enemy(vec3, versor, int, int);
void delete_space_obstacle(size_t);
void space_obstacle_remove_sim(size_t);

void delete_station_obstacle(size_t);
void station_obstacle_remove_sim(size_t);

void delete_item(size_t);
void item_remove_sim(size_t);

void refresh_wrapper(size_t);

/* Obstacles for station and space mode */
int init_space_obstacle_buffer();
int init_station_obstacle_buffer();
int init_items_buffer();
void free_items_buffer();
void free_space_obstacle_buffer();
void free_station_obstacle_buffer();
size_t init_space_obstacle(int, vec3, vec3, vec3, vec3, float);
int space_obstacle_insert_sim(size_t);
void delete_space_obstacle(size_t);
void delete_station_obstacle(size_t);
void station_obstacle_remove_sim(size_t);
void station_obstacle_insert_sim(size_t);
void space_obstacle_remove_sim(size_t);

/* Corridors for the station itself */
int init_corridor_buffer();
size_t init_corridor(vec3, versor, size_t);
void delete_corridor(size_t);
void corridor_remove_sim(size_t);
int corridor_insert_sim(size_t);
void free_corridor_buffer();
int gen_rand_int(int);
float gen_rand_float(float);
void create_station_corridors();

/* Arena functions */
size_t init_arena_buffer();
void free_arena_buffer();
void arena_remove_sim(size_t);
void delete_arena(size_t);


/* Generation of asteroid positioning, speed, dir, etc... */
void gen_rand_vec3(vec3 *, float);
void gen_rand_vec3_plus_minus(vec3 *, float);
void gen_rand_vec4_plus_minus(vec3 *, float);
void gen_rand_vec4(vec4 *, float);
float gen_rand_float(float);
void seed_random();

// Dead zone placement
ENTITY *init_dead_zone_ent();

// Station placement
ENTITY *init_station_ent();

// Terminal placement
ENTITY *init_terminal_ent();

void disable_coordinates();
void enable_coordinates();

void update_perspective();
void reset_camera(CAM *);

void enable_shooting();
void set_st_waypoint_enabled(int);
void reset_dmg_ui_state();

void reset_inventory();
void reset_st_player_state();
void reset_sp_player_state();

void hide_stallwarning();

void update_level_pos();

void pause_shield_audio();
