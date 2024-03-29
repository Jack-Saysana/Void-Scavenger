#include <ui/waypoint_ui.h>

void init_waypoint_ui() {
  station_waypoint = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.5, -0.5 }, 0.1, 0.1,
                                ABSOLUTE_POS | POS_UNIT_RATIO |
                                SIZE_UNIT_RATIO_Y);
  set_ui_texture(station_waypoint, "assets/ui/waypoint_blue.png");
  set_ui_enabled(station_waypoint, 1);
  set_ui_pivot(station_waypoint, PIVOT_CENTER);

}

void update_waypoint_ui() {
  if (mode != SPACE) {
    station_waypoint_enabled = 0;
  }

  if (station_waypoint_enabled) {
    set_ui_enabled(station_waypoint, 1);
    vec4 station_pos = { 0.0, 0.0, 0.0, 1.0 };
    get_sp_station_pos(station_pos);

    to_screen_space(station_pos, station_pos);

    station_pos[X] /= station_pos[W];
    station_pos[Y] /= station_pos[W];
    station_pos[X] = (station_pos[X] + 1.0) / 2.0;
    station_pos[Y] = (station_pos[Y] - 1.0) / 2.0;

    // Clamp target so it does not go off screen
    station_pos[X] = fmax(0.0, fmin(station_pos[X], 1.0));
    station_pos[Y] = fmax(-1.0, fmin(station_pos[Y], 0.0));

    // Clamp target to edge of screen if target is behind player
    if (station_pos[Z] < 0.0) {
      if (fmin(station_pos[X], 1.0 - station_pos[X]) <
          fmin(abs(station_pos[Y]), 1.0 - abs(station_pos[Y]))) {
        if (station_pos[X] < 0.5) {
          station_pos[X] = 0.0;
        } else {
          station_pos[X] = 1.0;
        }
      } else {
        if (station_pos[Y] > -0.5) {
          station_pos[Y] = -1.0;
        } else {
          station_pos[Y] = 0.0;
        }
      }
    }

    set_ui_pos(station_waypoint, station_pos);
  } else {
    set_ui_enabled(station_waypoint, 0);
  }
}

void toggle_st_waypoint() {
  station_waypoint_enabled = !station_waypoint_enabled;
}

void set_st_waypoint_enabled(int enabled) {
  station_waypoint_enabled = enabled;
}
