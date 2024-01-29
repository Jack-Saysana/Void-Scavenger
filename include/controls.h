#include <GLFW/glfw3.h>
#include <engine/engine.h>
#include <global_vars.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void fb_size_callback(GLFWwindow *, int, int);
void mouse_pos_callback(GLFWwindow *, double, double);
void mouse_scroll_callback(GLFWwindow *, double, double);
void mouse_button_callback(GLFWwindow *, int, int, int);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void update_perspective();
