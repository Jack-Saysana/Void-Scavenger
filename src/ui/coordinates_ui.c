#include <ui/coordinates_ui.h>

void coordinates_ui_initialize() {
  memset(coords, '\0', COORDS_SIZE);
  /* Set the coords color to white by default */
  glm_vec3_copy((vec3) VEC3_WHITE, coords_color);

  coordinates = add_ui_comp(UI_ROOT_COMP, (vec2) { 1.0, 0.0 }, 192.0, 24.0,
                             ABSOLUTE_POS | POS_UNIT_RATIO |
                             WIDTH_UNIT_PIXEL | HEIGHT_UNIT_PIXEL |
                             LINE_UNIT_RATIO_Y);
  set_ui_pivot(coordinates, PIVOT_TOP_RIGHT);
  coordinates_enabled = 1;
  set_ui_texture(coordinates, "assets/transparent.png");

}

void enable_coordinates() {
  set_ui_enabled(coordinates, (coordinates_enabled = 1));
}

void disable_coordinates() {
  set_ui_enabled(coordinates, (coordinates_enabled = 0));
}

void update_coordinates() {
  vec3 c = GLM_VEC3_ZERO_INIT;
  get_player_coordinates(c);
  snprintf(coords, COORDS_SIZE, "X:%.1f Y:%.1f Z:%.1f", c[0], c[1], c[2]);
  set_ui_text(coordinates, coords, 0.65, T_CENTER, fixed_sys, coords_color);
}

void set_coords_warning() {
  if (is_coords_colors_switching){
    return;
  }

  is_coords_colors_switching = 1;
  add_timer(WARNING_TIME, set_coords_color_red, -1000, NULL);
}

void stop_coords_warning() {
  is_coords_colors_switching = 0;
}

void set_coords_color_red() {
  if (is_coords_colors_switching) {
    add_timer(WARNING_TIME, set_coords_color_white, -1000, NULL);
    glm_vec3_copy((vec3) VEC3_RED, coords_color);
  } else {
    glm_vec3_copy((vec3) VEC3_WHITE, coords_color);
  }
}

void set_coords_color_white() {
  if (is_coords_colors_switching) {
    add_timer(WARNING_TIME, set_coords_color_red, -1000, NULL);
    glm_vec3_copy((vec3) VEC3_WHITE, coords_color);
  } else {
    glm_vec3_copy((vec3) VEC3_WHITE, coords_color);
  }
}
