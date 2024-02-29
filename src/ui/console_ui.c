#include <ui/console_ui.h>

void console_ui_initialize() {
  /* Root component - All console components are children of this */
  console_root = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.0, 0.0 }, 1.0, 1.0,
                             ABSOLUTE_POS | POS_UNIT_RATIO |
                             WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
                             LINE_UNIT_RATIO_Y);
  set_ui_enabled(console_root, 0);
  set_ui_pivot(console_root, PIVOT_TOP_LEFT);
  set_ui_display(console_root, 0);

  /* Actual console itself */
  console = add_ui_comp(console_root, (vec2) { 0.0 , 0.0 }, 0.5, 0.05,
                        RELATIVE_POS | POS_UNIT_RATIO |
                        WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
                        LINE_UNIT_RATIO_Y);
  set_ui_pivot(console, PIVOT_TOP_LEFT);
  set_ui_enabled(console, 1);
  set_ui_texture(console, "assets/transparent.png");


  /* Console error component - is only shown when error occurs */
  console_error = add_ui_comp(console_root, (vec2) { 0.0, -0.05 }, 0.500001, 0.05,
                            RELATIVE_POS | POS_UNIT_RATIO |
                            WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
                            LINE_UNIT_RATIO_Y);
  set_ui_pivot(console_error, PIVOT_TOP_LEFT);
  set_ui_enabled(console_error, 0);
  set_ui_texture(console_error, "assets/transparent.png");

  /* Console cursor - tracks how many characters have been typed */
  console_cursor = add_ui_comp(console_root, (vec2) { 0.0, 0.0 }, 0.5, 0.05,
                        ABSOLUTE_POS | POS_UNIT_RATIO |
                        WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
                        LINE_UNIT_RATIO_Y);
  set_ui_pivot(console_cursor, PIVOT_TOP_LEFT);
  set_ui_enabled(console_cursor, 1);
  cons_cursor_enabled = 1;
  set_ui_texture(console_cursor, "assets/transparent.png");
}

int is_console_enabled() {
  return console_root->enabled;
}

void enable_console() {
  set_ui_enabled(console_root, 1);
}

void disable_console() {
  set_ui_enabled(console_root, 0);
}

/* =============== CONSOLE =============== */

void update_console_text(char *cmd) {
  set_ui_text(console, cmd, 0.75, T_LEFT, fixed_sys, GLM_VEC3_ONE);
}

/* =============== CONSOLE ERROR =============== */

void set_console_error(char *error) {
  set_ui_text(console_error, error, 0.75, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_enabled(console_error, 1);
}

void disable_console_error() {
  set_ui_enabled(console_error, 0);
}

/* ============== CONSOLE CURSOR ================= */

void update_console_cursor(char *string) {
  set_ui_text(console_cursor, string, 0.75, T_LEFT, fixed_sys, GLM_VEC3_ONE);
}

void disable_console_cursor() {
  set_ui_enabled(console_cursor, 0);
  cons_cursor_enabled = 0;
}

void enable_console_cursor() {
  set_ui_enabled(console_cursor, 1);
  cons_cursor_enabled = 1;
}
