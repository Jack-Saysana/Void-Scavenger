#include <ui/damage_ui.h>

void init_damage_ui() {
  damage_ui = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.0, 0.0 }, 1.0, 1.0,
                          ABSOLUTE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO);
  set_ui_texture(damage_ui, "assets/ui/damage.png");
  set_ui_enabled(damage_ui, 0);
}

void update_damage_ui() {
  if (damage_state) {
    set_ui_enabled(damage_ui, 1);
  } else {
    set_ui_enabled(damage_ui, 0);
  }
}

void player_health_dmg() {
  damage_state = 1;
  add_timer(0.25, &damage_state, 0, NULL);
}

void reset_dmg_ui_state() {
  damage_state = 0;
}
