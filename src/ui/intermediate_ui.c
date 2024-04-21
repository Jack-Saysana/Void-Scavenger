#include <ui/intermediate_ui.h>

/*
                                   INTERMEDIATE
Implements the functionality for defining UI components for intermediate menu.
*/

/*
  Init intermediate menu globaly, call by general_ui.c init_ui_components()

  Return
    0 if successful
    otherwise unsuccessful
*/
int init_intermediate() {
  last_terminal_state = 0;

  ui_intermediate_root = add_ui_comp(
    UI_ROOT_COMP, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_intermediate_root, "assets/transparent.png");

  ui_intermediate_background = add_ui_comp(
    ui_intermediate_root, // UI_COMP *parent
    (vec2) { 0.7, -0.03 }, // vec2 pos
    0.24, // float width
    0.3, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_intermediate_background, "assets/ui/test.png");

  /*
  ==============
    Next Level
  ==============
  */
  ui_intermediate_next_lv_background = add_ui_comp(
    ui_intermediate_background, // UI_COMP *parent
    (vec2) { -0.5, 0 }, // vec2 pos
    0.5, // float width
    0.52, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_intermediate_next_lv_background, "assets/ui/test.png");

  ui_intermediate_next_lv_text_background = add_ui_comp(
    ui_intermediate_next_lv_background, // UI_COMP *parent
    (vec2) { 0.05, -0.076923 }, // vec2 pos
    0.95, // float width
    0.3076923, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_intermediate_next_lv_text_background, "assets/ui/hud_color.png");

  ui_intermediate_next_lv_text = add_ui_comp(
    ui_intermediate_next_lv_text_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.95, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_X
  );
  set_ui_texture(ui_intermediate_next_lv_text, "assets/transparent.png");
  memset(intermediate_next_lv_buffer, '\0', INTERMEDIATE_TEXT_BUFFER_SIZE);
#ifdef __linux__
  snprintf(intermediate_next_lv_buffer, INTERMEDIATE_TEXT_BUFFER_SIZE,
           "NEXT LV [%ld]", st_player.total_levels_completed + 1);
#else
  snprintf(intermediate_next_lv_buffer, INTERMEDIATE_TEXT_BUFFER_SIZE,
           "NEXT LV [%lld]", st_player.total_levels_completed + 1);
#endif
  set_ui_text(ui_intermediate_next_lv_text,
              intermediate_next_lv_buffer, 0.16, T_LEFT, fixed_sys,
              (vec3) { 0.0, 0.0, 0.0 });

  ui_intermediate_next_lv_button_root = add_ui_comp(
    ui_intermediate_next_lv_background, // UI_COMP *parent
    (vec2) { 0.05, -0.4615383 }, // vec2 pos
    0.95, // float width
    0.46153845, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_intermediate_next_lv_button_root, "assets/transparent.png");

  ui_intermediate_next_lv_button = init_blue_button(
    ui_intermediate_next_lv_button_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_intermediate_next_lv_button, "LAUNCH", 0.32, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_intermediate_next_lv_button, (void *) launch_on_click, NULL);

  /*
  ================
    Enemy 1 Info
  ================
  */
  ui_intermediate_enemy_1_type_background = add_ui_comp(
    ui_intermediate_background, // UI_COMP *parent
    (vec2) { 0.025, -0.04 }, // vec2 pos
    0.95, // float width
    0.16, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_intermediate_enemy_1_type_background,
                 "assets/ui/hud_color.png");

  ui_intermediate_enemy_1_type_text = add_ui_comp(
    ui_intermediate_enemy_1_type_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    LINE_UNIT_RATIO_X
  );
  set_ui_texture(ui_intermediate_enemy_1_type_text, "assets/transparent.png");
  set_ui_text(ui_intermediate_enemy_1_type_text,
              "POSSIBLE ENEMY TYPES", 0.08, T_LEFT, fixed_sys,
              (vec3) { 0.0, 0.0, 0.0 });

  ui_intermediate_enemy_1_info_background = add_ui_comp(
    ui_intermediate_background, // UI_COMP *parent
    (vec2) { 0.025, -0.24 }, // vec2 pos
    0.95, // float width
    0.24, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_intermediate_enemy_1_info_background,
                 "assets/ui/hud_color_bg.png");

  ui_intermediate_enemy_1_info_text = add_ui_comp(
    ui_intermediate_enemy_1_info_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    LINE_UNIT_RATIO_X
  );
  set_ui_texture(ui_intermediate_enemy_1_info_text, "assets/transparent.png");
  memset(intermediate_enemy_1_info_buffer, '\0', INTERMEDIATE_TEXT_BUFFER_SIZE);
  snprintf(intermediate_enemy_1_info_buffer, INTERMEDIATE_TEXT_BUFFER_SIZE,
           "ENEMY HEALTH INFO\nENEMY WEAPON INFO");
  set_ui_text(ui_intermediate_enemy_1_info_text,
              intermediate_enemy_1_info_buffer, 0.08, T_LEFT, fixed_sys,
              (vec3) { 0.0, 0.0, 0.0 });

  /*
  ================
    Enemy 2 Info
  ================
  */
  ui_intermediate_enemy_2_type_background = add_ui_comp(
    ui_intermediate_background, // UI_COMP *parent
    (vec2) { 0.025, -0.52 }, // vec2 pos
    0.95, // float width
    0.16, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_intermediate_enemy_2_type_background,
                 "assets/ui/hud_color.png");

  ui_intermediate_enemy_2_type_text = add_ui_comp(
    ui_intermediate_enemy_2_type_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    LINE_UNIT_RATIO_X
  );
  set_ui_texture(ui_intermediate_enemy_2_type_text, "assets/transparent.png");
  set_ui_text(ui_intermediate_enemy_2_type_text,
              "POSSIBLE ENEMY MOVEMENT", 0.08, T_LEFT, fixed_sys,
              (vec3) { 0.0, 0.0, 0.0 });

  ui_intermediate_enemy_2_info_background = add_ui_comp(
    ui_intermediate_background, // UI_COMP *parent
    (vec2) { 0.025, -0.72 }, // vec2 pos
    0.95, // float width
    0.24, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_intermediate_enemy_2_info_background,
                 "assets/ui/hud_color_bg.png");

  ui_intermediate_enemy_2_info_text = add_ui_comp(
    ui_intermediate_enemy_2_info_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    LINE_UNIT_RATIO_X
  );
  set_ui_texture(ui_intermediate_enemy_2_info_text, "assets/transparent.png");
  memset(intermediate_enemy_2_info_buffer, '\0',
         INTERMEDIATE_TEXT_BUFFER_SIZE);
  snprintf(intermediate_enemy_2_info_buffer, INTERMEDIATE_TEXT_BUFFER_SIZE,
           "ENEMY HEALTH INFO\nENEMY WEAPON INFO");
  set_ui_text(ui_intermediate_enemy_2_info_text,
              intermediate_enemy_1_info_buffer, 0.08, T_LEFT, fixed_sys,
              (vec3) { 0.0, 0.0, 0.0 });

  set_ui_enabled(ui_intermediate_root, 0);

  return 0;
}

