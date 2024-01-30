#include <GLFW/glfw3.h>
#include <engine/engine.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void render_scene(GLFWwindow *);
int init_game();
void cleanup_game();
void keyboard_input(GLFWwindow *);

void handle_collisions();
