#include <engine/ui_component.h>
#include <global_vars.h>
#include <const.h>
#include <stdio.h>

/*
                                   ESC
Implements the functionality for defining UI components for ESC menu.
*/

/* GLOBALS */
UI_COMP *ui_esc_root;
UI_COMP *ui_esc_background;
UI_COMP *ui_esc_render_root;
UI_COMP *ui_esc_render_button;
UI_COMP *ui_esc_control_root;
UI_COMP *ui_esc_control_button;
UI_COMP *ui_esc_difficulty_root;
UI_COMP *ui_esc_difficulty_button;

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_esc();
void toggle_esc();
void render_on_click();

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */
UI_COMP *init_blue_button(UI_COMP *, vec2, float, float, int);
