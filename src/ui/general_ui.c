#include <ui/general_ui.h>

/*
  Calls all the initialization functions for
  the individual ui components. Called in main
  to initialize all ui components at game start.
*/
void init_ui_components() {
  /* Add ui components initialization functions below... */
  if (import_font("assets/font/fixed_sys.bin",
                  "assets/font/fixed_sys.png",
                  &fixed_sys) == -1) {
    printf("Could not load fixed_sys!\n");
    exit(1);
  }
  console_ui_initialize();

  // Initialize stats
  if (init_stats()) {
    printf("Could not initialize stats!\n");
    exit(1);
  }

  // Initialize inventory
  if (init_inventory()) {
    printf("Could not initialize inventory!\n");
    exit(1);
  }
}
