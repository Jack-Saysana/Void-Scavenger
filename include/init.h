#include <global_vars.h>
#include <const.h>
#include <time.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

int init_scene();
int init_controls();
int init_wrapper_buffer();
int init_player();
int init_player_ship();
int init_projectile_buffer();
void barebones_ui_init();
void init_ui_components();
int init_timer_queue();
void free_timer_queue();
void clear_models();
int init_station_ship_parts_buffer();
int init_audio();
void exit_audio();
void load_audio_tracks();

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
void free_timer_queue();
void free_station_ship_parts_buffer();
