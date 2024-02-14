#include <ui/inventory_ui.h>
#include <stdio.h>

/*
                                   INVENTORY
Implements the functionality for defining UI components for player's station 
mode inventory.
*/

/*
  Init stats UI globaly, call by general_ui.c init_scene()

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
  set_ui_texture(inventory.ui_inventory_root, "assets/ui/transparent.png");

  inventory.ui_inventory_background = add_ui_comp(
    inventory.ui_inventory_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_background, "assets/ui/test.png");

  return 0;
}

/*
  Update stats UI per frame, call by render.c render_scene()
*/
void update_inventory() {

}

void toggle_inventory() {
  if (inventory.ui_inventory_root->enabled) {
    set_ui_enabled(inventory.ui_inventory_root, 0);
  } else {
    set_ui_enabled(inventory.ui_inventory_root, 1);
  }
}
