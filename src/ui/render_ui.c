#include <ui/render_ui.h>

/*
                                   RENDER
Implements the functionality for defining UI components for render menu.
*/

/*
  Init render UI globaly, call by general_ui.c init_ui_components()

  Return
    0 if successful
    otherwise unsuccessful
*/
int init_render() {
  ui_render_root = add_ui_comp(
    UI_ROOT_COMP, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_render_root, "assets/transparent.png");
  
  ui_render_background = add_ui_comp(
    ui_render_root, // UI_COMP *parent
    (vec2) { 0.4, -0.3 }, // vec2 pos
    0.2, // float width
    0.4, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_render_background, "assets/ui/hud_color_bg.png");

  ui_render_back_root = add_ui_comp(
    ui_render_background, // UI_COMP *parent
    (vec2) { 0.0625, -0.0625 }, // vec2 pos
    0.875, // float width
    0.25, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_render_back_root, "assets/transparent.png");

  ui_render_back_button = init_blue_button(
    ui_render_back_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_render_back_button, "BACK", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_render_back_button, (void *) back_on_click, NULL);
  
  ui_render_render_distance_root = add_ui_comp(
    ui_render_background, // UI_COMP *parent
    (vec2) { 0.0625, -0.375 }, // vec2 pos
    0.875, // float width
    0.25, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_render_render_distance_root, "assets/transparent.png");

  ui_render_render_distance_title_text = add_ui_comp(
    ui_render_render_distance_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    0.4, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_render_render_distance_title_text, "assets/transparent.png");
  set_ui_text(ui_render_render_distance_title_text, "RENDER DISTANCE", 0.625, T_CENTER, fixed_sys, GLM_VEC3_ZERO);

  ui_render_render_distance_minus_button = init_blue_button(
    ui_render_render_distance_root, // UI_COMP *parent
    (vec2) { 0.0, -0.4 }, // vec2 pos
    0.15, // float width
    0.6, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_render_render_distance_minus_button, "<", 0.42, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_render_render_distance_minus_button, (void *) render_distance_minus_on_click, NULL);

  ui_render_render_distance_value_text = add_ui_comp(
    ui_render_render_distance_root, // UI_COMP *parent
    (vec2) { 0.15, -0.4 }, // vec2 pos
    0.7, // float width
    0.6, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_render_render_distance_value_text, "assets/transparent.png");
  set_ui_text(ui_render_render_distance_value_text, "50", 0.42, T_CENTER, fixed_sys, GLM_VEC3_ZERO);

  ui_render_render_distance_plus_button = init_blue_button(
    ui_render_render_distance_root, // UI_COMP *parent
    (vec2) { 0.85, -0.4 }, // vec2 pos
    0.15, // float width
    0.6, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_render_render_distance_plus_button, ">", 0.42, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_render_render_distance_plus_button, (void *) render_distance_plus_on_click, NULL);
  
  ui_render_glowing_items_root = add_ui_comp(
    ui_render_background, // UI_COMP *parent
    (vec2) { 0.0625, -0.6875 }, // vec2 pos
    0.875, // float width
    0.25, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_render_render_distance_root, "assets/transparent.png");

  ui_render_glowing_items_button = init_blue_button(
    ui_render_glowing_items_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_render_glowing_items_button, "GLOWING ITEMS: OFF", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_render_glowing_items_button, (void *) glowing_items_on_click, NULL);

  set_ui_enabled(ui_render_root, 0);
  return 0;
}

void update_render() {
  if (item_glow == 1) {
    set_ui_text(ui_render_glowing_items_button, "GLOWING ITEMS: ON", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  } else {
    set_ui_text(ui_render_glowing_items_button, "GLOWING ITEMS: OFF", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  }
}

void back_on_click() {
  set_ui_enabled(ui_esc_root, 1);
  set_ui_enabled(ui_render_root, 0);
}

void render_distance_minus_on_click() {

}

void render_distance_plus_on_click() {

}

void glowing_items_on_click() {
  if (item_glow == 1) {
    item_glow = 0;
  } else {
    item_glow = 1;
  }
}
