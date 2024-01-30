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
  input_keys(window);
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

void input_keys(GLFWwindow *window) {
  /* Letters */
  int console_enabled = is_console_enabled();
  for (int i = GLFW_KEY_A; i <= GLFW_KEY_Z; i++) {
    if (glfwGetKey(window, i) == GLFW_PRESS && !holding_alpha[i - GLFW_KEY_A]) {
      holding_alpha[i - GLFW_KEY_A] = 1;
      if (console_enabled && cons_cmd_len < MAX_CMD_LEN - 1) {
        cons_cmd[cons_cmd_len++] = i + 32;
        update_console_text(cons_cmd);
        /* TODO: handle console cursor */
      }
    } else if (glfwGetKey(window, i) != GLFW_PRESS) {
      holding_alpha[i - GLFW_KEY_A] = 0;
    }
  }

  /* Numbers */
    for (int i = GLFW_KEY_0; i <= GLFW_KEY_9; i++) {
    if (glfwGetKey(window, i) == GLFW_PRESS && !holding_num[i - GLFW_KEY_0]) {
      holding_num[i - GLFW_KEY_0] = 1;
      if (console_enabled && cons_cmd_len < MAX_CMD_LEN - 1) {
        cons_cmd[cons_cmd_len++] = i;
        update_console_text(cons_cmd);
        /* TODO: handle console cursor */
      }
    } else if (glfwGetKey(window, i) != GLFW_PRESS) {
      holding_num[i - GLFW_KEY_0] = 0;
    }
  }

  /* Special Characters */
  /* Minus */
  if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS &&
      !holding_shift && !holding_minus) {
    holding_minus = 1;
    if (console_enabled && cons_cmd_len < MAX_CMD_LEN - 1) {
      cons_cmd[cons_cmd_len++] = '-';
      update_console_text(cons_cmd);
      /* TODO: handle console cursor */
    }
  } else if (glfwGetKey(window, GLFW_KEY_MINUS) != GLFW_PRESS &&
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS &&
      glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) != GLFW_PRESS)
      && holding_minus) {
    holding_minus = 0;
  }

  /* Space */
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !holding_space) {
    holding_space = 1;
    if (console_enabled && cons_cmd_len < MAX_CMD_LEN - 1) {
      cons_cmd[cons_cmd_len++] = ' ';
      update_console_text(cons_cmd);
      /* TODO: handle console cursor */
    }
  } else if (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS) {
    holding_space = 0;
  }

  /* Underscore */
  if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS && holding_shift &&
      !holding_underscore) {
    holding_underscore = 1;
    if (console_enabled && cons_cmd_len < MAX_CMD_LEN - 1) {
      cons_cmd[cons_cmd_len++] = '_';
      update_console_text(cons_cmd);
      /* TODO: handle console cursor */
    }
  } else if (glfwGetKey(window, GLFW_KEY_MINUS) != GLFW_PRESS &&
      (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS ||
      glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) != GLFW_PRESS) &&
      holding_underscore) {
    holding_underscore = 0;
  }

  /* Enter */
  if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && !holding_enter) {
    holding_enter = 1;
    if (console_enabled) {
      cons_cmd[cons_cmd_len++] = '\0';
      /* Call lexer to tokenize and parse the command */
      tokenize(cons_cmd, cons_cmd_len);
      /* Reset for the next command */
      cons_cmd_len = 0;
      for (int i = 0; i < 100; i++) {
        cons_cmd[i] = '\0';
      }
      update_console_text(cons_cmd);
    }
  } else if (glfwGetKey(window, GLFW_KEY_ENTER) != GLFW_PRESS) {
    holding_enter = 0;
  }

  /* Period / Dot */
  if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS && !holding_dot) {
    holding_dot = 1;
    if (console_enabled && cons_cmd_len < MAX_CMD_LEN - 1) {
      cons_cmd[cons_cmd_len++] = '.';
      update_console_text(cons_cmd);
      /* TODO: handle console cursor */
    }
  } else if (glfwGetKey(window, GLFW_KEY_PERIOD) != GLFW_PRESS) {
    holding_dot = 0;
  }

  /* Backspace */
  if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS && !holding_backspace) {
    holding_backspace = 1;
    if (console_enabled && cons_cmd_len > 0) {
      cons_cmd[--cons_cmd_len] = '\0';
      update_console_text(cons_cmd);
      /* TODO: handle console cursor */
    }
  } else if (glfwGetKey(window, GLFW_KEY_BACKSPACE) != GLFW_PRESS) {
    holding_backspace = 0;
  }

  /* Slash */
  if (glfwGetKey(window, GLFW_KEY_SLASH) == GLFW_PRESS && !holding_slash) {
    holding_slash = 1;
    if (console_enabled) {
      disable_console();
    } else {
      enable_console();
      cons_cmd_len = 0;
      for (int i = 0; i < 100; i++) {
        cons_cmd[i] = '\0';
      }
      update_console_text(cons_cmd);
    }
  } else if (glfwGetKey(window, GLFW_KEY_SLASH) != GLFW_PRESS) { 
    holding_slash = 0;
  }
}
