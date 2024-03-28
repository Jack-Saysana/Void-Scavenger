#include <ui/loading_ui.h>

void init_loading_ui() {
  loading_ui_bg = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.0, 0.0 }, 1.0, 1.0,
                              ABSOLUTE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO);

  loading_bar_bg = add_ui_comp(loading_ui_bg, (vec2) { 0.5, -0.75 }, 0.75, 0.05,
                               ABSOLUTE_POS | POS_UNIT_RATIO |
                               SIZE_UNIT_RATIO);
  set_ui_pivot(loading_bar_bg, PIVOT_CENTER);
  set_ui_texture(loading_bar_bg, "./assets/ui/hud_color_bg.png");

  loading_bar = add_ui_comp(loading_bar_bg, (vec2) { 0.0, 0.0 }, 0.5, 1.0,
                            RELATIVE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO);
  set_ui_texture(loading_bar, "./assets/ui/hud_color_20.png");
}

void update_loading_ui() {
  if (mode == LOADING) {
    set_ui_enabled(loading_ui_bg, 1);
    set_ui_width(loading_bar, get_total_load_state());
  } else {
    set_ui_enabled(loading_ui_bg, 0);
  }
}
