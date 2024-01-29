#include <init.h>

/*                                    INIT.C

  Invokes the initialization functions of the major components of the
  application. Also contains the central cleanup function, which will cleanup
  all allocated resources.

*/

int init_game() {
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

  init_ui_components();  

  return 0;
}

void cleanup_game() {
  cleanup_scene();
  // Add cleanup functions above...
  cleanup_gl();
}
