#include <game_over.h>

void game_over() {
  /* Stop the player from moving */
  player_ship.cur_speed = 0.0;
  glm_vec3_copy(GLM_VEC3_ZERO, st_player.ent->velocity);

  /* Revoke control of the ship or player */
  set_keyboard_enabledness(OFF);
  cursor_on(ON);
  set_game_over_stats();
  set_game_over_screen(ON);
}

void reset_game() {
  time(&start_time);
  set_game_over_screen(OFF);
  cursor_on(OFF);
  set_keyboard_enabledness(ON);
  free_timer_queue();
  if (mode == STATION) {
    clear_station_mode();
  } else {
    clear_space_mode();
  }
  /* Resets all stats back to defaults */
  reset_player();

  init_space_mode();
}
