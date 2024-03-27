#include <ui/item_ui.h>

void init_item_prompt_ui() {
  item_ui = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.5, -0.5 }, 0.1, 0.1,
                            ABSOLUTE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO);
  set_ui_pivot(item_ui, PIVOT_CENTER);
  set_ui_text(item_ui, item_msg, 0.2, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_texture(item_ui, "assets/transparent.png");
  set_ui_enabled(item_ui, (item_prompt_enabled = 0));
}

void set_item_prompt(int state) {
  item_prompt_enabled = state;
  set_ui_enabled(item_ui, state);
}

int get_item_prompt_state() {
  return item_prompt_enabled;
}
