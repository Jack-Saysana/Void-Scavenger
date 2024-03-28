#include <ui/fps_ui.h>

void fps_ui_initialize() {
  fps = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.5 , -0.025 }, 0.5, 0.05,
                        RELATIVE_POS | POS_UNIT_RATIO |
                        WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
                        LINE_UNIT_RATIO_Y);
  set_ui_pivot(fps, PIVOT_CENTER);
  memset(fps_buffer, '\0', FPS_BUFFER_SIZE);
  set_ui_texture(fps, "assets/transparent.png");
  set_ui_enabled(fps, (fps_enabled = 0));
}

void update_fps() {
  snprintf(fps_buffer, FPS_BUFFER_SIZE, "%.0f fps", 1.0 / REAL_DELTA);
  set_ui_text(fps, fps_buffer, 0.65, T_CENTER, fixed_sys, (vec3) {1.0, 1.0, 1.0});
}

void disable_fps() {
  set_ui_enabled(fps, (fps_enabled = 0));
}

void enable_fps() {
  set_ui_enabled(fps, (fps_enabled = 1));
}
