#include <loading.h>

/*                                LOADING.H

  Manages the threading for asset loading functionality, and game setup after
  loading is complete

*/

void loading_init() {
  reset_load_state();
  pthread_create(&loading_thread, NULL, load_assets, NULL);
}

int query_loading_status() {
  size_t status = 0;
  if (get_finished_loading()) {
    pthread_join(loading_thread, (void **) &status);
    if (status) {
      return -1;
    }

    mode = MAIN_MENU;
    status = init_game();
    if (status) {
      return -1;
    }
  }
  return 0;
}
