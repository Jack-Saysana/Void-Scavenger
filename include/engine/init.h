#ifndef __ENGINE_INIT_H__
#define __ENGINE_INIT_H__

#include <GLFW/glfw3.h>

GLFWwindow *init_gl(char *);
void cleanup_gl();
int register_fb_size_callback(void (*)(GLFWwindow *, int, int));
int register_mouse_movement_callback(void (*)(GLFWwindow *, double, double));
int register_scroll_callback(void (*)(GLFWwindow *, double, double));
int register_mouse_button_callback(void (*)(GLFWwindow *, int, int, int));

#endif
