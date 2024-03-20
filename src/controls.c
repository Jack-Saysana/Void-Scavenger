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
  if (keyboard_enabled) {
    input_keys(window);
  }
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
  if (!CURSOR_ENABLED && mode == STATION) {
    /* updates pitch and yaw of camera */
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
    vec3 player_up;
    glm_quat_rotatev(st_player.ent->rotation, (vec3){0.0, 1.0, 0.0}, player_up);
    mat4 rotation = GLM_MAT4_IDENTITY_INIT;
    glm_rotate(rotation, glm_rad(-mouse_dif[0]), player_up);
    versor rot_quat = GLM_QUAT_IDENTITY_INIT;
    glm_mat4_quat(rotation, rot_quat);
    glm_quat_mul(rot_quat, st_player.ent->rotation, st_player.ent->rotation);
  } else if (!CURSOR_ENABLED && mode == SPACE) {
    /* rotates the ships pitch and yaw*/
    mat4 rotation = GLM_MAT4_IDENTITY_INIT;
    vec3 ship_up;
    vec3 ship_side;
    glm_quat_rotatev(player_ship.ent->rotation, (vec3){0.0, 1.0, 0.0}, ship_up);
    glm_quat_rotatev(player_ship.ent->rotation, (vec3){0.0, 0.0, 1.0}, ship_side);
    glm_rotate(rotation, glm_rad(5.0 * -mouse_dif[1] * DELTA_TIME), ship_side);
    glm_rotate(rotation, glm_rad(5.0 * -mouse_dif[0] * DELTA_TIME), ship_up);
    versor rot_quat = GLM_QUAT_IDENTITY_INIT;
    glm_mat4_quat(rotation, rot_quat);
    glm_quat_mul(rot_quat, player_ship.ent->rotation, player_ship.ent->rotation);
  }
  prev_mouse_pos[0] = x_pos;
  prev_mouse_pos[1] = y_pos;
}

void mouse_scroll_callback(GLFWwindow *window, double x_off, double y_off) {
  // Insert mouse scroll handling here...
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
  if (CURSOR_ENABLED) {
    return;
  }
  // Insert mouse button handling here...
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    if (mode == STATION) {
      if(can_shoot) {
        /* firerate timer */
        can_shoot = 0;
        add_timer(st_player.fire_rate, (void *) &can_shoot, 1, NULL);
        /* forward vector from player*/
        vec3 forward;
        mat4 inv_cam = GLM_MAT4_IDENTITY_INIT;
        glm_mat4_inv(camera.view, inv_cam);
        forward[0] = inv_cam[2][0];
        forward[1] = inv_cam[2][1];
        forward[2] = inv_cam[2][2];
        glm_vec3_normalize(forward);
        glm_vec3_negate(forward);
        /* spawns projectile*/
        size_t proj_index = init_projectile(camera.pos,
                                            forward,
                                            10.0 + st_player.speed,
                                            SRC_PLAYER,
                                            player_ship.weapon.type,
                                            player_ship.weapon.damage,
                                            player_ship.weapon.range,
                                            1);
        projectile_insert_sim(proj_index);
      }
    } else if (mode == SPACE) {
      if (can_shoot) {
        /* fire rate timer */
        can_shoot = 0;
        add_timer(player_ship.weapon.fire_rate, (void *) &can_shoot, 1, NULL);
        /* get ship vectors */
        vec3 ship_forward;
        glm_quat_rotatev(player_ship.ent->rotation, (vec3){-1.0, 0.0, 0.0}, ship_forward);
        glm_normalize(ship_forward);
        vec3 ship_side;
        glm_quat_rotatev(player_ship.ent->rotation, (vec3){0.0, 0.0, 1.0}, ship_side);
        glm_normalize(ship_side);
        vec3 ship_up;
        glm_quat_rotatev(player_ship.ent->rotation, (vec3){0.0, 1.0, 0.0}, ship_up);
        glm_normalize(ship_up);
        /* rotate left gun to converage */
        glm_vec3_rotate(ship_forward, glm_rad(-5.0), ship_side);
        glm_vec3_rotate(ship_forward, glm_rad(-0.625), ship_up);
        /* get left gun offset pos */
        vec3 gun_pos = GLM_VEC3_ZERO_INIT;
        glm_vec3_scale_as(ship_forward, 7.0, gun_pos);
        glm_vec3_add(player_ship.ent->translation, gun_pos, gun_pos);
        glm_vec3_add(gun_pos, ship_side, gun_pos);
        /* spawn left projectile*/
        size_t proj_index = init_projectile(gun_pos,
                                            ship_forward,
                                            player_ship.weapon.proj_speed +
                                            player_ship.cur_speed,
                                            SRC_PLAYER,
                                            player_ship.weapon.type,
                                            player_ship.weapon.damage,
                                            player_ship.weapon.range,
                                            0);
        projectile_insert_sim(proj_index);
        /* get right gun offset pos */
        glm_vec3_negate(ship_side);
        glm_vec3_scale_as(ship_forward, 7.0, gun_pos);
        glm_vec3_add(player_ship.ent->translation, gun_pos, gun_pos);
        glm_vec3_add(gun_pos, ship_side, gun_pos);
        /* rotate right gun to converage */
        glm_vec3_rotate(ship_forward, glm_rad(1.25), ship_up);
        /* spawn right projectile*/
        proj_index = init_projectile(gun_pos,
                                     ship_forward,
                                     player_ship.weapon.proj_speed +
                                     player_ship.cur_speed,
                                     SRC_PLAYER,
                                     player_ship.weapon.type,
                                     player_ship.weapon.damage,
                                     player_ship.weapon.range,
                                     0);
        projectile_insert_sim(proj_index);
      }
    }
  }
}

