#include <ui/main_menu_ui.h>

void init_main_menu_ui() {
  btn_root = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.75, -0.5 }, 0.15, 0.25,
                         ABSOLUTE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO);
  set_ui_pivot(btn_root, PIVOT_CENTER);
  set_ui_display(btn_root, 0);

  start_btn = init_blue_button(btn_root, (vec2) { 0.0, 0.0 }, 1.0, 0.4,
                               ABSOLUTE_POS | POS_UNIT_RATIO |
                               SIZE_UNIT_RATIO);
  set_ui_text(start_btn, "START GAME", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);

  close_btn = init_blue_button(btn_root, (vec2) { 0.0, -1.0 }, 1.0, 0.4,
                               ABSOLUTE_POS | POS_UNIT_RATIO |
                               SIZE_UNIT_RATIO);
  set_ui_pivot(close_btn, PIVOT_BOTTOM_LEFT);
  set_ui_text(close_btn, "CLOSE GAME", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);

  set_ui_on_click(start_btn, start_game, NULL);
  set_ui_on_click(close_btn, close_game, NULL);
}

void update_main_menu_ui() {
  if (mode == MAIN_MENU) {
    set_ui_enabled(btn_root, 1);
  } else {
    set_ui_enabled(btn_root, 0);
  }
}

void start_game(UI_COMP *comp, void *args) {
  mode = LOADING;
  loading_init();
}

void close_game(UI_COMP *comp, void *args) {
  quit();
}
