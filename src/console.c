/*
                    CONSOLE.c
 Has all of the functions that are called from the parser
 to be used in the console
*/

#include <console.h>

void command_not_found() {
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