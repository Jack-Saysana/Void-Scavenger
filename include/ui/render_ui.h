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
UI_COMP *ui_render_render_distance_button;
UI_COMP *ui_render_glowing_items_root;
UI_COMP *ui_render_glowing_items_button;

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_render();

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */
UI_COMP *init_blue_button(UI_COMP *, vec2, float, float, int);
