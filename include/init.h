#include <global_vars.h>
#include <const.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

int init_scene();
int init_controls();
int init_wrapper_buffer();
int init_player();
int init_player_ship();
int init_projectile_buffer();
int init_space_mode();
int init_station_mode();
void barebones_ui_init();
void init_ui_components();
int init_timer_queue();
void free_timer_queue();
void clear_models();

void cleanup_gl();
void cleanup_scene();
void free_wrapper_buffer();
void free_player();
void free_player_ship();
void free_projectile_buffer();
void free_enemy_buffer();
void free_enemy_ship_buffer();
void free_space_obstacle_buffer();
void free_station_obstacle_buffer();
void free_corridor_buffer();