void open_intermediate() {
  last_terminal_state = 1;
  if (gen_sp_enemies) {
    gen_sp_enemies = 0;
    generate_sp_enemy_types();
    get_sp_enemy_type_strings(intermediate_enemy_1_info_buffer,
                              INTERMEDIATE_TEXT_BUFFER_SIZE,
                              intermediate_enemy_2_info_buffer,
                              INTERMEDIATE_TEXT_BUFFER_SIZE);
    set_ui_text(ui_intermediate_enemy_1_info_text,
                intermediate_enemy_1_info_buffer, 0.08, T_LEFT, fixed_sys,
                (vec3) { 0.0, 0.0, 0.0 });
    set_ui_text(ui_intermediate_enemy_2_info_text,
                intermediate_enemy_2_info_buffer, 0.08, T_LEFT, fixed_sys,
                (vec3) { 0.0, 0.0, 0.0 });
  }

  set_ui_enabled(ui_intermediate_root, 1);
  set_ui_pos(inventory.ui_inventory_background, (vec2) { 0.7, -0.36 });
  set_ui_width(inventory.ui_inventory_background, 0.159);
  set_ui_height(inventory.ui_inventory_background, 0.159);
  set_ui_pos(inventory.ui_inventory_info_background, (vec2) { 0.7, -0.67 });
  set_ui_enabled(ship_parts.ui_ship_parts_root, 1);
  set_ui_enabled(inventory.ui_inventory_root, 1);
  set_ui_enabled(ship_parts.ui_ship_parts_info_background, 1);
  set_ui_enabled(inventory.ui_inventory_info_background, 0);

  set_ui_enabled(ui_esc_root, 0);
  set_ui_enabled(ui_render_root, 0);
  set_ui_enabled(ui_control_root, 0);
  set_ui_enabled(skill_tree.ui_skill_tree_root, 0);

  CURSOR_ENABLED = 1;
}

