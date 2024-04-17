#include <GLFW/glfw3.h>
#include <engine/engine.h>
#include <global_vars.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void render_scene(GLFWwindow *);
int barebones_init();
void loading_init();
void cleanup_game();
int query_loading_status();
void keyboard_input(GLFWwindow *);
void decrement_current_timer(float);
void update_ui_components();
void player_ship_thrust_move();
void handle_collisions();
void enemy_behavior();
int delete_stale_objects();
void refresh_objects();
void loading_init();
void recharge_player_shield();
void reactor_recharge();
