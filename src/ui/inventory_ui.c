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
    0.3, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_background, "assets/ui/test.png");

  inventory.ui_inventory_info_title_background = add_ui_comp(
    inventory.ui_inventory_info_background, // UI_COMP *parent
    (vec2) { 0.025, -0.04 }, // vec2 pos
    0.95, // float width
    0.16, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_title_background,
                 "assets/ui/hud_color.png");

  inventory.ui_inventory_info_title_text = add_ui_comp(
    inventory.ui_inventory_info_title_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X |
    HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_title_text,
                 "assets/transparent.png");
  memset(inventory_info_title_buffer, '\0', INVENTORY_TEXT_BUFFER_SIZE);
  snprintf(inventory_info_title_buffer, INVENTORY_TEXT_BUFFER_SIZE,
           "[RARITY] TYPE");
  set_ui_text(inventory.ui_inventory_info_title_text,
              inventory_info_title_buffer, TEXT_LINE_HEIGHT, T_LEFT, fixed_sys,
              (vec3) { 0.0, 0.0, 0.0 });

  inventory.ui_inventory_info_content_background = add_ui_comp(
    inventory.ui_inventory_info_background, // UI_COMP *parent
    (vec2) { 0.025, -0.24 }, // vec2 pos
    0.95, // float width
    0.72, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_content_background,
                 "assets/ui/hud_color_bg.png");
  inventory.ui_inventory_info_content = add_ui_comp(
    inventory.ui_inventory_info_content_background,
    (vec2) { 0.0, -0.05 },
    1.0, 0.95,
    ABSOLUTE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO
  );
  set_ui_texture(inventory.ui_inventory_info_content,
                 "assets/transparent.png");
  /*
  inventory.ui_inventory_info_content_text = add_ui_comp(
    inventory.ui_inventory_info_content_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X |
    HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_info_content_text,
                 "assets/transparent.png");
  memset(inventory_info_content_buffer, '\0', INVENTORY_TEXT_BUFFER_SIZE);
  snprintf(inventory_info_content_buffer, INVENTORY_TEXT_BUFFER_SIZE, "EMPTY");
  set_ui_text(inventory.ui_inventory_info_content_text,
              inventory_info_content_buffer, CONTENT_LINE_HEIGHT, T_LEFT,
              fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  */
  for (int i = 0; i < NUM_INV_INFO_LINES; i++) {
    inventory.ui_inventory_info_lines[i] = add_ui_comp(
      inventory.ui_inventory_info_content,
      (vec2) { 0.05, 0.0 },
      0.7,
      CONTENT_LINE_HEIGHT,
      RELATIVE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO
    );
    set_ui_texture(inventory.ui_inventory_info_lines[i],
                   "assets/transparent.png");
    if (i == 0) {
      memset(inventory_info_buffers[i][0], '\0', INVENTORY_TEXT_BUFFER_SIZE);
      snprintf(inventory_info_buffers[i][0], INVENTORY_TEXT_BUFFER_SIZE,
               "EMPTY");
      set_ui_text(inventory.ui_inventory_info_lines[i],
                  inventory_info_buffers[i][0], 1.0, T_LEFT, fixed_sys,
                  (vec3) { 0.0, 0.0, 0.0 });
    } else {
      set_ui_enabled(inventory.ui_inventory_info_lines[i], 0);
    }

    inventory.ui_inventory_modifier_lines[i] = add_ui_comp(
      inventory.ui_inventory_info_content,
      (vec2) { 0.01, 0.0 },
      0.2,
      CONTENT_LINE_HEIGHT,
      RELATIVE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO
    );
    set_ui_texture(inventory.ui_inventory_modifier_lines[i],
                   "assets/transparent.png");
    if (i == 0) {
      memset(inventory_info_buffers[i][1], '\0',
             INVENTORY_TEXT_BUFFER_SIZE);
      set_ui_text(inventory.ui_inventory_modifier_lines[i],
                  inventory_info_buffers[i][1], 1.0, T_LEFT, fixed_sys,
                  (vec3) { 0.0, 0.0, 0.0 });
    } else {
      set_ui_enabled(inventory.ui_inventory_modifier_lines[i], 0);
    }
  }

  inventory.ui_inventory_background = add_ui_comp(
    inventory.ui_inventory_root, // UI_COMP *parent
    (vec2) { 0.4, -0.15 }, // vec2 pos
    0.33, // float width
    0.33, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(inventory.ui_inventory_background, "assets/ui/test.png");

  for (int i = 0; i < 9; i++) {
    inventory.ui_inventory_slot_background[i] = add_ui_comp(
      inventory.ui_inventory_background, // UI_COMP *parent
      (vec2) { 0.03773585 + 0.03773585 * (i % 3) + (i % 3) * 0.28301887,
               -(0.03773585 + (i / 3) * 0.32075472) }, // vec2 pos
      0.28301887, // float width
      0.28301887, // float height
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
  if (ui_intermediate_root->enabled) {
    return;
  }
  if (inventory.ui_inventory_root->enabled) {
    set_ui_enabled(inventory.ui_inventory_root, 0);
    if (ship_parts.ui_ship_parts_root->enabled) {
      set_ui_enabled(ship_parts.ui_ship_parts_root, 0);
    }
    CURSOR_ENABLED = 0;
  } else {
    set_ui_pos(inventory.ui_inventory_background, (vec2) { 0.4, -0.15 });
    set_ui_width(inventory.ui_inventory_background, 0.5);
    set_ui_height(inventory.ui_inventory_background, 0.5);
    set_ui_pos(inventory.ui_inventory_info_background, (vec2) { 0.15, -0.15 });
    set_ui_enabled(inventory.ui_inventory_root, 1);
    set_ui_enabled(inventory.ui_inventory_info_background, 1);
    set_ui_enabled(inventory.ui_inventory_background, 1);
    set_ui_enabled(skill_tree.ui_skill_tree_root, 0);
    set_ui_enabled(ship_parts.ui_ship_parts_root, 0);
    set_ui_enabled(ui_esc_root, 0);
    set_ui_enabled(ui_render_root, 0);
    set_ui_enabled(ui_control_root, 0);
    CURSOR_ENABLED = 1;
  }
}

void slot_on_hover_wrapper(UI_COMP *ui_comp, void *arg) {
  // Cast arg back to I_SLOT * and call slot_on_hover
  slot_on_hover(ui_comp, (I_SLOT *)arg);
}

void slot_on_hover(UI_COMP *ui_inventory_slot, I_SLOT *inventory_slot) {
  if (!inventory.ui_inventory_info_background->enabled) {
    set_ui_enabled(inventory.ui_inventory_info_background, 1);
  }
  if (ship_parts.ui_ship_parts_info_background->enabled) {
    set_ui_enabled(ship_parts.ui_ship_parts_info_background, 0);
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

  // update when slot item on hover
  set_ui_texture(ui_inventory_slot, "assets/ui/test.png");
  if (inventory_slot->type == I_SLOT_EMPTY) {
    snprintf(inventory_info_title_buffer, INVENTORY_TEXT_BUFFER_SIZE,
            "[RARITY] TYPE");
    set_ui_text(inventory.ui_inventory_info_title_text,
                inventory_info_title_buffer, TEXT_LINE_HEIGHT, T_LEFT,
                fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
    snprintf(inventory_info_buffers[0][0], INVENTORY_TEXT_BUFFER_SIZE,
             "EMPTY");
    set_ui_text(inventory.ui_inventory_info_lines[0],
                inventory_info_buffers[0][0], 1.0, T_LEFT,
                fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
    set_ui_enabled(inventory.ui_inventory_info_lines[0], 1);
    for (int i = 1; i < NUM_INV_INFO_LINES; i++) {
      set_ui_enabled(inventory.ui_inventory_info_lines[i], 0);
    }
    for (int i = 0; i < NUM_INV_INFO_LINES; i++) {
      set_ui_enabled(inventory.ui_inventory_modifier_lines[i], 0);
    }
  } else {
    // Fill title buffer
    if (inventory_slot->type == I_SLOT_WEAPON ) {
      snprintf(inventory_info_title_buffer, INVENTORY_TEXT_BUFFER_SIZE,
               "[%s] %s", rarity_str[inventory_slot->rarity],
               item_slot_weapon_type_str[inventory_slot->weapon_type]);
    } else {
      snprintf(inventory_info_title_buffer, INVENTORY_TEXT_BUFFER_SIZE,
               "[%s] %s", rarity_str[inventory_slot->rarity],
               item_slot_id_str[inventory_slot->type]);
    }
    set_ui_text(inventory.ui_inventory_info_title_text,
                inventory_info_title_buffer, TEXT_LINE_HEIGHT, T_LEFT,
                fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
    // Fill content buffer
    float diffs[7] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    switch (inventory_slot->type) {
      case I_SLOT_REACTOR:
        snprintf(inventory_info_buffers[0][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[MAX OUTPUT = %.2f]",
                 inventory_slot->data.reactor.max_output);
        set_ui_enabled(inventory.ui_inventory_info_lines[0], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[0], 1);
        diffs[0] = inventory_slot->data.reactor.max_output -
               player_ship.reactor.max_output;

        snprintf(inventory_info_buffers[1][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[RECHARGE RATE = %.2F]",
                 inventory_slot->data.reactor.recharge_rate);
        set_ui_enabled(inventory.ui_inventory_info_lines[1], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[1], 1);
        diffs[1] = inventory_slot->data.reactor.recharge_rate -
               player_ship.reactor.recharge_rate;

        snprintf(inventory_info_buffers[2][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[STALL TIME = %.2f]",
                 inventory_slot->data.reactor.stall_time);
        set_ui_enabled(inventory.ui_inventory_info_lines[2], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[2], 1);
        diffs[2] = inventory_slot->data.reactor.stall_time -
               player_ship.reactor.stall_time;

        for (int i = 3; i < NUM_INV_INFO_LINES; i++) {
          set_ui_enabled(inventory.ui_inventory_info_lines[i], 0);
          set_ui_enabled(inventory.ui_inventory_modifier_lines[i], 0);
        }
        break;
      case I_SLOT_HULL:
        snprintf(inventory_info_buffers[0][0], INVENTORY_TEXT_BUFFER_SIZE,
                  "[MAX HEALTH = %.2f]", inventory_slot->data.hull.max_health);
        set_ui_enabled(inventory.ui_inventory_info_lines[0], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[0], 1);
        diffs[0] = inventory_slot->data.hull.max_health -
                   player_ship.hull.max_health;

        for (int i = 1; i < NUM_INV_INFO_LINES; i++) {
          set_ui_enabled(inventory.ui_inventory_info_lines[i], 0);
          set_ui_enabled(inventory.ui_inventory_modifier_lines[i], 0);
        }
        break;
      case I_SLOT_SHIELD:
        snprintf(inventory_info_buffers[0][0], INVENTORY_TEXT_BUFFER_SIZE,
                  "[MAX SHIELD = %.2f]",
                  inventory_slot->data.shield.max_shield);
        set_ui_enabled(inventory.ui_inventory_info_lines[0], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[0], 1);
        diffs[0] = inventory_slot->data.shield.max_shield -
                   player_ship.shield.max_shield;

        snprintf(inventory_info_buffers[1][0], INVENTORY_TEXT_BUFFER_SIZE,
                  "[RECHARGE RATE = %.2f]",
                  inventory_slot->data.shield.recharge_rate);
        set_ui_enabled(inventory.ui_inventory_info_lines[1], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[1], 1);
        diffs[1] = inventory_slot->data.shield.recharge_rate -
                   player_ship.shield.recharge_rate;

        snprintf(inventory_info_buffers[2][0], INVENTORY_TEXT_BUFFER_SIZE,
                  "[RECHARGE DELAY = %.2f]",
                  inventory_slot->data.shield.recharge_delay);
        set_ui_enabled(inventory.ui_inventory_info_lines[2], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[2], 1);
        diffs[2] = inventory_slot->data.shield.recharge_delay -
                   player_ship.shield.recharge_delay;

        snprintf(inventory_info_buffers[3][0], INVENTORY_TEXT_BUFFER_SIZE,
                  "[POWER DRAW = %.2f]",
                  inventory_slot->data.shield.power_draw);
        set_ui_enabled(inventory.ui_inventory_info_lines[3], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[3], 1);
        diffs[3] = inventory_slot->data.shield.power_draw -
                   player_ship.shield.power_draw;

        for (int i = 4; i < NUM_INV_INFO_LINES; i++) {
          set_ui_enabled(inventory.ui_inventory_info_lines[i], 0);
          set_ui_enabled(inventory.ui_inventory_modifier_lines[i], 0);
        }
        break;
      case I_SLOT_WEAPON:
        snprintf(inventory_info_buffers[0][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[DAMAGE = %.2f]", inventory_slot->data.weapon.damage);
        set_ui_enabled(inventory.ui_inventory_info_lines[0], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[0], 1);
        diffs[0] = inventory_slot->data.weapon.damage -
                   player_ship.weapon.damage;

        snprintf(inventory_info_buffers[1][0], INVENTORY_TEXT_BUFFER_SIZE,
                          "[FIRE RATE = %.2f]",
                          inventory_slot->data.weapon.fire_rate);
        set_ui_enabled(inventory.ui_inventory_info_lines[1], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[1], 1);
        diffs[1] = inventory_slot->data.weapon.fire_rate -
                   player_ship.weapon.fire_rate;

        snprintf(inventory_info_buffers[2][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[MAX POWER DRAW = %.2f]",
                 inventory_slot->data.weapon.max_power_draw);
        set_ui_enabled(inventory.ui_inventory_info_lines[2], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[2], 1);
        diffs[2] = inventory_slot->data.weapon.max_power_draw -
                   player_ship.weapon.max_power_draw;

        snprintf(inventory_info_buffers[3][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[PROJ SPEED = %.2f]",
                 inventory_slot->data.weapon.proj_speed);
        set_ui_enabled(inventory.ui_inventory_info_lines[3], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[3], 1);
        diffs[3] = inventory_slot->data.shield.power_draw -
                   player_ship.shield.power_draw;

        snprintf(inventory_info_buffers[4][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[RANGE = %.2f]", inventory_slot->data.weapon.range);
        set_ui_enabled(inventory.ui_inventory_info_lines[4], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[4], 1);
        diffs[4] = inventory_slot->data.weapon.range - player_ship.weapon.range;

        snprintf(inventory_info_buffers[5][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[PROJ SIZE = %.2f]",
                 inventory_slot->data.weapon.bullet_size);
        set_ui_enabled(inventory.ui_inventory_info_lines[5], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[5], 1);
        diffs[5] = inventory_slot->data.weapon.bullet_size -
                   player_ship.weapon.bullet_size;

        snprintf(inventory_info_buffers[6][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[NUM BARRELS = %d]",
                 inventory_slot->data.weapon.num_barrels);
        set_ui_enabled(inventory.ui_inventory_info_lines[6], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[6], 1);
        diffs[6] = inventory_slot->data.weapon.num_barrels -
                   player_ship.weapon.num_barrels;

        break;
      case I_SLOT_WING:
        snprintf(inventory_info_buffers[0][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[MAX ANG ACCEL = %.2f]",
                 inventory_slot->data.wing.max_ang_accel);
        set_ui_enabled(inventory.ui_inventory_info_lines[0], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[0], 1);
        diffs[0] = inventory_slot->data.wing.max_ang_accel -
                   player_ship.wing.max_ang_accel;

        snprintf(inventory_info_buffers[1][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[MAX ANG VEL = %.2f]",
                 inventory_slot->data.wing.max_ang_vel);
        set_ui_enabled(inventory.ui_inventory_info_lines[1], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[1], 1);
        diffs[1] = inventory_slot->data.wing.max_ang_vel -
                   player_ship.wing.max_ang_vel;

        for (int i = 2; i < NUM_INV_INFO_LINES; i++) {
          set_ui_enabled(inventory.ui_inventory_info_lines[i], 0);
          set_ui_enabled(inventory.ui_inventory_modifier_lines[i], 0);
        }
        break;
      case I_SLOT_THRUSTER:
        snprintf(inventory_info_buffers[0][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[MAX ACCELERATION = %.2f]",
                 inventory_slot->data.thruster.max_accel);
        set_ui_enabled(inventory.ui_inventory_info_lines[0], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[0], 1);
        diffs[0] = inventory_slot->data.thruster.max_accel -
                   player_ship.thruster.max_accel;

        snprintf(inventory_info_buffers[1][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[MAX POWER DRAW = %.2f]",
                 inventory_slot->data.thruster.max_power_draw);
        set_ui_enabled(inventory.ui_inventory_info_lines[1], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[1], 1);
        diffs[1] = inventory_slot->data.thruster.max_power_draw -
                   player_ship.thruster.max_power_draw;

        snprintf(inventory_info_buffers[2][0], INVENTORY_TEXT_BUFFER_SIZE,
                 "[MAX VELOCITY = %.2f]",
                 inventory_slot->data.thruster.max_vel);
        set_ui_enabled(inventory.ui_inventory_info_lines[2], 1);
        set_ui_enabled(inventory.ui_inventory_modifier_lines[2], 1);
        diffs[2] = inventory_slot->data.thruster.max_vel -
                   player_ship.thruster.max_vel;

        for (int i = 3; i < NUM_INV_INFO_LINES; i++) {
          set_ui_enabled(inventory.ui_inventory_info_lines[i], 0);
          set_ui_enabled(inventory.ui_inventory_modifier_lines[i], 0);
        }
        break;
      default:
        break;
    }
    for (int i = 0; i < NUM_INV_INFO_LINES; i++) {
      set_ui_text(inventory.ui_inventory_info_lines[i],
                  inventory_info_buffers[i][0], 1.0, T_LEFT,
                  fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
      if (diffs[i] >= 0.0) {
        snprintf(inventory_info_buffers[i][1], INVENTORY_TEXT_BUFFER_SIZE,
                 "[+%.2f]", diffs[i]);
        set_ui_text(inventory.ui_inventory_modifier_lines[i],
                    inventory_info_buffers[i][1], 1.0, T_LEFT,
                    fixed_sys, (vec3) { 0.0, 1.0, 0.0 });
      } else {
        snprintf(inventory_info_buffers[i][1], INVENTORY_TEXT_BUFFER_SIZE,
                 "[%.2f]", diffs[i]);
        set_ui_text(inventory.ui_inventory_modifier_lines[i],
                    inventory_info_buffers[i][1], 1.0, T_LEFT,
                    fixed_sys, (vec3) { 1.0, 0.0, 0.0 });
      }
    }
    /*
    set_ui_text(inventory.ui_inventory_info_content_text,
                inventory_info_content_buffer, CONTENT_LINE_HEIGHT, T_LEFT,
                fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
    */
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
    return;
  } else if (mode == STATION) {
    // switch ship parts when click at intermediate menu
    if (ui_intermediate_root->enabled) {
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
    } else {
      // station mode drop item when click
      for (int i = 0; i < 9 ; i++) {
        if (inventory_slot == st_player.inventory + i) {
          drop_item(i);
        }
      }
      snprintf(inventory_info_title_buffer, INVENTORY_TEXT_BUFFER_SIZE,
               "[RARITY] TYPE");
      set_ui_text(inventory.ui_inventory_info_title_text,
                  inventory_info_title_buffer, TEXT_LINE_HEIGHT, T_LEFT,
                  fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
      snprintf(inventory_info_buffers[0][0], INVENTORY_TEXT_BUFFER_SIZE,
               "EMPTY");
      set_ui_enabled(inventory.ui_inventory_info_lines[0], 1);
      set_ui_text(inventory.ui_inventory_info_lines[0],
                  inventory_info_buffers[0][0], 1.0, T_LEFT,
                  fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
      for (int i = 1; i < NUM_INV_INFO_LINES; i++) {
        set_ui_enabled(inventory.ui_inventory_info_lines[i], 0);
      }
      for (int i = 0; i < NUM_INV_INFO_LINES; i++) {
        set_ui_enabled(inventory.ui_inventory_modifier_lines[i], 0);
      }
    }
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
