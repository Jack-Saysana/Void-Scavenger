#include <engine/ui_component.h>
#include <global_vars.h>
#include <const.h>
#include <stdio.h>

/*
                                   RENDER
Implements the functionality for defining UI components for render menu.
*/

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
UI_COMP *ui_render_glowing_items_root;
UI_COMP *ui_render_glowing_items_button;
float render_distance_multiplier;

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_render();
void update_render();
void back_on_click();
void render_distance_minus_on_click();
void render_distance_plus_on_click();
void glowing_items_on_click();

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */
UI_COMP *init_blue_button(UI_COMP *, vec2, float, float, int);
