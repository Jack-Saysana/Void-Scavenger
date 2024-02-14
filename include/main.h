#include <GLFW/glfw3.h>
#include <engine/engine.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void render_scene(GLFWwindow *);
int init_game();
void cleanup_game();
void keyboard_input(GLFWwindow *);
void decrement_current_timer(float);

void handle_collisions();
void enemy_behavior();
int delete_stale_objects();
void refresh_objects();
