#include <init.h>

/*                                    INIT.C

  Invokes the initialization functions of the major components of the
  application. Also contains the central cleanup function, which will cleanup
  all allocated resources.

*/

int init_game() {

  // Init required globals
  space_size = BASE_SPACE_SIZE;
  time(&start_time);

  // Add init functions below...
  int status = 0;
  status = init_scene();
  if (status) {
    return -1;
  }

  status = init_controls();
  if (status) {
    return -1;
  }

  status = init_timer_queue();
  status = init_wrapper_buffer();
  if (status) {
    return -1;
  }

  status = init_projectile_buffer();
  if (status) {
    return -1;
  }

  status = init_player();
  if (status) {
    return -1;
  }

  status = init_player_ship();
  if (status) {
    return -1;
  }

  init_ui_components();

  status = init_space_mode();
  // status = init_station_mode();
  if (status) {
    return -1;
  }

  return 0;
}

void cleanup_game() {
  cleanup_scene();
  free_player();
  free_player_ship();
  free_projectile_buffer();
  free_wrapper_buffer();
  // Add cleanup functions above...
  free_timer_queue();
  cleanup_gl();
}