void close_intermediate() {
  set_ui_enabled(ui_intermediate_root, 0);
  set_ui_enabled(ship_parts.ui_ship_parts_root, 0);
  set_ui_enabled(inventory.ui_inventory_root, 0);
  set_ui_enabled(ship_parts.ui_ship_parts_info_background, 0);
  set_ui_enabled(inventory.ui_inventory_info_background, 0);
  last_terminal_state = 0;
  CURSOR_ENABLED = 0;
}

void update_intermediate() {
  if (last_terminal_state == 1 && !get_terminal_ui_state()) {
    last_terminal_state = 0;
    close_intermediate();
  }
}

void toggle_intermediate() {
  if (ui_intermediate_root->enabled) {
    close_intermediate();
  } else {
    open_intermediate();
  }
}

void launch_on_click() {
  free_timer_queue();
  add_timer(TICK_RATE, tick, FUNCTION_PTR, NULL);
  reset_listener_orientation();
  reset_listener_pos();
  pause_audio(STATION_THEME);
  clear_station_mode();
  init_space_mode();
  play_audio(SPACE_THEME);

  st_player.total_levels_completed++;
  maze_size++;
  if (maze_size > 31) {
    maze_size = 31;
  }
  close_intermediate();
  gen_sp_enemies = 1;
}

/*
  Called when new enemy spawned

  Args:
    int slot_number
      1 or 2, corresponding to the slot of intermediate menu
    int enemy_move_type
      E_LOW_SPEED to E_ULTRA_SPEED
    SHIP *enemy_ship
      The enemy ship generated
*/
/*
void set_intermediate_enemy_type_info(int slot_number, int enemy_move_type, SHIP *enemy_ship) {
  const char *enemy_move_type_str[] =
  {
    [E_LOW_SPEED] = "LOW SPEED",
    [E_MID_SPEED] = "MID SPEED",
    [E_HIGH_SPEED] = "HIGH SPEED",
    [E_ULTRA_SPEED] = "ULTRA SPEED",
  };

  const char *enemy_weapon_type_str[] =
  {
    [W_BALLISTIC] = "BALLISTIC",
    [W_LASER] = "LASER",
    [W_PLASMA] = "PLASMA",
  };

  if (slot_number == 1) {
    snprintf(intermediate_enemy_1_type_buffer, INTERMEDIATE_TEXT_BUFFER_SIZE,
             "ENEMY TYPE [%s]", enemy_move_type_str[enemy_move_type]);
    set_ui_text(ui_intermediate_enemy_1_type_text,
              intermediate_enemy_1_type_buffer, 0.08, T_LEFT, fixed_sys,
              (vec3) { 0.0, 0.0, 0.0 });
    snprintf(intermediate_enemy_1_info_buffer, INTERMEDIATE_TEXT_BUFFER_SIZE,
             "HEALTH [%.0f] SHIELD [%.0f]\nWEAPON [%s]",
             enemy_ship->hull.max_health, enemy_ship->shield.max_shield,
             enemy_weapon_type_str[enemy_ship->weapon.type]);
    set_ui_text(ui_intermediate_enemy_1_info_text,
                intermediate_enemy_1_info_buffer, 0.08, T_LEFT, fixed_sys,
                (vec3) { 0.0, 0.0, 0.0 });
  } else if (slot_number == 2) {
    snprintf(intermediate_enemy_2_type_buffer, INTERMEDIATE_TEXT_BUFFER_SIZE,
             "ENEMY TYPE [%s]", enemy_move_type_str[enemy_move_type]);
    set_ui_text(ui_intermediate_enemy_2_type_text,
              intermediate_enemy_2_type_buffer, 0.08, T_LEFT, fixed_sys,
              (vec3) { 0.0, 0.0, 0.0 });
    snprintf(intermediate_enemy_2_info_buffer, INTERMEDIATE_TEXT_BUFFER_SIZE,
             "HEALTH [%.0f] SHIELD [%.0f]\nWEAPON [%s]",
             enemy_ship->hull.max_health, enemy_ship->shield.max_shield,
             enemy_weapon_type_str[enemy_ship->weapon.type]);
    set_ui_text(ui_intermediate_enemy_2_info_text,
                intermediate_enemy_2_info_buffer, 0.08, T_LEFT, fixed_sys,
                (vec3) { 0.0, 0.0, 0.0 });
  } else {
    return;
  }
}
*/
