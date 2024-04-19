#include <ui/terminal_ui.h>

void init_terminal_ui() {
  terminal_ui = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.5, -0.5 }, 0.25, 0.1,
                            ABSOLUTE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO);
  set_ui_pivot(terminal_ui, PIVOT_CENTER);
  set_ui_text(terminal_ui, term_msg, 0.2, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_texture(terminal_ui, "assets/transparent.png");
  terminal_enabled = 0;
  set_ui_enabled(terminal_ui, 0);
}

void set_terminal_ui(int state) {
  terminal_enabled = state;
  set_ui_enabled(terminal_ui, state);
}

int get_terminal_ui_state() {
  return terminal_enabled;
}
