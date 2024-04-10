#include <ui/esc_ui.h>

/*
                                   ESC
Implements the functionality for defining UI components for ESC menu.
*/

/*
  Init ESC UI globaly, call by general_ui.c init_ui_components()

  Return
    0 if successful
    otherwise unsuccessful
*/
int init_esc() {
  ui_esc_root = add_ui_comp(
    UI_ROOT_COMP, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_esc_root, "assets/transparent.png");
  
  ui_esc_background = add_ui_comp(
    ui_esc_root, // UI_COMP *parent
    (vec2) { 0.4, -0.3 }, // vec2 pos
    0.2, // float width
    0.4, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_esc_background, "assets/ui/hud_color_bg.png");

  ui_esc_render_root = add_ui_comp(
    ui_esc_background, // UI_COMP *parent
    (vec2) { 0.0625, -0.0625 }, // vec2 pos
    0.875, // float width
    0.25, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_esc_render_root, "assets/transparent.png");

  ui_esc_render_button = init_blue_button(
    ui_esc_render_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_esc_render_button, "RENDER SETTINGS", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_esc_render_button, (void *) render_on_click, NULL);

  ui_esc_control_root = add_ui_comp(
    ui_esc_background, // UI_COMP *parent
    (vec2) { 0.0625, -0.375 }, // vec2 pos
    0.875, // float width
    0.25, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_esc_control_root, "assets/transparent.png");

  ui_esc_control_button = init_blue_button(
    ui_esc_control_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_esc_control_button, "GAME CONTROL", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);

  ui_esc_difficulty_root = add_ui_comp(
    ui_esc_background, // UI_COMP *parent
    (vec2) { 0.0625, -0.6875 }, // vec2 pos
    0.875, // float width
    0.25, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_esc_difficulty_root, "assets/transparent.png");

  ui_esc_difficulty_button = init_blue_button(
    ui_esc_difficulty_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_esc_difficulty_button, "GAME DIFFICULTY", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);

  set_ui_enabled(ui_esc_root, 0);
  return 0;
}

void toggle_esc() {
  if (ui_esc_root->enabled) {
    set_ui_enabled(ui_esc_root, 0);
    CURSOR_ENABLED = 0;
  } else if (ui_render_root->enabled) {
    set_ui_enabled(ui_esc_root, 0);
    set_ui_enabled(ui_render_root, 0);
    set_ui_enabled(inventory.ui_inventory_root, 0);
    set_ui_enabled(skill_tree.ui_skill_tree_root, 0);
    set_ui_enabled(ship_parts.ui_ship_parts_root, 0);
    CURSOR_ENABLED = 0;
  } else {
    set_ui_enabled(ui_esc_root, 1);
    set_ui_enabled(inventory.ui_inventory_root, 0);
    set_ui_enabled(skill_tree.ui_skill_tree_root, 0);
    set_ui_enabled(ship_parts.ui_ship_parts_root, 0);
    CURSOR_ENABLED = 1;
  }
}

void render_on_click() {
  set_ui_enabled(ui_esc_root, 0);
  set_ui_enabled(ui_render_root, 1);
}
