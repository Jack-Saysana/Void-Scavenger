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
    0.2, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_title_background,
                 "assets/ui/hud_color_bg.png");

  inventory.ui_inventory_info_title_text = add_ui_comp(
    inventory.ui_inventory_info_title_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X |
    HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_X
  );
  set_ui_texture(inventory.ui_inventory_info_title_text,
                 "assets/transparent.png");
  memset(inventory_info_title_buffer, '\0', INVENTORY_TEXT_BUFFER_SIZE);
  snprintf(inventory_info_title_buffer, INVENTORY_TEXT_BUFFER_SIZE, "[RARITY] TYPE");
  set_ui_text(inventory.ui_inventory_info_title_text,
              inventory_info_title_buffer, 0.06, T_LEFT, fixed_sys, 
              (vec3) { 0.0, 0.0, 0.0 });
  
  inventory.ui_inventory_info_content_background = add_ui_comp(
    inventory.ui_inventory_info_background, // UI_COMP *parent
    (vec2) { 0.025, -0.3 }, // vec2 pos
    0.95, // float width
    0.65, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_content_background,
                 "assets/ui/hud_color.png");

  inventory.ui_inventory_info_content_text = add_ui_comp(
    inventory.ui_inventory_info_content_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X |
    HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_X
  );
  set_ui_texture(inventory.ui_inventory_info_content_text,
                 "assets/transparent.png");
  memset(inventory_info_content_buffer, '\0', INVENTORY_TEXT_BUFFER_SIZE);
  snprintf(inventory_info_content_buffer, INVENTORY_TEXT_BUFFER_SIZE, "EMPTY");
  set_ui_text(inventory.ui_inventory_info_content_text, inventory_info_content_buffer, 
              0.08, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

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
    set_ui_on_hover(inventory.ui_inventory_slot_background[i],
                    slot_on_hover_wrapper, (void *)(st_player.inventory + i));
    set_ui_no_hover(inventory.ui_inventory_slot_background[i],
                    slot_off_hover_wrapper, (void *)(st_player.inventory + i));

    inventory.ui_inventory_slot_icon[i] = add_ui_comp(
      inventory.ui_inventory_slot_background[i], // UI_COMP *parent
      (vec2) { 0.1, -0.1 }, // vec2 pos
      0.8, // float width
      0.8, // float height
      ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
    );
    set_ui_texture(inventory.ui_inventory_slot_icon[i],
                    "assets/ui/health_icon.png");
    set_ui_on_click(inventory.ui_inventory_slot_icon[i],
                    (void *) slot_on_click, st_player.inventory + i);
  }

  // set init visibility
  set_ui_enabled(inventory.ui_inventory_root, 0);

  return 0;
}

/*
  Update inventory UI per frame, call by general_ui.c update_ui_components()
*/
void update_inventory() {
  for (int i = 0; i < 9; i++) {
    update_slot(inventory.ui_inventory_slot_icon[i], st_player.inventory + i);
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
    set_ui_enabled(ui_esc_root, 0);
    CURSOR_ENABLED = 1;
  }
}

void slot_on_hover_wrapper(UI_COMP *ui_comp, void *arg) {
  // Cast arg back to I_SLOT * and call slot_on_hover
  slot_on_hover(ui_comp, (I_SLOT *)arg);
}

