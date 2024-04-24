#include <ui/level_ui.h>

void level_ui_initialize() {
  level = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.96, -0.03}, 0.2, 0.025,
                             ABSOLUTE_POS | POS_UNIT_RATIO |
                             WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
                             LINE_UNIT_RATIO_Y);


  set_ui_pivot(level,  PIVOT_CENTER);
  memset(level_buffer, '\0', LEVEL_BUFFER_SIZE);
  set_ui_texture(level, "assets/transparent.png");
  set_ui_enabled(level, 0);
}

void update_level_pos() {
  if (mode != STATION && mode != SPACE) {
    return;
  }
  if (mode == STATION) {
    set_ui_pos(level, (vec2) {0.96, -0.01});
  } else {
    set_ui_pos(level, (vec2) {0.96, -0.025});
  }
}

void update_level() {
  #ifdef __linux__
  snprintf(level_buffer, LEVEL_BUFFER_SIZE, "Game Level: %4ld",
           st_player.total_levels_completed + 1);
  #else
  snprintf(level_buffer, LEVEL_BUFFER_SIZE, "Game Level: %4lld",
           st_player.total_levels_completed + 1);
  #endif

  set_ui_text(level, level_buffer, 0.65, T_CENTER, fixed_sys,
              GLM_VEC3_ONE);
}

void enable_level() {
  set_ui_enabled(level, 1);
}
