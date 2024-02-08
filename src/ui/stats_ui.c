#include <ui/stats_ui.h>

/*
                                   STATS
Implements the functionality for defining UI components for both ship mode 
and station mode.
*/

/*
  Init stats UI globaly, call by render.c init_scene()

  Return
    0 if successful
    otherwise unsuccessful
*/
int init_stats() {

  // Init UI Components
  stats.ui_stats_root = add_ui_comp(
    UI_ROOT_COMP, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  // set_ui_texture(stats.ui_stats_root, "assets/ui/transparent.png");
  set_ui_display(stats.ui_stats_root, 0);

  stats.ui_shield_root = add_ui_comp(
    stats.ui_stats_root, // UI_COMP *parent
    (vec2) { 0.05, -0.8 }, // vec2 pos
    0.3, // float width
    0.05, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_shield_root, "assets/ui/transparent.png");

  stats.ui_shield_icon = add_ui_comp(
    stats.ui_shield_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    0.95, // float height
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_shield_icon, "assets/ui/shield_icon.png");

  stats.ui_shield_border = add_ui_comp(
    stats.ui_shield_root, // UI_COMP *parent
    (vec2) { 0.05, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_shield_border, "assets/ui/hud_color_bg.png");

  stats.ui_shield_bar = add_ui_comp(
    stats.ui_shield_border, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    0.8, // float width
    1.0, // float height
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_shield_bar, "assets/ui/hud_color.png");

  stats.ui_health_root = add_ui_comp(
    stats.ui_stats_root, // UI_COMP *parent
    (vec2) { 0.05, -0.85 }, // vec2 pos
    0.3, // float width
    0.05, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  // set_ui_texture(stats.ui_health_root, "assets/ui/transparent.png");
  set_ui_display(stats.ui_health_root, 0);

  stats.ui_health_icon = add_ui_comp(
    stats.ui_health_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_health_icon, "assets/ui/health_icon.png");

  stats.ui_health_border = add_ui_comp(
    stats.ui_health_root, // UI_COMP *parent
    (vec2) { 0.05, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_health_border, "assets/ui/hud_color_bg.png");

  stats.ui_health_bar = add_ui_comp(
    stats.ui_health_border, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    0.8, // float width
    1.0, // float height
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_health_bar, "assets/ui/hud_color.png");

  // Do not have velocity var
  // stats.ui_velocity_text = add_ui_comp(
  //   stats.ui_stats_root, // UI_COMP *parent
  //   (vec2) { 0.55, -0.6 }, // vec2 pos
  //   0.3, // float width
  //   0.05, // float height
  //   ABSOLUTE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO | LINE_UNIT_RATIO_Y
  // );
  // set_ui_texture(stats.ui_velocity_text, "assets/ui/transparent.png");
  // set_ui_text(stats.ui_velocity_text, "37357 mph", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.867, 1.0 });

  stats.ui_exp_root = add_ui_comp(
    stats.ui_stats_root, // UI_COMP *parent
    (vec2) { 0.0, -0.99 }, // vec2 pos
    1.0, // float width
    0.01, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  // set_ui_texture(stats.ui_exp_root, "assets/ui/transparent.png");
  set_ui_display(stats.ui_exp_root, 0);

  stats.ui_exp_border = add_ui_comp(
    stats.ui_exp_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_exp_border, "assets/ui/hud_color_bg.png");

  stats.ui_exp_bar = add_ui_comp(
    stats.ui_exp_border, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    0.8, // float width
    1.0, // float height
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_exp_bar, "assets/ui/hud_color.png");

  stats.ui_energy_root = add_ui_comp(
    stats.ui_stats_root, // UI_COMP *parent
    (vec2) { 0.2, -0.3 }, // vec2 pos
    0.03, // float width
    0.33, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  // set_ui_texture(stats.ui_energy_root, "assets/ui/transparent.png");
  set_ui_display(stats.ui_energy_root, 0);

  stats.ui_energy_border = add_ui_comp(
    stats.ui_energy_root, // UI_COMP *parent
    (vec2) { 0.1, 0.0 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_energy_border, "assets/ui/hud_color_bg.png");

  stats.ui_energy_bar = add_ui_comp(
    stats.ui_energy_border, // UI_COMP *parent
    (vec2) { 0.0, -1.0 }, // vec2 pos
    1.0, // float width
    -0.8, // float height
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_energy_bar, "assets/ui/hud_color.png");

  stats.ui_thruster_root = add_ui_comp(
    stats.ui_stats_root, // UI_COMP *parent
    (vec2) { 0.24, -0.3 }, // vec2 pos
    0.03, // float width
    0.33, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  // set_ui_texture(stats.ui_thruster_root, "assets/ui/transparent.png");
  set_ui_display(stats.ui_thruster_root, 0);


  stats.ui_thruster_border = add_ui_comp(
    stats.ui_thruster_root, // UI_COMP *parent
    (vec2) { 0.1, 0.0 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_thruster_border, "assets/ui/hud_color_bg.png");

  stats.ui_thruster_bar = add_ui_comp(
    stats.ui_thruster_border, // UI_COMP *parent
    (vec2) { 0.0, -1.0 }, // vec2 pos
    1.0, // float width
    -0.8, // float height
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_thruster_bar, "assets/ui/hud_color.png");

  return 0;
}

/*
  Update stats UI per frame, call by render.c render_scene()
*/
void update_stats() {
  // check current game mode
  if (mode == SPACE) {
    // disable exp ui
    set_ui_enabled(stats.ui_exp_root, 0);
    // update health and shield
    stats.ui_health_bar->width = player_ship.cur_health / player_ship.hull.max_health;
    stats.ui_shield_bar->width = player_ship.cur_shield / player_ship.shield.max_shield;
  } else if (mode == STATION) {
    // disable exp ui
    set_ui_enabled(stats.ui_exp_root, 1);
    // update health and exp
    stats.ui_health_bar->width = st_player.cur_health / st_player.max_health;
    stats.ui_shield_bar->width = st_player.cur_shield / st_player.max_shield;
    stats.ui_exp_bar->width = st_player.cur_experience / st_player.max_experience;
  }
}
