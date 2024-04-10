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

  ui_render_render_distance_root = add_ui_comp(
    ui_render_background, // UI_COMP *parent
    (vec2) { 0.0625, -0.375 }, // vec2 pos
    0.875, // float width
    0.25, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_render_render_distance_root, "assets/transparent.png");

  ui_render_render_distance_button = init_blue_button(
    ui_render_render_distance_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_render_render_distance_button, "RENDER DISTANCE", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);

  ui_render_glowing_items_root = add_ui_comp(
    ui_render_background, // UI_COMP *parent
    (vec2) { 0.0625, -0.6875 }, // vec2 pos
    0.875, // float width
    0.25, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_render_glowing_items_root, "assets/transparent.png");

  ui_render_glowing_items_button = init_blue_button(
    ui_render_glowing_items_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_render_glowing_items_button, "GLOWING ITEMS", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  
  set_ui_enabled(ui_render_root, 0);
  return 0;
}
