#include <ui/general_ui.h>

void barebones_ui_init() {
  if (import_font("assets/font/fixed_sys.bin",
                  "assets/font/fixed_sys.png",
                  &fixed_sys) == -1) {
    printf("Could not load fixed_sys!\n");
    exit(1);
  }

  init_loading_ui();
}

/*
  Calls all the initialization functions for
  the individual ui components. Called in main
  to initialize all ui components at game start.
*/
void init_ui_components() {
  /* Add ui components initialization functions below... */
  console_ui_initialize();

  // Initialize stats
  if (init_stats()) {
    printf("Could not initialize stats!\n");
    exit(1);
  }

  // Initialize inventory
  if (init_inventory()) {
    printf("Could not initialize inventory!\n");
    exit(1);
  }

  // Initialize ship parts
  if (init_ship_parts()) {
    printf("Could not initialize ship parts!\n");
    exit(1);
  }

  // Initialize skill tree
  if (init_skill_tree()) {
    printf("Could not initialize skill tree!\n");
    exit(1);
  }

  // Initialize ESC menu
  if (init_esc()) {
    printf("Could not initialize ESC menu!\n");
    exit(1);
  }

  // Initialize render menu
  if (init_render()) {
    printf("Could not initialize render menu!\n");
    exit(1);
  }

  // Initialize control menu
  if (init_control()) {
    printf("Could not initialize control menu!\n");
    exit(1);
  }

  // Initialize intermediate menu
  if (init_intermediate()) {
    printf("Could not initialize intermediate menu!\n");
    exit(1);
  }

  coordinates_ui_initialize();
  fps_ui_initialize();
  init_terminal_ui();
  init_target_ui();
  init_radar_ui();
  init_waypoint_ui();
  init_damage_ui();
  init_main_menu_ui();
  game_over_ui_initialize();
  init_item_prompt_ui();
  stall_ui_initialize();
  level_ui_initialize();
}

/*
  General function where all ui components which need per-frame
  updates are called from.
*/
void update_ui_components() {
  update_loading_ui();
  if (mode == LOADING) {
    return;
  }

  if (coordinates_enabled) {
    update_coordinates();
  }
  if (fps_enabled) {
    update_fps();
  }
  // update UI components
  update_level();
  update_stats();
  update_inventory();
  update_ship_parts();
  update_skill_tree();
  update_target_ui();
  update_radar_ui();
  update_waypoint_ui();
  update_damage_ui();
  update_main_menu_ui();
  update_render();
  update_control();
  update_esc();
  update_intermediate();
}
