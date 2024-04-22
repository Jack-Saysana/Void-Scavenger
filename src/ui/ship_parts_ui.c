#include <ui/ship_parts_ui.h>

/*
                                   SHIP_PARTS
Implements the functionality for defining UI components for player's space
mode ship parts.
*/

/*
  Init ship parts UI globaly, call by general_ui.c init_ui_components()

  Return
    0 if successful
    otherwise unsuccessful
*/

int init_ship_parts() {
  // Init equipped parts
  reset_equipped_parts();

  // Init UI components
  ship_parts.ui_ship_parts_root = add_ui_comp(
    UI_ROOT_COMP, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_parts_root, "assets/transparent.png");

  ship_parts.ui_ship_parts_background = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.04, 0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_parts_background,
                 "assets/ui/ship_top_view_mask.png");

  ship_parts.ui_ship_top_view = add_ui_comp(
    ship_parts.ui_ship_parts_background, // UI_COMP *parent
    (vec2) { 0, 0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_top_view, "assets/ui/ship_top_view.png");

  ship_parts.ui_reactor_background = add_ui_comp(
    ship_parts.ui_ship_top_view, // UI_COMP *parent
    (vec2) { 0.46, -0.55 }, // vec2 pos
    0.08, // float width
    0.08, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(ship_parts.ui_reactor_background,
                 "assets/ui/hud_color_bg.png");
  set_ui_on_hover(ship_parts.ui_reactor_background,
                  ship_parts_on_hover_wrapper, (void *)&equipped_reactor);
  set_ui_no_hover(ship_parts.ui_reactor_background,
                  ship_parts_off_hover_wrapper, (void *)&equipped_reactor);

  ship_parts.ui_reactor_icon = add_ui_comp(
    ship_parts.ui_reactor_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_reactor_icon,
                 "assets/ui/parts_reactor_icon.png");
  set_ui_on_click(ship_parts.ui_reactor_icon,
                  (void *) ship_parts_on_click, &equipped_reactor);

  ship_parts.ui_hull_background = add_ui_comp(
    ship_parts.ui_ship_top_view, // UI_COMP *parent
    (vec2) { 0.46, -0.35 }, // vec2 pos
    0.08, // float width
    0.08, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(ship_parts.ui_hull_background, "assets/ui/hud_color_bg.png");
  set_ui_on_hover(ship_parts.ui_hull_background,
                  ship_parts_on_hover_wrapper, (void *)&equipped_hull);
  set_ui_no_hover(ship_parts.ui_hull_background,
                  ship_parts_off_hover_wrapper, (void *)&equipped_hull);

  ship_parts.ui_hull_icon = add_ui_comp(
    ship_parts.ui_hull_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_hull_icon, "assets/ui/parts_hull_icon.png");
  set_ui_on_click(ship_parts.ui_hull_icon, (void *) ship_parts_on_click,
                  &equipped_hull);

  ship_parts.ui_shield_background = add_ui_comp(
    ship_parts.ui_ship_top_view, // UI_COMP *parent
    (vec2) { 0.46, -0.05 }, // vec2 pos
    0.08, // float width
    0.08, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(ship_parts.ui_shield_background,
                 "assets/ui/hud_color_bg.png");
  set_ui_on_hover(ship_parts.ui_shield_background,
                  ship_parts_on_hover_wrapper, (void *)&equipped_shield);
  set_ui_no_hover(ship_parts.ui_shield_background,
                  ship_parts_off_hover_wrapper, (void *)&equipped_shield);

  ship_parts.ui_shield_icon = add_ui_comp(
    ship_parts.ui_shield_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_shield_icon, "assets/ui/parts_shield_icon.png");
  set_ui_on_click(ship_parts.ui_shield_icon, (void *) ship_parts_on_click,
                  &equipped_shield);

  ship_parts.ui_weapon_background = add_ui_comp(
    ship_parts.ui_ship_top_view, // UI_COMP *parent
    (vec2) { 0.62, -0.3 }, // vec2 pos
    0.08, // float width
    0.08, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(ship_parts.ui_weapon_background,
                 "assets/ui/hud_color_bg.png");
  set_ui_on_hover(ship_parts.ui_weapon_background,
                  ship_parts_on_hover_wrapper, (void *)&equipped_weapon);
  set_ui_no_hover(ship_parts.ui_weapon_background,
                  ship_parts_off_hover_wrapper, (void *)&equipped_weapon);

  ship_parts.ui_weapon_icon = add_ui_comp(
    ship_parts.ui_weapon_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts_weapon_icon.png");
  set_ui_on_click(ship_parts.ui_weapon_icon, (void *) ship_parts_on_click,
                  &equipped_weapon);

  ship_parts.ui_wing_background = add_ui_comp(
    ship_parts.ui_ship_top_view, // UI_COMP *parent
    (vec2) { 0.3, -0.3 }, // vec2 pos
    0.08, // float width
    0.08, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(ship_parts.ui_wing_background, "assets/ui/hud_color_bg.png");
  set_ui_on_hover(ship_parts.ui_wing_background,
                  ship_parts_on_hover_wrapper, (void *)&equipped_wing);
  set_ui_no_hover(ship_parts.ui_wing_background,
                  ship_parts_off_hover_wrapper, (void *)&equipped_wing);

  ship_parts.ui_wing_icon = add_ui_comp(
    ship_parts.ui_wing_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_wing_icon, "assets/ui/parts_wing_icon.png");
  set_ui_on_click(ship_parts.ui_wing_icon, (void *) ship_parts_on_click,
                  &equipped_wing);

  ship_parts.ui_thruster_background = add_ui_comp(
    ship_parts.ui_ship_top_view, // UI_COMP *parent
    (vec2) { 0.46, -0.8 }, // vec2 pos
    0.08, // float width
    0.08, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(ship_parts.ui_thruster_background,
                 "assets/ui/hud_color_bg.png");
  set_ui_on_hover(ship_parts.ui_thruster_background,
                  ship_parts_on_hover_wrapper, (void *)&equipped_thruster);
  set_ui_no_hover(ship_parts.ui_thruster_background,
                  ship_parts_off_hover_wrapper, (void *)&equipped_thruster);

  ship_parts.ui_thruster_icon = add_ui_comp(
    ship_parts.ui_thruster_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_thruster_icon,
                 "assets/ui/parts_thruster_icon.png");
  set_ui_on_click(ship_parts.ui_thruster_icon, (void *) ship_parts_on_click,
                  &equipped_thruster);

  ship_parts.ui_ship_parts_info_background = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.7, -0.67 }, // vec2 pos
    0.24, // float width
    0.30, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_parts_info_background,
                 "assets/ui/test.png");

  ship_parts.ui_ship_parts_info_title_background = add_ui_comp(
    ship_parts.ui_ship_parts_info_background, // UI_COMP *parent
    (vec2) { 0.025, -0.04 }, // vec2 pos
    0.95, // float width
    0.16, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_parts_info_title_background,
                 "assets/ui/hud_color.png");

  ship_parts.ui_ship_parts_info_title_text = add_ui_comp(
    ship_parts.ui_ship_parts_info_title_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    LINE_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_parts_info_title_text,
                 "assets/transparent.png");
  memset(ship_parts_info_title_buffer, '\0', SHIP_PARTS_TEXT_BUFFER_SIZE);
  snprintf(ship_parts_info_title_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
           "[RARITY] TYPE");
  set_ui_text(ship_parts.ui_ship_parts_info_title_text,
              ship_parts_info_title_buffer, TEXT_LINE_HEIGHT, T_LEFT,
              fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  ship_parts.ui_ship_parts_info_content_background = add_ui_comp(
    ship_parts.ui_ship_parts_info_background, // UI_COMP *parent
    (vec2) { 0.025, -0.24 }, // vec2 pos
    0.95, // float width
    0.72, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_parts_info_content_background,
                 "assets/ui/hud_color_bg.png");

  ship_parts.ui_ship_parts_info_content_text = add_ui_comp(
    ship_parts.ui_ship_parts_info_content_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    LINE_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_parts_info_content_text,
                 "assets/transparent.png");
  memset(ship_parts_info_content_buffer, '\0', SHIP_PARTS_TEXT_BUFFER_SIZE);
  snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
           "EMPTY");
  set_ui_text(ship_parts.ui_ship_parts_info_content_text,
              ship_parts_info_content_buffer, CONTENT_LINE_HEIGHT, T_LEFT,
              fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  // set init visibility
  set_ui_enabled(ship_parts.ui_ship_parts_root, 0);

  return 0;
}

/*
  Update ship parts UI per frame, call by general_ui.c update_ui_components()
*/
void update_ship_parts() {
  // check current game mode
  if (mode == SPACE) {
    // Update ship parts icons
    update_ship_parts_icons();
  } else if (mode == STATION) {
    // set visibility
    // set_ui_enabled(ship_parts.ui_ship_parts_root, 0);
    update_ship_parts_icons();
  }
}

void toggle_ship_parts() {
  if (ui_intermediate_root->enabled) {
    return;
  }
  if (ship_parts.ui_ship_parts_root->enabled) {
    set_ui_enabled(ship_parts.ui_ship_parts_root, 0);
    if (inventory.ui_inventory_root->enabled) {
      set_ui_enabled(inventory.ui_inventory_root, 0);
    }
    CURSOR_ENABLED = 0;
  } else {
    set_ui_enabled(ship_parts.ui_ship_parts_root, 1);
    set_ui_enabled(ship_parts.ui_ship_parts_info_background, 1);
    set_ui_enabled(ship_parts.ui_ship_parts_background, 1);
    set_ui_enabled(inventory.ui_inventory_root, 0);
    set_ui_enabled(ui_esc_root, 0);
    set_ui_enabled(ui_render_root, 0);
    set_ui_enabled(ui_control_root, 0);
    CURSOR_ENABLED = 1;
  }
}

void update_ship_parts_icons() {
  if (equipped_hull.type == I_SLOT_EMPTY) {
    set_ui_texture(ship_parts.ui_hull_icon, "assets/transparent.png");
  } else {
    switch (equipped_hull.rarity) {
      case WHITE_RARITY:
        set_ui_texture(ship_parts.ui_hull_icon, "assets/ui/parts/i_hull_white.png");
        break;
      case BLUE_RARITY:
        set_ui_texture(ship_parts.ui_hull_icon, "assets/ui/parts/i_hull_blue.png");
        break;
      case GREEN_RARITY:
        set_ui_texture(ship_parts.ui_hull_icon, "assets/ui/parts/i_hull_green.png");
        break;
      case PURPLE_RARITY:
        set_ui_texture(ship_parts.ui_hull_icon, "assets/ui/parts/i_hull_purple.png");
        break;
      case GOLD_RARITY:
        set_ui_texture(ship_parts.ui_hull_icon, "assets/ui/parts/i_hull_gold.png");
        break;
    }
  }

  if (equipped_reactor.type == I_SLOT_EMPTY) {
    set_ui_texture(ship_parts.ui_reactor_icon, "assets/transparent.png");
  } else {
    switch (equipped_reactor.rarity) {
      case WHITE_RARITY:
        set_ui_texture(ship_parts.ui_reactor_icon, "assets/ui/parts/i_reactor_white.png");
        break;
      case BLUE_RARITY:
        set_ui_texture(ship_parts.ui_reactor_icon, "assets/ui/parts/i_reactor_blue.png");
        break;
      case GREEN_RARITY:
        set_ui_texture(ship_parts.ui_reactor_icon, "assets/ui/parts/i_reactor_green.png");
        break;
      case PURPLE_RARITY:
        set_ui_texture(ship_parts.ui_reactor_icon, "assets/ui/parts/i_reactor_purple.png");
        break;
      case GOLD_RARITY:
        set_ui_texture(ship_parts.ui_reactor_icon, "assets/ui/parts/i_reactor_gold.png");
        break;
    }
  }

  if (equipped_shield.type == I_SLOT_EMPTY) {
    set_ui_texture(ship_parts.ui_shield_icon, "assets/transparent.png");
  } else {
    switch (equipped_shield.rarity) {
      case WHITE_RARITY:
        set_ui_texture(ship_parts.ui_shield_icon, "assets/ui/parts/i_shield_white.png");
        break;
      case BLUE_RARITY:
        set_ui_texture(ship_parts.ui_shield_icon, "assets/ui/parts/i_shield_blue.png");
        break;
      case GREEN_RARITY:
        set_ui_texture(ship_parts.ui_shield_icon, "assets/ui/parts/i_shield_green.png");
        break;
      case PURPLE_RARITY:
        set_ui_texture(ship_parts.ui_shield_icon, "assets/ui/parts/i_shield_purple.png");
        break;
      case GOLD_RARITY:
        set_ui_texture(ship_parts.ui_shield_icon, "assets/ui/parts/i_shield_gold.png");
        break;
    }
  }

  if (equipped_thruster.type == I_SLOT_EMPTY) {
    set_ui_texture(ship_parts.ui_thruster_icon, "assets/transparent.png");
  } else {
    switch (equipped_thruster.rarity) {
      case WHITE_RARITY:
        set_ui_texture(ship_parts.ui_thruster_icon, "assets/ui/parts/i_thruster_white.png");
        break;
      case BLUE_RARITY:
        set_ui_texture(ship_parts.ui_thruster_icon, "assets/ui/parts/i_thruster_blue.png");
        break;
      case GREEN_RARITY:
        set_ui_texture(ship_parts.ui_thruster_icon, "assets/ui/parts/i_thruster_green.png");
        break;
      case PURPLE_RARITY:
        set_ui_texture(ship_parts.ui_thruster_icon, "assets/ui/parts/i_thruster_purple.png");
        break;
      case GOLD_RARITY:
        set_ui_texture(ship_parts.ui_thruster_icon, "assets/ui/parts/i_thruster_gold.png");
        break;
    }
  }

  if (equipped_weapon.type == I_SLOT_EMPTY) {
    set_ui_texture(ship_parts.ui_weapon_icon, "assets/transparent.png");
  } else {
    switch(equipped_weapon.weapon_type) {
      case W_LASER:
        switch (equipped_weapon.rarity) {
          case WHITE_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_laser_white.png");
            break;
          case BLUE_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_laser_blue.png");
            break;
          case GREEN_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_laser_green.png");
            break;
          case PURPLE_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_laser_purple.png");
            break;
          case GOLD_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_laser_gold.png");
            break;
        }
        break;
      case W_BALLISTIC:
        switch (equipped_weapon.rarity) {
          case WHITE_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_ballistic_white.png");
            break;
          case BLUE_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_ballistic_blue.png");
            break;
          case GREEN_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_ballistic_green.png");
            break;
          case PURPLE_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_ballistic_purple.png");
            break;
          case GOLD_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_ballistic_gold.png");
            break;
        }
        break;
      case W_PLASMA:
        switch (equipped_weapon.rarity) {
          case WHITE_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_plasma_white.png");
            break;
          case BLUE_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_plasma_blue.png");
            break;
          case GREEN_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_plasma_green.png");
            break;
          case PURPLE_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_plasma_purple.png");
            break;
          case GOLD_RARITY:
            set_ui_texture(ship_parts.ui_weapon_icon, "assets/ui/parts/w_plasma_gold.png");
            break;
        }
        break;
    }
  }

  if (equipped_wing.type == I_SLOT_EMPTY) {
    set_ui_texture(ship_parts.ui_wing_icon, "assets/transparent.png");
  } else {
    switch (equipped_wing.rarity) {
      case WHITE_RARITY:
        set_ui_texture(ship_parts.ui_wing_icon, "assets/ui/parts/i_wing_white.png");
        break;
      case BLUE_RARITY:
        set_ui_texture(ship_parts.ui_wing_icon, "assets/ui/parts/i_wing_blue.png");
        break;
      case GREEN_RARITY:
        set_ui_texture(ship_parts.ui_wing_icon, "assets/ui/parts/i_wing_green.png");
        break;
      case PURPLE_RARITY:
        set_ui_texture(ship_parts.ui_wing_icon, "assets/ui/parts/i_wing_purple.png");
        break;
      case GOLD_RARITY:
        set_ui_texture(ship_parts.ui_wing_icon, "assets/ui/parts/i_wing_gold.png");
        break;
    }
  }
}

void ship_parts_on_hover_wrapper(UI_COMP *ui_ship_parts, void *arg) {
  ship_parts_on_hover(ui_ship_parts, (I_SLOT *)arg);
}

void ship_parts_on_hover(UI_COMP *ui_ship_parts, I_SLOT *equipped_ship_parts) {
  if (!ship_parts.ui_ship_parts_info_background->enabled) {
    set_ui_enabled(ship_parts.ui_ship_parts_info_background, 1);
  }
  if (inventory.ui_inventory_info_background->enabled) {
    set_ui_enabled(inventory.ui_inventory_info_background, 0);
  }

  const char *item_slot_id_str[] =
  {
    [I_SLOT_REACTOR] = "REACTOR",
    [I_SLOT_HULL] = "HULL",
    [I_SLOT_SHIELD]  = "SHIELD",
    [I_SLOT_WEAPON]  = "WEAPON",
    [I_SLOT_WING] = "WING",
    [I_SLOT_THRUSTER] = "THRUSTER",
    [I_SLOT_EMPTY]  = "EMPTY"
  };

  const char *item_slot_weapon_type_str[] =
  {
    [W_BALLISTIC] = "WEAPON BALLISTIC",
    [W_LASER] = "WEAPON LASER",
    [W_PLASMA]  = "WEAPON PLASMA",
  };

  const char *rarity_str[] =
  {
    [GOLD_RARITY] = "GOLD",
    [PURPLE_RARITY] = "PURPLE",
    [GREEN_RARITY]  = "GREEN",
    [BLUE_RARITY]  = "BLUE",
    [WHITE_RARITY] = "WHITE",
  };

  set_ui_texture(ui_ship_parts, "assets/ui/test.png");
  // Fill title buffer
  if (equipped_ship_parts->type == I_SLOT_WEAPON) {
    snprintf(ship_parts_info_title_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
             "[%s] %s", rarity_str[equipped_ship_parts->rarity],
             item_slot_weapon_type_str[equipped_ship_parts->weapon_type]);
  } else if (equipped_ship_parts->type != I_SLOT_EMPTY) {
    snprintf(ship_parts_info_title_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
             "[%s] %s", rarity_str[equipped_ship_parts->rarity],
             item_slot_id_str[equipped_ship_parts->type]);
  } else {
    snprintf(ship_parts_info_title_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
             "[RARITY] TYPE");
  }
  set_ui_text(ship_parts.ui_ship_parts_info_title_text,
              ship_parts_info_title_buffer, TEXT_LINE_HEIGHT, T_LEFT,
              fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  // Fill content buffer
  switch (equipped_ship_parts->type) {
    case I_SLOT_REACTOR:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
                "[MAX OUTPUT = %.2f]\n[RECHARGE RATE = %.2f]\n[STALL TIME = %.2f]",
                 equipped_ship_parts->data.reactor.max_output,
                 equipped_ship_parts->data.reactor.recharge_rate,
                 equipped_ship_parts->data.reactor.stall_time);
      break;
    case I_SLOT_HULL:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
                "[MAX HEALTH = %.2f]",
                equipped_ship_parts->data.hull.max_health);
      break;
    case I_SLOT_SHIELD:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
                "[MAX SHIELD = %.2f]\n[RECHARGE RATE = %.2f]\n[RECHARGE DELAY = %.2f]\n[POWER DRAW = %.2f]",
                equipped_ship_parts->data.shield.max_shield,
                equipped_ship_parts->data.shield.recharge_rate,
                equipped_ship_parts->data.shield.recharge_delay,
                equipped_ship_parts->data.shield.power_draw);
      break;
    case I_SLOT_WEAPON:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
                "[DAMAGE = %.2f]\n[FIRE RATE = %.2f]\n[POWER DRAW = %.2f]\n[PROJ SPEED = %.2f]\n[RANGE = %.2f]\n[PROJ SIZE = %.2f]\n[NUM BARRELS = %.d]",
                equipped_ship_parts->data.weapon.damage,
                equipped_ship_parts->data.weapon.fire_rate,
                equipped_ship_parts->data.weapon.max_power_draw,
                equipped_ship_parts->data.weapon.proj_speed,
                equipped_ship_parts->data.weapon.range,
                equipped_ship_parts->data.weapon.bullet_size,
                equipped_ship_parts->data.weapon.num_barrels);
      break;
    case I_SLOT_WING:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
                "[MAX ANG ACCEL = %.2f]\n[MAX ANG VEL = %.2f]",
                equipped_ship_parts->data.wing.max_ang_accel,
                equipped_ship_parts->data.wing.max_ang_vel);
      break;
    case I_SLOT_THRUSTER:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
                "[MAX ACCELERATION = %.2f]\n[MAX POWER DRAW = %.2f]\n[MAX VELOCITY = %.2f]",
                equipped_ship_parts->data.thruster.max_accel,
                equipped_ship_parts->data.thruster.max_power_draw,
                equipped_ship_parts->data.thruster.max_vel);
      break;
    case DEFAULT:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE, "EMPTY");
      break;
  }
  set_ui_text(ship_parts.ui_ship_parts_info_content_text,
              ship_parts_info_content_buffer, CONTENT_LINE_HEIGHT, T_LEFT,
              fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
}

void ship_parts_off_hover_wrapper(UI_COMP *ui_ship_parts, void *arg) {
  ship_parts_off_hover(ui_ship_parts, (I_SLOT *)arg);
}

void ship_parts_off_hover(UI_COMP *ui_ship_parts, I_SLOT *equipped_ship_parts) {
  set_ui_texture(ui_ship_parts, "assets/ui/hud_color_bg.png");
}

void ship_parts_on_click(UI_COMP *ui_ship_parts, I_SLOT *equipped_ship_parts) {
  if (mode == SPACE) {
    return;
  }

  I_SLOT *first_empty_slot = inv_first_avail();
  if (!first_empty_slot) {
    // TODO: add popup prompt
    printf("INVENTORY IS FULL\n");
    return;
  }
  switch_slot(equipped_ship_parts, inv_first_avail());
  update_ship_stats();
}

void update_ship_stats() {
  player_ship.reactor = equipped_reactor.data.reactor;
  player_ship.reactor.max_output = equipped_reactor.data.reactor.max_output;

  player_ship.hull = equipped_hull.data.hull;

  player_ship.shield = equipped_shield.data.shield;
  player_ship.cur_shield = fmin(player_ship.shield.max_shield,
                                player_ship.cur_shield);
  player_ship.recharging_shield = 0;
  update_timer_args(ship_shield_recharge_delay, &player_ship,
                    (void *) INVALID_INDEX);
  add_timer(player_ship.shield.recharge_delay,
            ship_shield_recharge_delay, -1000, &player_ship);

  player_ship.weapon = equipped_weapon.data.weapon;

  player_ship.wing = equipped_wing.data.wing;

  player_ship.thruster = equipped_thruster.data.thruster;
  player_ship.cur_speed = fmin(player_ship.thruster.max_vel,
                               player_ship.cur_speed);
  glm_vec3_scale_as(player_ship.ent->velocity, player_ship.cur_speed,
                    player_ship.ent->velocity);
}
