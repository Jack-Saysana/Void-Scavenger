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
  if (first_mouse_move) {
    /* accounts for when mouse has not been moved yet*/
    prev_mouse_pos[0] = x_pos;
    prev_mouse_pos[1] = y_pos;
  }
  vec2 mouse_dif;
  mouse_dif[0] = x_pos - prev_mouse_pos[0];
  mouse_dif[1] = y_pos - prev_mouse_pos[1];
  glm_vec2_scale(mouse_dif, mouse_sens, mouse_dif);
  camera.pitch += mouse_dif[1];
  if (camera.pitch > 89) {
    camera.pitch = 89;
  } else if (camera.pitch < -89) {
    camera.pitch = -89;
  }
  camera.yaw += mouse_dif[0];
  if (camera.yaw > 360 || camera.yaw < -360) {
    camera.yaw = (int)(camera.yaw) % 360;
  }
  prev_mouse_pos[0] = x_pos;
  prev_mouse_pos[1] = y_pos;
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
  if (console_enabled) {
    update_cursor_enabledness(); 
  }
  for (int i = GLFW_KEY_A; i <= GLFW_KEY_Z; i++) {
    if (glfwGetKey(window, i) == GLFW_PRESS) {
      if (console_enabled && cons_cmd_len < MAX_CMD_LEN - 1 && !holding_alpha[i - GLFW_KEY_A]) {
        cons_cmd[cons_cmd_len++] = i + 32;
        update_console_text(cons_cmd);
        advance_cursor();
      } else if (!console_enabled && mode == STATION) {
        /* FPS movment */
        if (i == GLFW_KEY_W) {
          /* Handle W press */
          move_camera(&camera, MOVE_FORWARD);
        } else if (i == GLFW_KEY_S) {
          /* Handle S press */
          move_camera(&camera, MOVE_BACKWARD);
        } else if (i == GLFW_KEY_A) {
          /* Handle A press */
          move_camera(&camera, MOVE_LEFT);
        } else if (i == GLFW_KEY_D) {
          /* Handle D press */
          move_camera(&camera, MOVE_RIGHT);
        } else if (i == GLFW_KEY_I && !holding_alpha[i - GLFW_KEY_A]) {
          /* Handle I press */
          toggle_inventory();
        }
      } else if (!console_enabled && mode == SPACE) {
        /* TODO Ship movment */
        if (i == GLFW_KEY_W) {
          /* Handle W press */
          move_camera(&camera, MOVE_FORWARD);
        } else if (i == GLFW_KEY_S){
          /* Handle S press */
          move_camera(&camera, MOVE_BACKWARD);
        } else if (i == GLFW_KEY_A){
          /* Handle A press */
          move_camera(&camera, MOVE_LEFT);
        } else if (i == GLFW_KEY_D){
          /* Handle D press */
          move_camera(&camera, MOVE_RIGHT);
        }  else if (i == GLFW_KEY_P) {
          /* Handle P press (Ship Parts at Space Mode) */
          toggle_ship_parts();
        }
      }
      holding_alpha[i - GLFW_KEY_A] = 1;
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
        advance_cursor();
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
      advance_cursor();
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
      advance_cursor();
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
      advance_cursor();
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
      cons_cursor_pos = 0;
      for (int i = 0; i < 100; i++) {
        cons_cmd[i] = '\0';
      }
      cons_cursor[0] = '_';
      for (int i = 1; i < 101; i++) {
        cons_cursor[i] = '\0';
      }
      update_console_text(cons_cmd);
      update_console_cursor(cons_cursor);
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
      advance_cursor();
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
      retreat_cursor();
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
      cons_cursor_pos = 0;
      for (int i = 0; i < 100; i++) {
        cons_cmd[i] = '\0';
      }
      cons_cursor[0] = '_';
      for (int i = 1; i < 101; i++) {
        cons_cursor[i] = '\0';
      }
      update_console_text(cons_cmd);
      update_console_cursor(cons_cursor);
    }
  } else if (glfwGetKey(window, GLFW_KEY_SLASH) != GLFW_PRESS) { 
    holding_slash = 0;
  }
}

void advance_cursor() {
  if (cons_cursor_pos <= 100) {
    cons_cursor[cons_cursor_pos++] = ' ';
    cons_cursor[cons_cursor_pos] = '_';
    update_console_cursor(cons_cursor);
  }
}

void retreat_cursor() {
  if (cons_cursor_pos >= 1) {
    cons_cursor[cons_cursor_pos] = '\0';
    cons_cursor[--cons_cursor_pos] = '_';
    update_console_cursor(cons_cursor);
  }
}

void update_cursor_enabledness() {
  if (cons_cursor_enabled) {
    /* Set timer to disable cursor */
    add_timer(0.25, (void *) (disable_console_cursor), -1000); 
  } else {
    /* Set timer to enable cursor */
    add_timer(0.25,(void *) (enable_console_cursor), -1000); 
  }
}
