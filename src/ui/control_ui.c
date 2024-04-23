#include <ui/control_ui.h>

/*
                                   CONTROL
Implements the functionality for defining UI components for control menu.
*/

/*
  Init control UI globaly, call by general_ui.c init_ui_components()

  Return
    0 if successful
    otherwise unsuccessful
*/
int init_control() {
  ui_control_root = add_ui_comp(
    UI_ROOT_COMP, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_control_root, "assets/transparent.png");

  ui_control_background = add_ui_comp(
    ui_control_root, // UI_COMP *parent
    (vec2) { 0.3, -0.2 }, // vec2 pos
    0.4, // float width
    0.6, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_control_background, "assets/ui/hud_color_bg.png");

  ui_control_back_root = add_ui_comp(
    ui_control_background, // UI_COMP *parent
    (vec2) { 0.04167, -0.04167 }, // vec2 pos
    0.4375, // float width
    0.1667, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_control_back_root, "assets/transparent.png");

  ui_control_back_button = init_blue_button(
    ui_control_back_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_control_back_button, "BACK", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_control_back_button, (void *) control_back_on_click, NULL);

  ui_control_cheat_root = add_ui_comp(
    ui_control_background, // UI_COMP *parent
    (vec2) { 0.52084, -0.04167 }, // vec2 pos
    0.4375, // float width
    0.1667, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_control_cheat_root, "assets/transparent.png");

  ui_control_cheat_button = init_blue_button(
    ui_control_cheat_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_control_cheat_button, "CHEAT: ON", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_control_cheat_button, (void *) control_cheat_on_click, NULL);

  ui_control_instruction_root = add_ui_comp(
    ui_control_background, // UI_COMP *parent
    (vec2) { 0.03125, -0.25 }, // vec2 pos
    0.9375, // float width
    0.70833, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_control_instruction_root, "assets/transparent.png");

  ui_control_instruction_image = add_ui_comp(
    ui_control_instruction_root, // UI_COMP *parent
    //(vec2) { 0.0, -0.04167 }, // vec2 pos
    (vec2) { 0.5, -0.25 }, // vec2 pos
    0.75, // float width
    0.375, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_pivot(ui_control_instruction_image, PIVOT_CENTER);
  set_ui_texture(ui_control_instruction_image, "assets/ui/wasd_mouse.png");

  ui_control_instruction_title_text = add_ui_comp(
    //ui_control_instruction_image, // UI_COMP *parent
    ui_control_instruction_root, // UI_COMP *parent
    //(vec2) { 0.0, 0.0 }, // vec2 pos
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    0.05, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_control_instruction_title_text, "assets/transparent.png");
  memset(control_instruction_title_buffer, '\0', CONTROL_BUFFER_SIZE);
  snprintf(control_instruction_title_buffer, CONTROL_BUFFER_SIZE, mode == SPACE ? "SPACE MODE" : "STATION MODE");
  set_ui_text(ui_control_instruction_title_text, control_instruction_title_buffer, 1.0, T_CENTER, fixed_sys, GLM_VEC3_ZERO);

  ui_control_instruction_key_text = add_ui_comp(
    //ui_control_instruction_image, // UI_COMP *parent
    ui_control_instruction_root, // UI_COMP *parent
    //(vec2) { 0.0, -0.75 }, // vec2 pos
    (vec2) { 0.0, -0.65 }, // vec2 pos
    0.5, // float width
    0.05, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_control_instruction_key_text, "assets/transparent.png");
  memset(control_instruction_key_buffer, '\0', CONTROL_BUFFER_SIZE);
  snprintf(control_instruction_key_buffer, CONTROL_BUFFER_SIZE,
           "[W]: ACCEL\n[S]: DECEL\n[A]: LEFT ROLL\n[D]: RIGHT ROLL");
  set_ui_text(ui_control_instruction_key_text, control_instruction_key_buffer,
              1.0, T_LEFT, fixed_sys, GLM_VEC3_ZERO);

  ui_control_instruction_mouse_text = add_ui_comp(
    //ui_control_instruction_image, // UI_COMP *parent
    ui_control_instruction_root, // UI_COMP *parent
    //(vec2) { 0.5, -0.95 }, // vec2 pos
    (vec2) { 0.5, -0.65 }, // vec2 pos
    0.5, // float width
    0.05, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_control_instruction_mouse_text, "assets/transparent.png");
  memset(control_instruction_mouse_buffer, '\0', CONTROL_BUFFER_SIZE);
  snprintf(control_instruction_mouse_buffer, CONTROL_BUFFER_SIZE, "      [LBUTTON] FIRE");
  set_ui_text(ui_control_instruction_mouse_text, control_instruction_mouse_buffer, 1.0, T_CENTER, fixed_sys, GLM_VEC3_ZERO);

  set_ui_enabled(ui_control_root, 0);
  return 0;
}

void update_control() {
  if (ui_control_root->enabled) {
    if (mode == SPACE) {
      snprintf(control_instruction_title_buffer, CONTROL_BUFFER_SIZE,
               "SPACE MODE");
      set_ui_text(ui_control_instruction_title_text,
                  control_instruction_title_buffer, 1.0, T_CENTER, fixed_sys,
                  GLM_VEC3_ZERO);
      snprintf(control_instruction_key_buffer, CONTROL_BUFFER_SIZE,
               "[W]: ACCEL\n[S]: DECEL\n[A]: LEFT ROLL\n[D]: RIGHT ROLL\n[R]: LOOK BEHIND\n[TAB]: TARGET NEAREST ENEMY\n[C]: TOGGLE STATION WAYPOINT\n[P]: SHIP PARTS");
      set_ui_text(ui_control_instruction_key_text,
                  control_instruction_key_buffer, 1.0, T_LEFT, fixed_sys,
                  GLM_VEC3_ZERO);
      set_ui_texture(ui_control_instruction_image, "assets/ui/control_space.png");
    } else if (mode == STATION) {
      snprintf(control_instruction_title_buffer, CONTROL_BUFFER_SIZE,
               "STATION MODE");
      set_ui_text(ui_control_instruction_title_text,
                  control_instruction_title_buffer, 1.0, T_CENTER, fixed_sys,
                  GLM_VEC3_ZERO);
      snprintf(control_instruction_key_buffer, CONTROL_BUFFER_SIZE,
               "[W]: FORWARD\n[S]: BACK\n[A]: LEFT\n[D]: RIGHT\n[SPACE]: JUMP\n[I]: INVENTORY\n[K]: SKILL TREE\n");
      set_ui_text(ui_control_instruction_key_text,
                  control_instruction_key_buffer, 1.0, T_LEFT, fixed_sys,
                  GLM_VEC3_ZERO);
      set_ui_texture(ui_control_instruction_image, "assets/ui/control_station.png");
    }

    if (get_cheats_state()) {
      set_ui_text(ui_control_cheat_button, "CHEAT: ON", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
      set_ui_on_click(ui_control_cheat_button, (void *) control_cheat_on_click, NULL);
    } else {
      set_ui_text(ui_control_cheat_button, "CHEAT: OFF", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
      set_ui_on_click(ui_control_cheat_button, (void *) control_cheat_on_click, NULL);
    }
  }
}

void control_back_on_click() {
  set_ui_enabled(ui_esc_root, 1);
  set_ui_enabled(ui_control_root, 0);
}

void control_cheat_on_click() {
  if (get_cheats_state() == 1) {
    update_cheats(0);
  } else {
    update_cheats(1);
  }
}
