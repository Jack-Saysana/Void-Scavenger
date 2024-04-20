#include <engine/ui_component.h>
#include <global_vars.h>
#include <const.h>
#include <stdio.h>
#include <string.h>

/*
                                   RENDER
Implements the functionality for defining UI components for render menu.
*/

static char *resolution_names[] = {
  "1280x720 (16:9)",
  "1366x768 (16:9)",
  "1920x1080 (16:9)",
  "2560x1440 (16:9)",
  "3840x2160 (16:9)",

  "1280x800 (16:10)",
  "1440x900 (16:10)",
  "1680x1050 (16:10)",
  "1920x1200 (16:10)",

  "2560x1080 (21:9)",
  "3440x1440 (21:9)",
  "3840x1600 (21:9)",
  "5120x2160 (21:9)",

  "640x480 (4:3)",
  "800x600 (4:3)",
  "1024x768 (4:3)",
  "1400x1050 (4:3)",
  "1440x1080 (4:3)",
  "1600x1200 (4:3)",
  "1920x1440 (4:3)",
  "2048x1536 (4:3)",
};
static vec2 resolutions[] = {
  {1280, 720},
  {1366, 768},
  {1920, 1080},
  {2560, 1440},
  {3840, 2160},

  {1280, 800},
  {1440, 900},
  {1680, 1050},
  {1920, 1200},

  {2560, 1080},
  {3440, 1400},
  {3840, 1600},
  {5120, 2160},

  {640, 480},
  {800, 600},
  {1024, 768},
  {1400, 1050},
  {1440, 1080},
  {1600, 1200},
  {1920, 1440},
  {2048, 1536},
};
#define NUM_RESOLUTIONS (21)

#define RENDER_BUFFER_SIZE (128)
/* GLOBALS */
UI_COMP *ui_render_root;
UI_COMP *ui_render_background;
UI_COMP *ui_render_back_root;
UI_COMP *ui_render_back_button;
UI_COMP *ui_render_render_distance_root;
UI_COMP *ui_render_render_distance_title_text;
UI_COMP *ui_render_render_distance_minus_button;
UI_COMP *ui_render_render_distance_value_text;
UI_COMP *ui_render_render_distance_plus_button;
UI_COMP *ui_resolution_root;
UI_COMP *ui_resolution_title_text;
UI_COMP *ui_resolution_minus_button;
UI_COMP *ui_resolution_value_text;
UI_COMP *ui_resolution_plus_button;
UI_COMP *ui_resolution_apply_button;
UI_COMP *ui_render_glowing_items_root;
UI_COMP *ui_render_glowing_items_button;
int render_distance_multiplier;
static char render_distance_buffer[RENDER_BUFFER_SIZE];
static int cur_res = 0;

GAME_MODE last_game_mode;

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_render();
void update_render();
void render_back_on_click();
void render_distance_minus_on_click();
void render_distance_plus_on_click();
void glowing_items_on_click();
void change_resolution(UI_COMP *, void *);
void update_resolution();
void write_settings();

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */
UI_COMP *init_blue_button(UI_COMP *, vec2, float, float, int);
void set_render_dist(float dist);
void set_sim_dist(float dist);
void set_resolution(int, int);
