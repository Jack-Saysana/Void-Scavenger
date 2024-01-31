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
