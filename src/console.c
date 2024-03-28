/*
                    CONSOLE.c
 Has all of the functions that are called from the parser
 to be used in the console
*/

#include <console.h>

void close_error_message() {
  disable_console_error();
}

void show_error_message(const char *error) {
  set_console_error(error);
  close_error ce = &close_error_message;
  add_timer(1.5, ce, -1000, NULL);
}

void command_not_found() {
  show_error_message("Command not found!");
  fprintf(stderr, "Command not found!\n");
  print_parse_table();
}

void cursor_on(int on) {
  if (on) {
    CURSOR_ENABLED = 1;
  } else {
    CURSOR_ENABLED = 0;
  }
}

void eshoot_on(int on) {
  if (on) {
    ESHOOT_ON = 1;
  } else {
    ESHOOT_ON = 0;
  }
}

void set_gun(S_WEAPON_T type) {
  if (type == BALLISTIC) {
    player_ship.weapon.type = BALLISTIC;
    player_ship.weapon.fire_rate = S_BASE_FIRERATE;
  } else if (type == LASER) {
    player_ship.weapon.type = LASER;
    player_ship.weapon.fire_rate = S_BASE_FIRERATE_LASER;
  } else {
    player_ship.weapon.type = PLASMA;
    player_ship.weapon.fire_rate = S_BASE_FIRERATE;
  }
}

void set_gamemode_station() {
  if (mode == STATION) {
    return;
  }
  free_timer_queue();
  clear_space_mode();
  init_station_mode();
}

void set_gamemode_space() {
  if (mode == SPACE) {
    return;
  }
  free_timer_queue();
  clear_station_mode();
  init_space_mode();
}

void quit() {
  cleanup_game();
  exit(0);
}

void set_player_station_speed(float input) {
  st_player.speed = input;
}

void set_sim_dist(float dist) {
  SIM_DIST = dist;
  refresh_sim_distances();
}

void set_render_dist(float dist) {
  RENDER_DIST = dist;
  refresh_sim_distances();
}

void reset_station() {
  clear_station_mode();
  init_station_mode();
}

void reset_space() {
  clear_space_mode();
  init_space_mode();
}

void fps_toggle() {
  if (!fps_enabled) {
    fps_enabled = 1;
    enable_fps();
  } else {
    fps_enabled = 0;
    disable_fps();
  }
}

void set_arena(float size) {
  space_size = size;
  reset_space();
}

void set_player_health(float health, int mode) {
  if (mode == SPACE) {
    player_ship.cur_health = health;
  } else {
    st_player.cur_health = health;
  }
}

void set_player_shield(float shield, int mode) {
  if (mode == SPACE) {
    player_ship.cur_shield = shield;
  } else {
    st_player.cur_shield = shield;
  }
}

void toggle_item_glow() {
  item_glow = !item_glow;
}
void set_player_xp(float xp) {
  st_player.cur_experience = xp;
}

void set_gamelevel(float gamelevel) {
  st_player.total_levels_completed = gamelevel;
  if (mode == SPACE) {
    reset_space();
  } else {
    reset_station();
  }
}
