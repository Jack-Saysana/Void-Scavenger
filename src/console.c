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
  add_timer(1.5, ce, -1000);
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

void set_gamemode_station() {
  if (mode == STATION) {
    return;
  }
  clear_space_mode();
  init_station_mode();
}

void set_gamemode_space() {
  if (mode == SPACE) {
    return;
  }
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
