#include <ui/inventory_ui.h>

/*
                                   INVENTORY
Implements the functionality for defining UI components for player's station 
mode inventory.
*/

/*
  Init inventory UI globaly, call by general_ui.c init_ui_components()

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
    0.2833, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_title_background,
                 "assets/ui/hud_color_bg.png");

  inventory.ui_inventory_info_title_text = add_ui_comp(
    inventory.ui_inventory_info_title_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X |
    HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_title_text,
                 "assets/transparent.png");
  set_ui_text(inventory.ui_inventory_info_title_text,
              "title", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  inventory.ui_inventory_info_content_background = add_ui_comp(
    inventory.ui_inventory_info_background, // UI_COMP *parent
    (vec2) { 0.025, -0.3833 }, // vec2 pos
    0.95, // float width
    0.5666, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_content_background,
                 "assets/ui/hud_color.png");

  inventory.ui_inventory_info_content_text = add_ui_comp(
    inventory.ui_inventory_info_content_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.4, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X |
    HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_content_text,
                 "assets/transparent.png");
  set_ui_text(inventory.ui_inventory_info_content_text, "content", 1.0, T_LEFT,
              fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

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
      (vec2) { 0.025 + 0.025 * (i % 3) + (i % 3) * 0.3, 
               -(0.025 + (i / 3) * 0.325) }, // vec2 pos
      0.3, // float width
      0.3, // float height
      ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
    );
    set_ui_texture(inventory.ui_inventory_slot_background[i],
                   "assets/ui/hud_color_bg.png");
    // set_ui_on_hover(inventory.ui_inventory_slot_background[i],
    //                 slot_on_hover, NULL);
    // set_ui_no_hover(inventory.ui_inventory_slot_background[i],
    //                 slot_off_hover, NULL);

    inventory.ui_inventory_slot_icon[i] = add_ui_comp(
      inventory.ui_inventory_slot_background[i], // UI_COMP *parent
      (vec2) { 0.2, -0.2 }, // vec2 pos
      0.6, // float width
      0.6, // float height
      ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
    );
    // switch (i%3) {
    //   case 0:
    //     set_ui_texture(inventory.ui_inventory_slot_icon[i], "assets/ui/energy_icon.png");
    //     set_ui_texture(inventory.ui_inventory_slot_icon[i], "assets/ui/energy_icon.png");
    //     set_ui_texture(inventory.ui_inventory_slot_icon[i], "assets/ui/energy_icon.png");
    //     break;
    //   case 1:
    //     set_ui_texture(inventory.ui_inventory_slot_icon[i], "assets/ui/health_icon.png");
    //     break;
    //   case 2:
    //     set_ui_texture(inventory.ui_inventory_slot_icon[i], "assets/ui/parts_thruster_icon.png");
    //     break;
    // }
    set_ui_texture(inventory.ui_inventory_slot_icon[i],
                    "assets/ui/health_icon.png");
    set_ui_on_click(inventory.ui_inventory_slot_icon[i],
                    slot_on_click, NULL);
  }

  // set init visibility
  set_ui_enabled(inventory.ui_inventory_root, 0);

  return 0;
}

/*
  Update inventory UI per frame, call by general_ui.c update_ui_components()
*/
void update_inventory() {
  // check current game mode
  if (mode == SPACE) {
    // set visibility
  } else if (mode == STATION) {
    // update inventory slots
    // TODO: Should be functional in sprint 2
    // set_ui_texture(inventory.ui_inventory_slot_icon[0], "assets/ui/parts/i_reactor_blue.png");
    // for (int i = 0; i < 1; i++) {
    //   update_slot(inventory.ui_inventory_slot_icon[i], st_player.inventory + i);
    // }
  }
}

void toggle_inventory() {
  if (inventory.ui_inventory_root->enabled) {
    set_ui_enabled(inventory.ui_inventory_root, 0);
    CURSOR_ENABLED = 0;
  } else {
    set_ui_enabled(inventory.ui_inventory_root, 1);
    set_ui_enabled(skill_tree.ui_skill_tree_root, 0);
    set_ui_enabled(ship_parts.ui_ship_parts_root, 0);
    CURSOR_ENABLED = 1;
  }
}

