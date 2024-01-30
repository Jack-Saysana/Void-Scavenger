#include <ui/console_ui.h>

void console_ui_initialize() {
  console = add_ui_comp(UI_ROOT_COMP, (vec3) { 0.0, 0.0, 0.0 }, 0.5, 32.0,
                        RELATIVE_POS | POS_UNIT_RATIO |
                        WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_PIXEL |
                        LINE_UNIT_RATIO_Y);
  set_ui_enabled(console, 0);
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

void update_console_text(char *cmd) {
  set_ui_text(console, cmd, 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
}