void slot_on_hover(UI_COMP *ui_inventory_slot, I_SLOT *inventory_slot) {
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

  // update when slot item on hover
  set_ui_texture(ui_inventory_slot, "assets/ui/test.png");
  if (inventory_slot->type == I_SLOT_EMPTY) {
    snprintf(inventory_info_title_buffer, INVENTORY_TEXT_BUFFER_SIZE, "[RARITY] TYPE");
    set_ui_text(inventory.ui_inventory_info_title_text,
                inventory_info_title_buffer, 0.08, T_LEFT, fixed_sys, 
                (vec3) { 0.0, 0.0, 0.0 });
    snprintf(inventory_info_content_buffer, INVENTORY_TEXT_BUFFER_SIZE, "EMPTY");
    set_ui_text(inventory.ui_inventory_info_content_text, inventory_info_content_buffer, 
                0.08, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  } else {
    // Fill title buffer
    if (inventory_slot->type == I_SLOT_WEAPON ) {
      snprintf(inventory_info_title_buffer, INVENTORY_TEXT_BUFFER_SIZE, "[%s] %s", 
           rarity_str[inventory_slot->rarity], item_slot_weapon_type_str[inventory_slot->weapon_type]);
    } else {
      snprintf(inventory_info_title_buffer, INVENTORY_TEXT_BUFFER_SIZE, "[%s] %s", 
           rarity_str[inventory_slot->rarity], item_slot_id_str[inventory_slot->type]);
    }
    set_ui_text(inventory.ui_inventory_info_title_text, inventory_info_title_buffer, 
                0.08, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
    // Fill content buffer
    switch (inventory_slot->type) {
      case I_SLOT_REACTOR:
        snprintf(inventory_info_content_buffer, INVENTORY_TEXT_BUFFER_SIZE,
                 "[MAX OUTPUT = %.2f]", inventory_slot->data.reactor.max_output);
        break;
      case I_SLOT_HULL:
        snprintf(inventory_info_content_buffer, INVENTORY_TEXT_BUFFER_SIZE,
                  "[MAX HEALTH = %.2f]", inventory_slot->data.hull.max_health);
        break;
      case I_SLOT_SHIELD:
        snprintf(inventory_info_content_buffer, INVENTORY_TEXT_BUFFER_SIZE,
                  "[MAX SHIELD = %.2f]\n[RECHARGE RATE = %.2f]\n[RECHARGE DELAY = %.2f]\n[POWER DRAW = %.2f]", 
                  inventory_slot->data.shield.max_shield, inventory_slot->data.shield.recharge_rate, 
                  inventory_slot->data.shield.recharge_delay, inventory_slot->data.shield.power_draw);
        break;
      case I_SLOT_WEAPON:
        snprintf(inventory_info_content_buffer, INVENTORY_TEXT_BUFFER_SIZE,
                  "[DAMAGE = %.2f]\n[FIRE RATE = %.2f]\n[MAX POWER DRAW = %.2f]\n[PROJCTION SPEED = %.2f]\n[RANGE = %.2f]", 
                  inventory_slot->data.weapon.damage, inventory_slot->data.weapon.fire_rate, 
                  inventory_slot->data.weapon.max_power_draw, inventory_slot->data.weapon.proj_speed, 
                  inventory_slot->data.weapon.range);
        break;
      case I_SLOT_WING:
        snprintf(inventory_info_content_buffer, INVENTORY_TEXT_BUFFER_SIZE, 
                 "[MAX ANG ACCEL = %.2f]\n[MAX ANG VEL = %.2f]", 
                 inventory_slot->data.wing.max_ang_accel, inventory_slot->data.wing.max_ang_vel);
        break;
      case I_SLOT_THRUSTER:
        snprintf(inventory_info_content_buffer, INVENTORY_TEXT_BUFFER_SIZE, 
                 "[MAX ACCELERATION = %.2f]\n[MAX POWER DRAW = %.2f]\n[MAX VELOCITY = %.2f]", 
                 inventory_slot->data.thruster.max_accel, inventory_slot->data.thruster.max_power_draw, inventory_slot->data.thruster.max_vel);
        break;
      default:
        break;
    }
    set_ui_text(inventory.ui_inventory_info_content_text, inventory_info_content_buffer, 0.06, 
                T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  }
}

void slot_off_hover_wrapper(UI_COMP *ui_comp, void *arg) {
  // Cast arg back to I_SLOT * and call slot_on_hover
  slot_off_hover(ui_comp, (I_SLOT *)arg);
}

void slot_off_hover(UI_COMP *ui_inventory_slot, I_SLOT *inventory_slot) {
  // update when slot item off hover
  set_ui_texture(ui_inventory_slot, "assets/ui/hud_color_bg.png");
}

void slot_on_click(UI_COMP *ui_inventory_slot, I_SLOT *inventory_slot) {
  if (mode == SPACE) {
    // space mode switch ship parts when click
    switch (inventory_slot->type) {
      case I_SLOT_REACTOR:
        switch_slot(&equipped_reactor, inventory_slot);
        player_ship.reactor = equipped_reactor.data.reactor;
        break;
      case I_SLOT_HULL:
        switch_slot(&equipped_hull, inventory_slot);
        player_ship.hull = equipped_hull.data.hull;
        break;
      case I_SLOT_SHIELD:
        switch_slot(&equipped_shield, inventory_slot);
        player_ship.shield = equipped_shield.data.shield;
        player_ship.cur_shield = fmin(player_ship.shield.max_shield,
                                      player_ship.cur_shield);
        player_ship.recharging_shield = 0;
        update_timer_args(ship_shield_recharge_delay, &player_ship,
                          (void *) INVALID_INDEX);
        add_timer(player_ship.shield.recharge_delay,
                  ship_shield_recharge_delay, -1000, &player_ship);
        break;
      case I_SLOT_WEAPON:
        switch_slot(&equipped_weapon, inventory_slot);
        player_ship.weapon = equipped_weapon.data.weapon;
        set_can_shoot(1);
        break;
      case I_SLOT_WING:
        switch_slot(&equipped_wing, inventory_slot);
        player_ship.wing = equipped_wing.data.wing;
        break;
      case I_SLOT_THRUSTER:
        switch_slot(&equipped_thruster, inventory_slot);
        player_ship.thruster = equipped_thruster.data.thruster;
        break;
      case DEFAULT:
        break;
    }
  } else if (mode == STATION) {
    // station mode drop item when click
    for (int i = 0; i < 9 ; i++) {
      if (inventory_slot == st_player.inventory + i) {
        drop_item(i);
      }
    }
    snprintf(inventory_info_title_buffer, INVENTORY_TEXT_BUFFER_SIZE, "[RARITY] TYPE");
    set_ui_text(inventory.ui_inventory_info_title_text,
                inventory_info_title_buffer, 0.08, T_LEFT, fixed_sys, 
                (vec3) { 0.0, 0.0, 0.0 });
    snprintf(inventory_info_content_buffer, INVENTORY_TEXT_BUFFER_SIZE, "EMPTY");
    set_ui_text(inventory.ui_inventory_info_content_text, inventory_info_content_buffer, 
                0.08, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  }
}

void switch_slot(I_SLOT *slot_a, I_SLOT *slot_b) {
  I_SLOT temp_slot;
  temp_slot.type = slot_b->type;
  temp_slot.rarity = slot_b->rarity;
  temp_slot.weapon_type = slot_b->weapon_type;
  temp_slot.data = slot_b->data;

  slot_b->type = slot_a->type;
  slot_b->rarity = slot_a->rarity;
  slot_b->weapon_type = slot_a->weapon_type;
  slot_b->data = slot_a->data;

  slot_a->type = temp_slot.type;
  slot_a->rarity = temp_slot.rarity;
  slot_a->weapon_type = temp_slot.weapon_type;
  slot_a->data = temp_slot.data;
}

void update_slot(UI_COMP *ui_inventory_slot, I_SLOT *inventory_slot) {
  switch (inventory_slot->type) {
    case I_SLOT_EMPTY:
      set_ui_texture(ui_inventory_slot, "assets/transparent.png");
      break;
    case I_SLOT_REACTOR:
      switch (inventory_slot->rarity) {
        case WHITE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_reactor_white.png");
          break;
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
        case WHITE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_hull_white.png");
          break;
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
        case WHITE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_shield_white.png");
          break;
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
            case WHITE_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_laser_white.png");
              break;
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
            case WHITE_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_ballistic_white.png");
              break;
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
            case WHITE_RARITY:
              set_ui_texture(ui_inventory_slot, "assets/ui/parts/w_plasma_white.png");
              break;
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
        case WHITE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_wing_white.png");
          break;
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
        case WHITE_RARITY:
          set_ui_texture(ui_inventory_slot, "assets/ui/parts/i_thruster_white.png");
          break;
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
      set_ui_texture(ui_inventory_slot, "assets/transparent.png");
      break;
  }
}
