#include <engine/engine.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

int init_scene();
int init_controls();
int init_wrapper_buffer();
int init_player();
int init_player_ship();
int init_projectile_buffer();
int init_space_mode();
void init_ui_components();

void cleanup_gl();
void cleanup_scene();
void free_wrapper_buffer();
void free_player();
void free_player_ship();
void free_projectile_buffer();
