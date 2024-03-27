#include <ui/ship_parts_ui.h>
#include <stdio.h>

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
  equipped_hull.type = I_SLOT_HULL;
  equipped_hull.rarity = WHITE_RARITY;
  equipped_hull.weapon_type = NOT_WEAPON;
  equipped_hull.data.hull.max_health = 100;

  equipped_reactor.type = I_SLOT_REACTOR;
  equipped_reactor.rarity = WHITE_RARITY;
  equipped_reactor.weapon_type = NOT_WEAPON;
  equipped_reactor.data.reactor.max_output = 100;

  equipped_shield.type = I_SLOT_SHIELD;
  equipped_shield.rarity = WHITE_RARITY;
  equipped_shield.weapon_type = NOT_WEAPON;
  equipped_shield.data.shield.max_shield = 100;
  equipped_shield.data.shield.power_draw = 25;
  equipped_shield.data.shield.recharge_delay = 2;
  equipped_shield.data.shield.recharge_rate = 5;
  
  equipped_thruster.type = I_SLOT_THRUSTER;
  equipped_thruster.rarity = WHITE_RARITY;
  equipped_thruster.weapon_type = NOT_WEAPON;
  equipped_thruster.data.thruster.max_accel = 5;
  equipped_thruster.data.thruster.max_power_draw = 25;
  equipped_thruster.data.thruster.max_vel = 10;

  equipped_weapon.type = I_SLOT_WEAPON;
  equipped_weapon.rarity = WHITE_RARITY;
  equipped_weapon.weapon_type = W_BALLISTIC;
  equipped_weapon.data.weapon.damage = 100;
  equipped_weapon.data.weapon.fire_rate = 0.1;
  equipped_weapon.data.weapon.max_power_draw = 25;
  equipped_weapon.data.weapon.proj_speed = 50;
  equipped_weapon.data.weapon.range = 100;
  equipped_weapon.data.weapon.type = BALLISTIC;

  equipped_wing.type = I_SLOT_WING;
  equipped_wing.rarity = WHITE_RARITY;
  equipped_wing.weapon_type = NOT_WEAPON;
  equipped_wing.data.wing.max_ang_accel = 0.25;
  equipped_wing.data.wing.max_ang_vel = 0.25;

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
    (vec2) { 0.15, 0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_parts_background, "assets/ui/ship_top_view_mask.png");

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
  set_ui_texture(ship_parts.ui_reactor_background, "assets/ui/hud_color_bg.png");
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
  set_ui_texture(ship_parts.ui_reactor_icon, "assets/ui/parts_reactor_icon.png");

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

  ship_parts.ui_shield_background = add_ui_comp(
    ship_parts.ui_ship_top_view, // UI_COMP *parent
    (vec2) { 0.46, -0.05 }, // vec2 pos
    0.08, // float width
    0.08, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(ship_parts.ui_shield_background, "assets/ui/hud_color_bg.png");
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

  ship_parts.ui_weapon_background = add_ui_comp(
    ship_parts.ui_ship_top_view, // UI_COMP *parent
    (vec2) { 0.62, -0.3 }, // vec2 pos
    0.08, // float width
    0.08, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(ship_parts.ui_weapon_background, "assets/ui/hud_color_bg.png");
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

  ship_parts.ui_thruster_background = add_ui_comp(
    ship_parts.ui_ship_top_view, // UI_COMP *parent
    (vec2) { 0.46, -0.8 }, // vec2 pos
    0.08, // float width
    0.08, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(ship_parts.ui_thruster_background, "assets/ui/hud_color_bg.png");
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
  set_ui_texture(ship_parts.ui_thruster_icon, "assets/ui/parts_thruster_icon.png");

  ship_parts.ui_ship_parts_info_background = add_ui_comp(
    ship_parts.ui_ship_parts_root, // UI_COMP *parent
    (vec2) { 0.7, -0.7 }, // vec2 pos
    0.24, // float width
    0.24, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_parts_info_background, "assets/ui/test.png");

  ship_parts.ui_ship_parts_info_title_background = add_ui_comp(
    ship_parts.ui_ship_parts_info_background, // UI_COMP *parent
    (vec2) { 0.025, -0.05 }, // vec2 pos
    0.95, // float width
    0.2, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_parts_info_title_background, "assets/ui/hud_color_bg.png");

  ship_parts.ui_ship_parts_info_title_text = add_ui_comp(
    ship_parts.ui_ship_parts_info_title_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_X
  );
  set_ui_texture(ship_parts.ui_ship_parts_info_title_text, "assets/transparent.png");
  memset(ship_parts_info_title_buffer, '\0', SHIP_PARTS_TEXT_BUFFER_SIZE);
  snprintf(ship_parts_info_title_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE, "[RARITY] TYPE");
  set_ui_text(ship_parts.ui_ship_parts_info_title_text,
              ship_parts_info_title_buffer, 0.08, T_LEFT, fixed_sys, 
              (vec3) { 0.0, 0.0, 0.0 });

  ship_parts.ui_ship_parts_info_content_background = add_ui_comp(
    ship_parts.ui_ship_parts_info_background, // UI_COMP *parent
    (vec2) { 0.025, -0.3 }, // vec2 pos
    0.95, // float width
    0.65, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ship_parts.ui_ship_parts_info_content_background, "assets/ui/hud_color.png");

  ship_parts.ui_ship_parts_info_content_text = add_ui_comp(
    ship_parts.ui_ship_parts_info_content_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X |
    HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_X
  );
  set_ui_texture(ship_parts.ui_ship_parts_info_content_text,
                 "assets/transparent.png");
  memset(ship_parts_info_content_buffer, '\0', SHIP_PARTS_TEXT_BUFFER_SIZE);
  snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE, "EMPTY");
  set_ui_text(ship_parts.ui_ship_parts_info_content_text, ship_parts_info_content_buffer, 
              0.08, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  // set layer to front
  // set_manual_layer(ship_parts.ui_ship_parts_root, 0.01);

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
    set_ui_enabled(ship_parts.ui_ship_parts_root, 0);
  }
}

void toggle_ship_parts() {
  if (ship_parts.ui_ship_parts_root->enabled) {
    set_ui_enabled(ship_parts.ui_ship_parts_root, 0);
    CURSOR_ENABLED = 0;
  } else {
    set_ui_enabled(ship_parts.ui_ship_parts_root, 1);
    set_ui_enabled(inventory.ui_inventory_root, 0);
    CURSOR_ENABLED = 1;
  }
}

void update_ship_parts_icons() {
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

void ship_parts_on_hover_wrapper(UI_COMP *ui_ship_parts, void *arg) {
  ship_parts_on_hover(ui_ship_parts, (I_SLOT *)arg);
}

void ship_parts_on_hover(UI_COMP *ui_ship_parts, I_SLOT *equipped_ship_parts) {
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
  if (equipped_ship_parts->type == I_SLOT_WEAPON ) {
    snprintf(ship_parts_info_title_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE, "[%s] %s", 
          rarity_str[equipped_ship_parts->rarity], item_slot_weapon_type_str[equipped_ship_parts->weapon_type]);
  } else {
    snprintf(ship_parts_info_title_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE, "[%s] %s", 
          rarity_str[equipped_ship_parts->rarity], item_slot_id_str[equipped_ship_parts->type]);
  }
  set_ui_text(ship_parts.ui_ship_parts_info_title_text, ship_parts_info_title_buffer, 
              0.08, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  // Fill content buffer
  switch (equipped_ship_parts->type) {
    case I_SLOT_REACTOR:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
                "[MAX OUTPUT = %.2f]", equipped_ship_parts->data.reactor.max_output);
      break;
    case I_SLOT_HULL:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
                "[MAX HEALTH = %.2f]", equipped_ship_parts->data.hull.max_health);
      break;
    case I_SLOT_SHIELD:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
                "[MAX SHIELD = %.2f] [RECHARGE RATE = %.2f] [RECHARGE DELAY = %.2f] [POWER DRAW = %.2f]", 
                equipped_ship_parts->data.shield.max_shield, equipped_ship_parts->data.shield.recharge_rate, 
                equipped_ship_parts->data.shield.recharge_delay, equipped_ship_parts->data.shield.power_draw);
      break;
    case I_SLOT_WEAPON:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
                "[DAMAGE = %.2f] [FIRE RATE = %.2f] [MAX POWER DRAW = %.2f] [PROJCTION SPEED = %.2f] [RANGE = %.2f]", 
                equipped_ship_parts->data.weapon.damage, equipped_ship_parts->data.weapon.fire_rate, 
                equipped_ship_parts->data.weapon.max_power_draw, equipped_ship_parts->data.weapon.proj_speed, 
                equipped_ship_parts->data.weapon.range);
      break;
    case I_SLOT_WING:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
                "[MAX ANGULAR ACCELERATION = %.2f] [MAX ANGULAR VELOCITY = %.2f]", 
                equipped_ship_parts->data.wing.max_ang_accel, equipped_ship_parts->data.wing.max_ang_vel);
      break;
    case I_SLOT_THRUSTER:
      snprintf(ship_parts_info_content_buffer, SHIP_PARTS_TEXT_BUFFER_SIZE,
                "[MAX ACCELERATION = %.2f] [MAX POWER DRAW = %.2f] [MAX VELOCITY = %.2f]", 
                equipped_ship_parts->data.thruster.max_accel, equipped_ship_parts->data.thruster.max_power_draw, equipped_ship_parts->data.thruster.max_vel);
      break;
    case DEFAULT:
      break;
  }
  set_ui_text(ship_parts.ui_ship_parts_info_content_text, ship_parts_info_content_buffer, 0.08, 
              T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
}

void ship_parts_off_hover_wrapper(UI_COMP *ui_ship_parts, void *arg) {
  ship_parts_off_hover(ui_ship_parts, (I_SLOT *)arg);
}

void ship_parts_off_hover(UI_COMP *ui_ship_parts, I_SLOT *equipped_ship_parts) {
  set_ui_texture(ui_ship_parts, "assets/ui/hud_color_bg.png");
}