void slot_on_hover(UI_COMP *ui_inventory_slot, void *unused) {
  // update when slot item on hover
  // TODO: Should be functional in sprint 2
  set_ui_texture(ui_inventory_slot, "assets/ui/test.png");
  set_ui_text(inventory.ui_inventory_info_title_text, "title_on_hover", 0.5, 
              T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  set_ui_text(inventory.ui_inventory_info_content_text, "content_on_hover", 
              0.5, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
}

void slot_off_hover(UI_COMP *ui_inventory_slot, void *unused) {
  // update when slot item on hover
  // TODO: Should be functional in sprint 2
  set_ui_texture(ui_inventory_slot, "assets/ui/hud_color_bg.png");
  set_ui_text(inventory.ui_inventory_info_title_text, "title", 1.0, T_LEFT, 
              fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  set_ui_text(inventory.ui_inventory_info_content_text, "content", 1.0, T_LEFT,
              fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
}

void slot_on_click(UI_COMP *ui_inventory_slot, void *unused) {
  // set_ui_text(inventory.ui_inventory_info_title_text, "clicked", 1.0, T_LEFT, 
  //             fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  // set_ui_text(inventory.ui_inventory_info_content_text, "clicked", 1.0, T_LEFT,
  //             fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
}

void update_slot(UI_COMP *ui_inventory_slot, I_SLOT *inventory_slot) {
  switch (inventory_slot->type) {
    case I_SLOT_REACTOR:
      switch (inventory_slot->rarity) {
        case BLUE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_reactor_blue.png");
          break;
        case GREEN_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_reactor_green.png");
          break;
        case PURPLE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_reactor_purple.png");
          break;
        case GOLD_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_reactor_gold.png");
          break;
      }
      break;
    case I_SLOT_HULL:
      switch (inventory_slot->rarity) {
        case BLUE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_hull_blue.png");
          break;
        case GREEN_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_hull_green.png");
          break;
        case PURPLE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_hull_purple.png");
          break;
        case GOLD_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_hull_gold.png");
          break;
      }
      break;
    case I_SLOT_SHIELD:
      switch (inventory_slot->rarity) {
        case BLUE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_shield_blue.png");
          break;
        case GREEN_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_shield_green.png");
          break;
        case PURPLE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_shield_purple.png");
          break;
        case GOLD_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_shield_gold.png");
          break;
      }
      break;
    case I_SLOT_WEAPON:
      switch(inventory_slot->weapon_type) {
        case W_LASER:
          switch (inventory_slot->rarity) {
            case BLUE_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_laser_blue.png");
              break;
            case GREEN_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_laser_green.png");
              break;
            case PURPLE_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_laser_purple.png");
              break;
            case GOLD_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_laser_gold.png");
              break;
          }
          break;
        case W_BALLISTIC:
          switch (inventory_slot->rarity) {
            case BLUE_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_ballistic_blue.png");
              break;
            case GREEN_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_ballistic_green.png");
              break;
            case PURPLE_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_ballistic_purple.png");
              break;
            case GOLD_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_ballistic_gold.png");
              break;
          }
          break;
        case W_PLASMA:
          switch (inventory_slot->rarity) {
            case BLUE_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_plasma_blue.png");
              break;
            case GREEN_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_plasma_green.png");
              break;
            case PURPLE_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_plasma_purple.png");
              break;
            case GOLD_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_plasma_gold.png");
              break;
          }
          break;
      }
      break;
    case I_SLOT_WING:
      switch (inventory_slot->rarity) {
        case BLUE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_wing_blue.png");
          break;
        case GREEN_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_wing_green.png");
          break;
        case PURPLE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_wing_purple.png");
          break;
        case GOLD_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_wing_gold.png");
          break;
      }
      break;
    case I_SLOT_THRUSTER:
      switch (inventory_slot->rarity) {
        case BLUE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_thruster_blue.png");
          break;
        case GREEN_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_thruster_green.png");
          break;
        case PURPLE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_thruster_purple.png");
          break;
        case GOLD_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_thruster_gold.png");
          break;
      }
      break;
    default:
      // set_ui_texture(ui_inventory_slot, "assets/ui/hud_color_bg.png");
      break;
  }
}
