#include <ui/stallwarning_ui.h>

void stall_ui_initialize() {
  /* Set the coords color to white by default */

  stallwarning = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.5, -0.4}, 2.0, 2.0,
                             ABSOLUTE_POS | POS_UNIT_RATIO |
                             WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
                             LINE_UNIT_RATIO_Y);
  set_ui_pivot(stallwarning, PIVOT_CENTER);
  set_ui_texture(stallwarning, "assets/transparent.png");
  snprintf(stallwarning_text, STALL_BUFFER_SIZE, "REACTOR OFFLINE");
  set_ui_text(stallwarning, stallwarning_text, 0.08, T_CENTER, 
              fixed_sys, (vec3) {0.0, 221.0, 255.0});
  set_ui_enabled(stallwarning, 0);

}

void enable_stallwarning() {
  set_ui_enabled(stallwarning, (stallwarning_enabled = 1));
  if (player_ship.ship_stalled) {
    add_timer(WARNING_TIME, disable_stallwarning, -1000, NULL);
  }
}

void disable_stallwarning() {
  set_ui_enabled(stallwarning, (stallwarning_enabled = 0));
  if (player_ship.ship_stalled) {
    add_timer(WARNING_TIME, enable_stallwarning, -1000, NULL);
  }
}


void start_stallwarning() {
    add_timer(WARNING_TIME, enable_stallwarning, -1000, NULL);
}

void end_stallwarning() {
    snprintf(stallwarning_text, STALL_BUFFER_SIZE, "REACTOR ONLINE");
    set_ui_text(stallwarning, stallwarning_text, 0.08, T_CENTER, 
              fixed_sys, (vec3) {0.0, 1.0, 0.0});
}

void reset_stallwarning() {
    disable_stallwarning();
    snprintf(stallwarning_text, STALL_BUFFER_SIZE, "REACTOR OFFLINE");
    set_ui_text(stallwarning, stallwarning_text, 0.08, T_CENTER, 
                fixed_sys, (vec3) {0.0, 221.0, 255.0});
}