void input_keys(GLFWwindow *window) {
  /* Letters */
  st_player.ent->velocity[X] = 0;
  st_player.ent->velocity[Z] = 0;
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
          //move_camera(&camera, MOVE_FORWARD);
          vec3 player_forward;
          glm_quat_rotatev(st_player.ent->rotation, (vec3){-1.0, 0.0, 0.0}, player_forward);
          glm_normalize(player_forward);
          glm_vec3_scale(player_forward, st_player.speed, player_forward);
          glm_vec3_add(player_forward, st_player.ent->velocity,
                       st_player.ent->velocity);
        }
        if (i == GLFW_KEY_S) {
          /* Handle S press */
          // move_camera(&camera, MOVE_BACKWARD);
          vec3 player_forward;
          glm_quat_rotatev(st_player.ent->rotation, (vec3){-1.0, 0.0, 0.0}, player_forward);
          glm_normalize(player_forward);
          glm_vec3_scale(player_forward, st_player.speed, player_forward);
          glm_vec3_negate(player_forward);
          glm_vec3_add(player_forward, st_player.ent->velocity,
                       st_player.ent->velocity);
        }
        if (i == GLFW_KEY_A) {
          /* Handle A press */
          // move_camera(&camera, MOVE_LEFT);
          vec3 player_left;
          glm_quat_rotatev(st_player.ent->rotation, (vec3){0.0, 0.0, 1.0},
                            player_left);
          glm_normalize(player_left);
          glm_vec3_scale(player_left, st_player.speed, player_left);
          glm_vec3_add(player_left, st_player.ent->velocity,
                       st_player.ent->velocity);
        }
        if (i == GLFW_KEY_D) {
          /* Handle D press */
          // move_camera(&camera, MOVE_RIGHT);
          vec3 player_left;
          glm_quat_rotatev(st_player.ent->rotation, (vec3){0.0, 0.0, 1.0},
                            player_left);
          glm_normalize(player_left);
          glm_vec3_scale(player_left, st_player.speed, player_left);
          glm_vec3_negate(player_left);
          glm_vec3_add(player_left, st_player.ent->velocity,
                       st_player.ent->velocity);
        }
        if (i == GLFW_KEY_I && !holding_alpha[i - GLFW_KEY_A]) {
          /* Handle I press */
          toggle_inventory();
        }
        if (i == GLFW_KEY_K && !holding_alpha[i - GLFW_KEY_A]) {
          /* Handle K press */
          toggle_skill_tree();
        }
        if (i == GLFW_KEY_E && get_terminal_ui_state() &&
                   !holding_alpha[i - GLFW_KEY_A]) {
          set_gamemode_space();
          st_player.total_levels_completed++;
        }
      } else if (!console_enabled && mode == SPACE) {
        if (i == GLFW_KEY_W) {
          /* Handle W press */
          /* increases curent speed of player ship up to max_vel */
          if (player_ship.cur_speed >= player_ship.thruster.max_vel) {
            player_ship.cur_speed = player_ship.thruster.max_vel;
          } else {
            player_ship.cur_speed += DELTA_TIME * player_ship.thruster.max_accel;
          }
        } else if (i == GLFW_KEY_S){
          /* Handle S press */
          /* decreases curent speed of player ship down to 0 */
          if (player_ship.cur_speed <= 0 ) {
            player_ship.cur_speed = 0;
          } else {
            player_ship.cur_speed -= DELTA_TIME * player_ship.thruster.max_accel;
          }
        } else if (i == GLFW_KEY_A){
          /* Handle A press */
          /*roll left*/
          vec3 ship_forward;
          glm_quat_rotatev(player_ship.ent->rotation, (vec3){1.0, 0.0, 0.0}, ship_forward);
          mat4 rotation = GLM_MAT4_IDENTITY_INIT;
          glm_rotate(rotation, glm_rad(DELTA_TIME * 50), ship_forward);
          versor rot_quat = GLM_QUAT_IDENTITY_INIT;
          glm_mat4_quat(rotation, rot_quat);
          glm_quat_mul(rot_quat, player_ship.ent->rotation, player_ship.ent->rotation);
        } else if (i == GLFW_KEY_D){
          /* Handle D press */
          /*roll right*/
          vec3 ship_forward;
          glm_quat_rotatev(player_ship.ent->rotation, (vec3){1.0, 0.0, 0.0}, ship_forward);
          mat4 rotation = GLM_MAT4_IDENTITY_INIT;
          glm_rotate(rotation, glm_rad(-1 * DELTA_TIME * 50), ship_forward);
          versor rot_quat = GLM_QUAT_IDENTITY_INIT;
          glm_mat4_quat(rotation, rot_quat);
          glm_quat_mul(rot_quat, player_ship.ent->rotation, player_ship.ent->rotation);
        }  else if (i == GLFW_KEY_P && !holding_alpha[i - GLFW_KEY_A]) {
          /* Handle P press (Ship Parts at Space Mode) */
          toggle_ship_parts();
        } else if (i == GLFW_KEY_I && !holding_alpha[i - GLFW_KEY_A]) {
          /* Handle I press */
          toggle_inventory();
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
  if (glfwGetKey(window, GLFW_KEY_SPACE)) {
    if (console_enabled && cons_cmd_len < MAX_CMD_LEN - 1 && !holding_space) {
      cons_cmd[cons_cmd_len++] = ' ';
      update_console_text(cons_cmd);
      advance_cursor();
    }
    holding_space = 1;
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
    add_timer(0.25, (void *) (disable_console_cursor), -1000, NULL);
  } else {
    /* Set timer to enable cursor */
    add_timer(0.25,(void *) (enable_console_cursor), -1000, NULL);
  }
}

void enable_shooting() {
  can_shoot = 1;
}

void set_keyboard_enabledness(int set) {
  keyboard_enabled = set;
}
