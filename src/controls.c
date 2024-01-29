#include <controls.h>

/*                             CONTROLS.C

  Contains the mouse and keyboard input handlers for handling player controls
  related to movement, camera view, and typing
*/

// ============================== INITIALIZATION =============================

int init_controls() {
  int status = register_fb_size_callback(fb_size_callback);
  if (status) {
    return -1;
  }

  status = register_mouse_movement_callback(mouse_pos_callback);
  if (status) {
    return -1;
  }

  status = register_scroll_callback(mouse_scroll_callback);
  if (status) {
    return -1;
  }

  status = register_mouse_button_callback(mouse_button_callback);
  if (status) {
    return -1;
  }

  return 0;
}

// ================================= HANDLERS ================================

void keyboard_input(GLFWwindow *window) {
  // Insert keyboard handlers here...
}

void fb_size_callback(GLFWwindow *window, int res_x, int res_y) {
  // Update perspective matrices so render scaling remains consistent with
  // screen resolution
  update_perspective();
}

void mouse_pos_callback(GLFWwindow *window, double x_pos, double y_pos) {
  // Insert mouse handling here...
}

void mouse_scroll_callback(GLFWwindow *window, double x_off, double y_off) {
  // Insert mouse scroll handling here...
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
  // Insert mouse button handling here...
}
