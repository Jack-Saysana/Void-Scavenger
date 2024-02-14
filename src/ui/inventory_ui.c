#include <ui/inventory_ui.h>

/*
                                   INVENTORY
Implements the functionality for defining UI components for player's station 
mode inventory.
*/

/*
  Init inventory UI globaly, call by general_ui.c init_scene()

  Return
    0 if successful
    otherwise unsuccessful
*/
int init_inventory() {
  inventory.ui_inventory_root = add_ui_comp(
    UI_ROOT_COMP, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_root, "assets/transparent.png");

    inventory.ui_inventory_info_background = add_ui_comp(
    inventory.ui_inventory_root, // UI_COMP *parent
    (vec2) { 0.15, -0.15 }, // vec2 pos
    0.24, // float width
    0.24, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_background, "assets/ui/test.png");

  inventory.ui_inventory_info_title_background = add_ui_comp(
    inventory.ui_inventory_info_background, // UI_COMP *parent
    (vec2) { 0.025, -0.05 }, // vec2 pos
    0.95, // float width
    0.3, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_title_background, "assets/ui/hud_color_bg.png");

  inventory.ui_inventory_info_title_text = add_ui_comp(
    inventory.ui_inventory_info_title_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_title_text, "assets/transparent.png");
  set_ui_text(inventory.ui_inventory_info_title_text, "title", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  inventory.ui_inventory_info_content_background = add_ui_comp(
    inventory.ui_inventory_info_background, // UI_COMP *parent
    (vec2) { 0.025, -0.4 }, // vec2 pos
    0.95, // float width
    0.55, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_content_background, "assets/ui/hud_color.png");

  inventory.ui_inventory_info_content_text = add_ui_comp(
    inventory.ui_inventory_info_content_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.5, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_content_text, "assets/transparent.png");
  set_ui_text(inventory.ui_inventory_info_content_text, "content", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  inventory.ui_inventory_background = add_ui_comp(
    inventory.ui_inventory_root, // UI_COMP *parent
    (vec2) { 0.4, -0.15 }, // vec2 pos
    0.3, // float width
    0.3, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(inventory.ui_inventory_background, "assets/ui/test.png");

  for (int i = 0; i < 9; i++) {
    inventory.ui_inventory_slot_background[i] = add_ui_comp(
      inventory.ui_inventory_background, // UI_COMP *parent
      (vec2) { 0.025 + 0.025 * (i % 3) + (i % 3) * 0.3, -(0.025 + (i / 3) * 0.325) }, // vec2 pos
      0.3, // float width
      0.3, // float height
      ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
    );
    set_ui_texture(inventory.ui_inventory_slot_background[i], "assets/ui/hud_color_bg.png");
    // set_ui_on_hover(inventory.ui_inventory_slot_background[i], slot_on_hover, NULL);
    // set_ui_no_hover(inventory.ui_inventory_slot_background[i], slot_on_no_hover, NULL);

    inventory.ui_inventory_slot_icon[i] = add_ui_comp(
      inventory.ui_inventory_slot_background[i], // UI_COMP *parent
      (vec2) { 0.2, -0.2 }, // vec2 pos
      0.6, // float width
      0.6, // float height
      ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
    );
    set_ui_texture(inventory.ui_inventory_slot_icon[i], "assets/ui/health_icon.png");
  }

  // set init visibility
  set_ui_enabled(inventory.ui_inventory_root, 0);

  return 0;
}

/*
  Update inventory UI per frame, call by render.c render_scene()
*/
void update_inventory() {
  // check current game mode
  if (mode == SPACE) {
    // set visibility
    set_ui_enabled(inventory.ui_inventory_root, 0);
  } else if (mode == STATION) {
    // update inventory slots
    // TODO: Should be functional in sprint 2
  }
}

void toggle_inventory() {
  if (inventory.ui_inventory_root->enabled) {
    set_ui_enabled(inventory.ui_inventory_root, 0);
  } else {
    set_ui_enabled(inventory.ui_inventory_root, 1);
  }
}

void slot_on_hover(UI_COMP *ui_inventory_slot, void *unused) {
  // update when slot item on hover
  // TODO: Should be functional in sprint 2
  set_ui_texture(ui_inventory_slot, "assets/ui/test.png");
  set_ui_text(inventory.ui_inventory_info_title_text, "title_on_hover", 0.5, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  set_ui_text(inventory.ui_inventory_info_content_text, "content_on_hover", 0.5, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
}

void slot_on_no_hover(UI_COMP *ui_inventory_slot, void *unused) {
  // update when slot item on hover
  // TODO: Should be functional in sprint 2
  set_ui_texture(ui_inventory_slot, "assets/ui/hud_color_bg.png");
  set_ui_text(inventory.ui_inventory_info_title_text, "title", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  set_ui_text(inventory.ui_inventory_info_content_text, "content", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
}
