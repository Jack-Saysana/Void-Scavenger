#include <ui/console_ui.h>

void console_ui_initialize() {
  console = add_ui_comp(UI_ROOT_COMP, (vec3) { 0.0, 0.0, 0.0 }, 0.5, 32.0,
                        RELATIVE_POS | POS_UNIT_RATIO |
                        WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_PIXEL);
  set_ui_enabled(console, 1);
}

int is_console_enabled() {
  return console->enabled;
}

void enable_console() {
  set_ui_enabled(console, 1);
}

void disable_console() {
  set_ui_enabled(console, 0);
}
