#include <ui/ship_parts_ui.h>
#include <stdio.h>

/*
                                   SHIP_PARTS
Implements the functionality for defining UI components for player's space 
mode ship parts.
*/

/*
  Init ship parts UI globaly, call by general_ui.c init_scene()

  Return
    0 if successful
    otherwise unsuccessful
*/
int init_ship_parts() {
  ship_parts.ui_ship_parts_root = add_ui_comp(
    UI_ROOT_COMP, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_parts_root, "assets/ui/test.png");

  ship_parts.ui_reactor_background = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.2, -0.2 }, // vec2 pos
    0.2, // float width
    0.2, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_reactor_background, "assets/ui/hud_color_bg.png");

  ship_parts.ui_reactor_icon = add_ui_comp(
    ship_parts.ui_reactor_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_reactor_icon, "assets/ui/hud_color.png");

  ship_parts.ui_hull_background = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.4, -0.2 }, // vec2 pos
    0.2, // float width
    0.2, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_hull_background, "assets/ui/hud_color_bg.png");

  ship_parts.ui_hull_icon = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_hull_icon, "assets/ui/hud_color.png");

  ship_parts.ui_shield_background = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.6, -0.2 }, // vec2 pos
    0.2, // float width
    0.2, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_shield_background, "assets/ui/hud_color_bg.png");

  ship_parts.ui_shield_icon = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_shield_icon, "assets/ui/hud_color.png");

  ship_parts.ui_weapon_background = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.2, -0.4 }, // vec2 pos
    0.2, // float width
    0.2, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_weapon_background, "assets/ui/hud_color_bg.png");

  ship_parts.ui_weapon_icon = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/hud_color.png");

  ship_parts.ui_wing_background = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.4, -0.4 }, // vec2 pos
    0.2, // float width
    0.2, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_wing_background, "assets/ui/hud_color_bg.png");

  ship_parts.ui_wing_icon = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_wing_icon, "assets/ui/hud_color.png");

  ship_parts.ui_thruster_background = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.6, -0.4 }, // vec2 pos
    0.2, // float width
    0.2, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_thruster_background, "assets/ui/hud_color_bg.png");

  ship_parts.ui_thruster_icon = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_thruster_icon, "assets/ui/hud_color.png");

  set_ui_enabled(ship_parts.ui_ship_parts_root, 0);

  return 0;
}

/*
  Update ship parts UI per frame, call by render.c render_scene()
*/
void update_ship_parts() {
  // check current game mode
  if (mode == SPACE) {
    // update inventory slots
    // TODO: Should be functional in sprint 2
    
  } else if (mode == STATION) {
    // set visibility
    set_ui_enabled(ship_parts.ui_ship_parts_root, 1);
  }
}

void toggle_ship_parts() {
  if (ship_parts.ui_ship_parts_root->enabled) {
    set_ui_enabled(ship_parts.ui_ship_parts_root, 0);
  } else {
    set_ui_enabled(ship_parts.ui_ship_parts_root, 1);
  }
}
