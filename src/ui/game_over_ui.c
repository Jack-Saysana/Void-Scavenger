#include <ui/game_over_ui.h>

void game_over_ui_initialize() {
  /* Root component - all children for game over screen are parented by */
  game_over_root = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.5, -0.5 }, 0.45,
                               0.45 * INVERSE_GOLDEN_RATIO,
                               RELATIVE_POS | POS_UNIT_RATIO |
                               WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X |
                               LINE_UNIT_RATIO_Y);
  set_ui_enabled(game_over_root, OFF);
  set_ui_pivot(game_over_root, PIVOT_CENTER);
  set_ui_texture(game_over_root, "assets/ui/hud_color_bg.png");

  game_over_stats = add_ui_comp(game_over_root, (vec2) { 0.5, -0.45 }, 0.55,
                                 0.55 * INVERSE_GOLDEN_RATIO,
                                 RELATIVE_POS | POS_UNIT_RATIO |
                                 WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X |
                                 LINE_UNIT_RATIO_Y);
  set_ui_pivot(game_over_stats, PIVOT_CENTER);
  set_ui_texture(game_over_stats, "assets/ui/hud_color.png");
  set_ui_enabled(game_over_stats, ON);

  game_over_title = add_ui_comp(game_over_root, (vec2) { 0.5, -0.075 }, 0.75,
                                0.75 * INVERSE_GOLDEN_RATIO,
                                ABSOLUTE_POS | POS_UNIT_RATIO |
                                WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X |
                                LINE_UNIT_RATIO_Y);
  set_ui_pivot(game_over_title, PIVOT_CENTER);
  set_ui_texture(game_over_title, "assets/transparent.png");
  set_ui_text(game_over_title, "GAME OVER", 0.25, T_CENTER, fixed_sys,
              GLM_VEC3_ZERO);

  game_over_restart = add_ui_comp(game_over_root, (vec2) { 0.25, -0.85 }, 0.175,
                                  0.175 * INVERSE_GOLDEN_RATIO,
                                  ABSOLUTE_POS | POS_UNIT_RATIO |
                                  WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X |
                                  LINE_UNIT_RATIO_Y);
  set_ui_pivot(game_over_restart, PIVOT_CENTER);
  set_ui_text(game_over_restart, "RESTART", 0.35, T_CENTER, fixed_sys,
              GLM_VEC3_ZERO);
  set_ui_texture(game_over_restart, "assets/ui/test.png");
  set_ui_enabled(game_over_restart, ON);
  set_ui_on_release(game_over_restart, reset_game, NULL);

  game_over_quit = add_ui_comp(game_over_root, (vec2) { 0.75, -0.85 }, 0.175,
                               0.175 * INVERSE_GOLDEN_RATIO,
                               ABSOLUTE_POS | POS_UNIT_RATIO |
                               WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_X |
                               LINE_UNIT_RATIO_Y);
  set_ui_pivot(game_over_quit, PIVOT_CENTER);
  set_ui_text(game_over_quit, "QUIT", 0.35, T_CENTER, fixed_sys,
              GLM_VEC3_ZERO);
  set_ui_texture(game_over_quit, "assets/ui/test.png");
  set_ui_enabled(game_over_quit, ON);
  set_ui_on_release(game_over_quit, quit, NULL);
}

void set_game_over_screen(int set) {
  set_ui_enabled(game_over_root, set);
  if (set) {
    set_ui_enabled(ui_esc_root, 0);
    set_ui_enabled(ui_render_root, 0);
    set_ui_enabled(ui_control_root, 0);
    set_ui_enabled(inventory.ui_inventory_root, 0);
    set_ui_enabled(skill_tree.ui_skill_tree_root, 0);
    set_ui_enabled(ship_parts.ui_ship_parts_root, 0);
  }
}

void set_game_over_stats() {
  time_t cur_time;
  time(&cur_time);
  float time_played = difftime(cur_time, start_time);
  float minutes_played = time_played / 60.0;
  float hours_played = minutes_played / 60.0;
  if (minutes_played >= 1.0) {
    time_played = fmodf(time_played, 60.0);
  }
  #ifdef __linux
  snprintf(game_over_stats_buffer, GAME_OVER_STATS_SIZE,
           " Levels Completed: %ld\n"
           " Distance Flown: %.1lf\n"
           " Distance Walked: %.1lf\n"
           " Aliens Defeated: %ld\n"
           " Ships Defeated: %ld\n"
           " Damage Dealt: %.1lf\n"
           " Damage Taken: %.1lf\n"
           " Total Experience %.1lf\n"
           " Time Played: %.0f hrs %.0f min %.0f sec\n",
           st_player.total_levels_completed,
           st_player.total_distance_flown,
           st_player.total_distance_walked,
           st_player.total_enemies_defeated,
           st_player.total_ships_defeated,
           st_player.total_damage_dealt,
           st_player.total_damage_taken,
           st_player.total_experience,
           hours_played,
           minutes_played,
           time_played
           );
  #else
  snprintf(game_over_stats_buffer, GAME_OVER_STATS_SIZE,
           " Levels Completed: %lld\n"
           " Distance Flown: %.1lf\n"
           " Distance Walked: %.1lf\n"
           " Aliens Defeated: %lld\n"
           " Ships Defeated: %lld\n"
           " Damage Dealt: %.1lf\n"
           " Damage Taken: %.1lf\n"
           " Total Experience %.1lf\n"
           " Time Played: %.0f hrs %.0f min %.0f sec\n",
           st_player.total_levels_completed,
           st_player.total_distance_flown,
           st_player.total_distance_walked,
           st_player.total_enemies_defeated,
           st_player.total_ships_defeated,
           st_player.total_damage_dealt,
           st_player.total_damage_taken,
           st_player.total_experience,
           hours_played,
           minutes_played,
           time_played
           );
  #endif
  set_ui_text(game_over_stats, game_over_stats_buffer,
              0.10, T_LEFT, fixed_sys, GLM_VEC3_ZERO);
}
