#include <ui/render_ui.h>

/*
                                   RENDER
Implements the functionality for defining UI components for render menu.
*/

/*
  Init render UI globaly, call by general_ui.c init_ui_components()

  Return
    0 if successful
    otherwise unsuccessful
*/
int init_render() {
  last_game_mode = SPACE;

  ui_render_root = add_ui_comp(
    UI_ROOT_COMP, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_render_root, "assets/transparent.png");

  ui_render_background = add_ui_comp(
    ui_render_root, // UI_COMP *parent
    (vec2) { 0.4, -0.2125 }, // vec2 pos
    0.2, // float width
    0.575, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_render_background, "assets/ui/hud_color_bg.png");

  ui_render_back_root = add_ui_comp(
    ui_render_background, // UI_COMP *parent
    (vec2) { 0.0625, -0.04347826 }, // vec2 pos
    0.875, // float width
    0.17391304, // float height
    //ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(ui_render_back_root, "assets/transparent.png");

  ui_render_back_button = init_blue_button(
    ui_render_back_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_render_back_button, "BACK", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_render_back_button, (void *) render_back_on_click, NULL);

  ui_render_render_distance_root = add_ui_comp(
    ui_render_background, // UI_COMP *parent
    //(vec2) { 0.0625, -0.26086956 }, // vec2 pos
    //(vec2) { 0.0625, -0.24 }, // vec2 pos
    (vec2) { 0.0625, 0.0 }, // vec2 pos
    0.875, // float width
    0.17391304, // float height
    //ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_render_render_distance_root, "assets/transparent.png");

  ui_render_render_distance_title_text = add_ui_comp(
    ui_render_render_distance_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    0.4, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_render_render_distance_title_text, "assets/transparent.png");
  set_ui_text(ui_render_render_distance_title_text, "RENDER DISTANCE", 0.625, T_CENTER, fixed_sys, GLM_VEC3_ZERO);

  ui_render_render_distance_minus_button = init_blue_button(
    ui_render_render_distance_root, // UI_COMP *parent
    (vec2) { 0.0, -0.4 }, // vec2 pos
    0.15, // float width
    0.6, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_render_render_distance_minus_button, "<", 0.42, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_render_render_distance_minus_button, (void *) render_distance_minus_on_click, NULL);

  ui_render_render_distance_value_text = add_ui_comp(
    ui_render_render_distance_root, // UI_COMP *parent
    (vec2) { 0.15, -0.4 }, // vec2 pos
    0.7, // float width
    0.6, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_render_render_distance_value_text, "assets/transparent.png");
  memset(render_distance_buffer, '\0', RENDER_BUFFER_SIZE);
  snprintf(render_distance_buffer, RENDER_BUFFER_SIZE, "%d", render_distance_multiplier);
  set_ui_text(ui_render_render_distance_value_text, render_distance_buffer, 0.42, T_CENTER, fixed_sys, GLM_VEC3_ZERO);

  ui_render_render_distance_plus_button = init_blue_button(
    ui_render_render_distance_root, // UI_COMP *parent
    (vec2) { 0.85, -0.4 }, // vec2 pos
    0.15, // float width
    0.6, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_render_render_distance_plus_button, ">", 0.42, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_render_render_distance_plus_button, (void *) render_distance_plus_on_click, NULL);

  ui_resolution_root = add_ui_comp(
    ui_render_background, // UI_COMP *parent
    //(vec2) { 0.0625, -0.47826086 }, // vec2 pos
    (vec2) { 0.0625, 0.0 }, // vec2 pos
    0.875, // float width
    //0.17391304, // float height
    0.24, // float height
    //ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_resolution_root, "assets/transparent.png");

  ui_resolution_title_text = add_ui_comp(
    ui_resolution_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    0.325, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_resolution_title_text, "assets/transparent.png");
  set_ui_text(ui_resolution_title_text, "RESOLUTION", 0.625, T_CENTER,
              fixed_sys, GLM_VEC3_ZERO);

  ui_resolution_minus_button = init_blue_button(
    ui_resolution_root, // UI_COMP *parent
    (vec2) { 0.0, -0.3 }, // vec2 pos
    0.15, // float width
    0.4, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    SIZE_UNIT_RATIO
  );
  set_ui_text(ui_resolution_minus_button, "<", 0.42, T_CENTER, fixed_sys,
              GLM_VEC3_ONE);
  set_ui_on_click(ui_resolution_minus_button, (void *) change_resolution,
                  (void *) 0);

  ui_resolution_value_text = add_ui_comp(
    ui_resolution_root, // UI_COMP *parent
    (vec2) { 0.15, -0.3 }, // vec2 pos
    0.7, // float width
    0.3, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_resolution_value_text, "assets/transparent.png");
  set_ui_text(ui_resolution_value_text, resolution_names[cur_res], 0.42,
              T_CENTER, fixed_sys, GLM_VEC3_ZERO);

  ui_resolution_plus_button = init_blue_button(
    ui_resolution_root, // UI_COMP *parent
    (vec2) { 0.85, -0.3 }, // vec2 pos
    0.15, // float width
    0.4, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    SIZE_UNIT_RATIO
  );
  set_ui_text(ui_resolution_plus_button, ">", 0.42, T_CENTER, fixed_sys,
              GLM_VEC3_ONE);
  set_ui_on_click(ui_resolution_plus_button, (void *) change_resolution,
                  (void *) 1);

  ui_resolution_apply_button = init_blue_button(
    ui_resolution_root, // UI_COMP *parent
    (vec3) { 0.5, -1.0 }, // vec2 pos
    0.5, // float width
    0.25, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    SIZE_UNIT_RATIO
  );
  set_ui_pivot(ui_resolution_apply_button, PIVOT_BOTTOM);
  set_ui_text(ui_resolution_apply_button, "APPLY", 0.5, T_CENTER, fixed_sys,
              GLM_VEC3_ONE);
  set_ui_on_click(ui_resolution_apply_button, (void *) update_resolution,
                  NULL);

  ui_windowed_root = add_ui_comp(
    ui_render_background, // UI_COMP *parent
    //(vec2) { 0.0625, -0.715 }, // vec2 pos
    (vec2) { 0.0625, -0.05 }, // vec2 pos
    0.875, // float width
    //0.17391304, // float height
    0.11, // float height
    //ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_render_render_distance_root, "assets/transparent.png");


  ui_windowed_button = init_blue_button(
    ui_windowed_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_windowed_button, "WINDOWED: OFF", 0.25, T_CENTER,
              fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_windowed_button, (void *) toggle_windowed, NULL);

  ui_render_glowing_items_root = add_ui_comp(
    ui_render_background, // UI_COMP *parent
    //(vec2) { 0.0625, -0.78260868 }, // vec2 pos
    (vec2) { 0.0625, -0.05 }, // vec2 pos
    0.875, // float width
    //0.17391304, // float height
    0.11, // float height
    //ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
    RELATIVE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y |
    SIZE_UNIT_RATIO
  );
  set_ui_texture(ui_render_render_distance_root, "assets/transparent.png");


  ui_render_glowing_items_button = init_blue_button(
    ui_render_glowing_items_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | SIZE_UNIT_RATIO
  );
  set_ui_text(ui_render_glowing_items_button, "GLOWING ITEMS: OFF", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  set_ui_on_click(ui_render_glowing_items_button, (void *) glowing_items_on_click, NULL);

  set_ui_enabled(ui_render_root, 0);
  return 0;
}

void update_render() {
  if (item_glow == 1) {
    set_ui_text(ui_render_glowing_items_button, "GLOWING ITEMS: ON", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  } else {
    set_ui_text(ui_render_glowing_items_button, "GLOWING ITEMS: OFF", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);
  }

  if (windowed) {
    set_ui_text(ui_windowed_button, "WINDOWED: ON", 0.25, T_CENTER,
                fixed_sys, GLM_VEC3_ONE);
    set_ui_enabled(ui_resolution_root, 0);
  } else {
    set_ui_text(ui_windowed_button, "WINDOWED: OFF", 0.25, T_CENTER,
                fixed_sys, GLM_VEC3_ONE);
    set_ui_enabled(ui_resolution_root, 1);
  }

  snprintf(render_distance_buffer, RENDER_BUFFER_SIZE, "%d", render_distance_multiplier);
  set_ui_text(ui_render_render_distance_value_text, render_distance_buffer, 0.42, T_CENTER, fixed_sys, GLM_VEC3_ZERO);

  if (last_game_mode != mode) {
    if (mode == SPACE) {
      set_render_dist((SP_BASE_RENDER_DIST / 100) * render_distance_multiplier);
      set_sim_dist((SP_BASE_SIM_DIST / 100) * render_distance_multiplier);
    } else if (mode == STATION) {
      set_render_dist((ST_BASE_RENDER_DIST / 100) * render_distance_multiplier);
      set_sim_dist((ST_BASE_SIM_DIST / 100) * render_distance_multiplier);
    }
    last_game_mode = mode;
  }
}

void render_back_on_click() {
  set_ui_enabled(ui_esc_root, 1);
  set_ui_enabled(ui_render_root, 0);
}

void render_distance_minus_on_click() {
  if (render_distance_multiplier > 5) {
    render_distance_multiplier -= 5;
  }

  if (mode == SPACE) {
    set_render_dist((SP_BASE_RENDER_DIST / 100) * render_distance_multiplier);
    set_sim_dist((SP_BASE_SIM_DIST / 100) * render_distance_multiplier);
  } else if (mode == STATION) {
    set_render_dist((ST_BASE_RENDER_DIST / 100) * render_distance_multiplier);
    set_sim_dist((ST_BASE_SIM_DIST / 100) * render_distance_multiplier);
  }
  last_game_mode = mode;
}

void render_distance_plus_on_click() {
  if (render_distance_multiplier < 100) {
    render_distance_multiplier += 5;
  }

  if (mode == SPACE) {
    set_render_dist((SP_BASE_RENDER_DIST / 100) * render_distance_multiplier);
    set_sim_dist((SP_BASE_SIM_DIST / 100) * render_distance_multiplier);
  } else if (mode == STATION) {
    set_render_dist((ST_BASE_RENDER_DIST / 100) * render_distance_multiplier);
    set_sim_dist((ST_BASE_SIM_DIST / 100) * render_distance_multiplier);
  }
  last_game_mode = mode;
}

void glowing_items_on_click() {
  if (item_glow == 1) {
    item_glow = 0;
  } else {
    item_glow = 1;
  }
}

void change_resolution(UI_COMP *ui, void *args) {
  if (windowed) {
    return;
  }

  size_t move = (size_t) args;
  if (move) {
    cur_res = (cur_res + 1) % NUM_RESOLUTIONS;
  } else if (cur_res) {
    cur_res--;
  } else {
    cur_res = NUM_RESOLUTIONS - 1;
  }
  set_ui_text(ui_resolution_value_text, resolution_names[cur_res], 0.42,
              T_CENTER, fixed_sys, GLM_VEC3_ZERO);
}

void update_resolution() {
  set_resolution(resolutions[cur_res][X], resolutions[cur_res][Y], windowed);
  write_settings();
}

void read_settings() {
  FILE *settings = fopen("./settings.txt", "r");
  if (settings == NULL) {
    cur_res = 0;
    return;
  }
  fscanf(settings, "res: %d\nrd: %d\nwindowed: %d\n", &cur_res,
         &render_distance_multiplier, &windowed);
  fclose(settings);
}

void toggle_windowed() {
  windowed = !windowed;
  update_resolution();
}

void write_settings() {
  FILE *settings = fopen("./settings.txt", "w");
  if (settings == NULL) {
    return;
  }
  fprintf(settings, "res: %d\nrd: %d\nwindowed: %d\n", cur_res,
          render_distance_multiplier, windowed);
  fclose(settings);
}
