#include <game_over.h>

void game_over() {
  if (!is_game_over) {
    is_game_over = 1;
    /* Stop the player from moving */
    player_ship.cur_speed = 0.0;
    glm_vec3_copy(GLM_VEC3_ZERO, st_player.ent->velocity);
    if (mode == STATION) {
      play_player_death();
    } else {
      pause_ship_audio();
      play_ship_explosion();
    }

    /* Revoke control of the ship or player */
    set_keyboard_enabledness(OFF);
    cursor_on(ON);
    set_game_over_stats();
    set_game_over_screen(ON);
  }
}

void reset_game() {
  is_game_over = 0;
  time(&start_time);
  set_game_over_screen(OFF);
  cursor_on(OFF);
  set_keyboard_enabledness(ON);
  free_timer_queue();
  add_timer(TICK_RATE, tick, FUNCTION_PTR, NULL);
  if (mode == STATION) {
    clear_station_mode();
  } else {
    clear_space_mode();
  }
  /* Resets all stats back to defaults */
  reset_player();

  init_space_mode();
}

int game_over_check() {
  return is_game_over;
}
