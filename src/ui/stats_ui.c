#include <ui/stats_ui.h>

/*
                                   STATS
Implements the functionality for defining UI components for both ship mode 
and station mode.
*/

/*
  Init stats UI globaly, call by general_ui.c init_ui_components()

  Return
    0 if successful
    otherwise unsuccessful
*/
int init_stats() {

  stats.ui_stats_root = add_ui_comp(
    UI_ROOT_COMP, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_stats_root, "assets/transparent.png");

  stats.ui_shield_root = add_ui_comp(
    stats.ui_stats_root, // UI_COMP *parent
    (vec2) { 0.04, -0.6 }, // vec2 pos
    0.02, // float width
    0.3, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_shield_root, "assets/transparent.png");


  stats.ui_shield_icon = add_ui_comp(
    stats.ui_shield_root, // UI_COMP *parent
    (vec2) { 0.0, -1.02 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(stats.ui_shield_icon, "assets/ui/shield_icon.png");

  stats.ui_shield_border = add_ui_comp(
    stats.ui_shield_root, // UI_COMP *parent
    (vec2) { 0.1, -1.0 }, // vec2 pos
    0.8, // float width
    -1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_shield_border, "assets/ui/hud_color_bg.png");

  stats.ui_shield_bar = add_ui_comp(
    stats.ui_shield_border, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_shield_bar, "assets/ui/hud_color.png");

  stats.ui_health_root = add_ui_comp(
    stats.ui_stats_root, // UI_COMP *parent
    (vec2) { 0.07, -0.6 }, // vec2 pos
    0.02, // float width
    0.3, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_health_root, "assets/transparent.png");

  stats.ui_health_icon = add_ui_comp(
    stats.ui_health_root, // UI_COMP *parent
    (vec2) { 0.0, -1.02 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(stats.ui_health_icon, "assets/ui/health_icon.png");

  stats.ui_health_border = add_ui_comp(
    stats.ui_health_root, // UI_COMP *parent
    (vec2) { 0.1, -1.0 }, // vec2 pos
    0.8, // float width
    -1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_health_border, "assets/ui/hud_color_bg.png");

  stats.ui_health_bar = add_ui_comp(
    stats.ui_health_border, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_health_bar, "assets/ui/hud_color.png");

  stats.ui_energy_root = add_ui_comp(
    stats.ui_stats_root, // UI_COMP *parent
    (vec2) { 0.1, -0.6 }, // vec2 pos
    0.02, // float width
    0.3, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_energy_root, "assets/transparent.png");

  stats.ui_energy_icon = add_ui_comp(
    stats.ui_energy_root, // UI_COMP *parent
    (vec2) { 0.0, -1.02 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(stats.ui_energy_icon, "assets/ui/energy_icon.png");

  stats.ui_energy_border = add_ui_comp(
    stats.ui_energy_root, // UI_COMP *parent
    (vec2) { 0.1, -1.0 }, // vec2 pos
    0.8, // float width
    -1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_energy_border, "assets/ui/hud_color_bg.png");

  stats.ui_energy_bar = add_ui_comp(
    stats.ui_energy_border, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_energy_bar, "assets/ui/hud_color.png");

  stats.ui_thruster_root = add_ui_comp(
    stats.ui_stats_root, // UI_COMP *parent
    (vec2) { 0.13, -0.6 }, // vec2 pos
    0.02, // float width
    0.3, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_thruster_root, "assets/transparent.png");

  stats.ui_thruster_icon = add_ui_comp(
    stats.ui_thruster_root, // UI_COMP *parent
    (vec2) { 0.0, -1.02 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X
  );
  set_ui_texture(stats.ui_thruster_icon, "assets/ui/thruster_icon.png");

  stats.ui_thruster_border = add_ui_comp(
    stats.ui_thruster_root, // UI_COMP *parent
    (vec2) { 0.1, -1.0 }, // vec2 pos
    0.8, // float width
    -1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_thruster_border, "assets/ui/hud_color_bg.png");

  stats.ui_thruster_bar = add_ui_comp(
    stats.ui_thruster_border, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_thruster_bar, "assets/ui/hud_color.png");

    stats.ui_exp_root = add_ui_comp(
    stats.ui_stats_root, // UI_COMP *parent
    (vec2) { 0.0, -0.99 }, // vec2 pos
    1.0, // float width
    0.01, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_exp_root, "assets/transparent.png");

  stats.ui_exp_border = add_ui_comp(
    stats.ui_exp_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_exp_border, "assets/ui/hud_color_bg.png");

  stats.ui_exp_bar = add_ui_comp(
    stats.ui_exp_border, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    0.8, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(stats.ui_exp_bar, "assets/ui/hud_color.png");

  return 0;
}

/*
  Update stats UI per frame, call by general_ui.c update_ui_components()
*/
void update_stats() {
  // check current game mode
  if (mode == SPACE) {
    switch_space_hud();
    
    // update stats
    // TODO: Should be functional in sprint 2
    set_ui_height(stats.ui_shield_bar, 0.9);
    set_ui_height(stats.ui_health_bar, 0.7);
    set_ui_height(stats.ui_energy_bar, 0.5);
    set_ui_height(stats.ui_thruster_bar, 0.3);

  } else if (mode == STATION) {
    switch_station_hud();

    // update stats
    // TODO: Should be functional in sprint 2
    set_ui_width(stats.ui_shield_bar, 0.9);
    set_ui_width(stats.ui_health_bar, 0.7);
    set_ui_width(stats.ui_exp_bar, 0.5);
  }
}

/*
  Switch current hud to space style hud
*/
void switch_space_hud() {
  // set visibility
  set_ui_enabled(stats.ui_shield_root, 1);
  set_ui_enabled(stats.ui_health_root, 1);
  set_ui_enabled(stats.ui_energy_root, 1);
  set_ui_enabled(stats.ui_thruster_root, 1);
  set_ui_enabled(stats.ui_exp_root, 0);

  // set health bar and shield to space style
  set_ui_pos(stats.ui_shield_root, (vec2) { 0.04, -0.6 });
  set_ui_width(stats.ui_shield_root, 0.02);
  set_ui_height(stats.ui_shield_root, 0.3);
  set_ui_options(stats.ui_shield_root, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y);

  set_ui_pos(stats.ui_shield_icon, (vec2) { 0.0, -1.02 });
  set_ui_width(stats.ui_shield_icon, 1.0);
  set_ui_height(stats.ui_shield_icon, 1.0);
  set_ui_options(stats.ui_shield_root, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X);

  set_ui_pos(stats.ui_shield_border, (vec2) { 0.1, -1.0 });
  set_ui_width(stats.ui_shield_border, 0.8);
  set_ui_height(stats.ui_shield_border, -1.0);
  set_ui_options(stats.ui_shield_root, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y);

  set_ui_pos(stats.ui_shield_bar, (vec2) { 0.0, 0.0 });
  set_ui_width(stats.ui_shield_bar, 1.0);
  set_ui_height(stats.ui_shield_bar, 0.8);
  set_ui_options(stats.ui_shield_root, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y);

  set_ui_pos(stats.ui_health_root, (vec2) { 0.07, -0.6 });
  set_ui_width(stats.ui_health_root, 0.02);
  set_ui_height(stats.ui_health_root, 0.3);
  set_ui_options(stats.ui_health_root, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y);

  set_ui_pos(stats.ui_health_icon, (vec2) { 0.0, -1.02 });
  set_ui_width(stats.ui_health_icon, 1.0);
  set_ui_height(stats.ui_health_icon, 1.0);
  set_ui_options(stats.ui_health_icon, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X);

  set_ui_pos(stats.ui_health_border, (vec2) { 0.1, -1.0 });
  set_ui_width(stats.ui_health_border, 0.8);
  set_ui_height(stats.ui_health_border, -1.0);
  set_ui_options(stats.ui_health_border, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y);

  set_ui_pos(stats.ui_health_bar, (vec2) { 0.0, 0.0 });
  set_ui_width(stats.ui_health_bar, 1.0);
  set_ui_height(stats.ui_health_bar, 0.8);
  set_ui_options(stats.ui_health_bar, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y);
}

/*
  Switch current hud to station style hud
*/
void switch_station_hud() {
  // set visibility
  set_ui_enabled(stats.ui_shield_root, 1);
  set_ui_enabled(stats.ui_health_root, 1);
  set_ui_enabled(stats.ui_energy_root, 0);
  set_ui_enabled(stats.ui_thruster_root, 0);
  set_ui_enabled(stats.ui_exp_root, 1);

  // set health bar and shield to station style
  set_ui_pos(stats.ui_shield_root, (vec2) { 0.06, -0.86 });
  set_ui_width(stats.ui_shield_root, 0.2);
  set_ui_height(stats.ui_shield_root, 0.03);
  set_ui_options(stats.ui_shield_root, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y);

  set_ui_pos(stats.ui_shield_icon, (vec2) { -0.02, 0.0 });
  set_ui_width(stats.ui_shield_icon, -1.0);
  set_ui_height(stats.ui_shield_icon, 1.0);
  set_ui_options(stats.ui_shield_icon, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y);

  set_ui_pos(stats.ui_shield_border, (vec2) { 0.0, 0.0 });
  set_ui_width(stats.ui_shield_border, 1.0);
  set_ui_height(stats.ui_shield_border, 1.0);
  set_ui_options(stats.ui_shield_border, RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y);

  set_ui_pos(stats.ui_shield_bar, (vec2) { 0.0, 0.0 });
  set_ui_width(stats.ui_shield_bar, 1.0);
  set_ui_height(stats.ui_shield_bar, 1.0);
  set_ui_options(stats.ui_shield_bar, RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y);

  set_ui_pos(stats.ui_health_root, (vec2) { 0.06, -0.9 });
  set_ui_width(stats.ui_health_root, 0.2);
  set_ui_height(stats.ui_health_root, 0.03);
  set_ui_options(stats.ui_health_root, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y);

  set_ui_pos(stats.ui_health_icon, (vec2) { -0.02, 0.0 });
  set_ui_width(stats.ui_health_icon, -1.0);
  set_ui_height(stats.ui_health_icon, 1.0);
  set_ui_options(stats.ui_health_icon, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y);

  set_ui_pos(stats.ui_health_border, (vec2) { 0.0, 0.0 });
  set_ui_width(stats.ui_health_border, 1.0);
  set_ui_height(stats.ui_health_border, 1.0);
  set_ui_options(stats.ui_health_border, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y);

  set_ui_pos(stats.ui_health_bar, (vec2) { 0.0, 0.0 });
  set_ui_width(stats.ui_health_bar, 1.0);
  set_ui_height(stats.ui_health_bar, 1.0);
  set_ui_options(stats.ui_health_bar, ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y);
}
