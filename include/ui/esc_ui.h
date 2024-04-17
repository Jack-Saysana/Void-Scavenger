#include <engine/ui_component.h>
#include <global_vars.h>
#include <const.h>
#include <stdio.h>
#include <string.h>

/*
                                   ESC
Implements the functionality for defining UI components for ESC menu.
*/

#define ESC_BUFFER_SIZE (128)
/* GLOBALS */
UI_COMP *ui_esc_root;
UI_COMP *ui_esc_background;
UI_COMP *ui_esc_render_root;
UI_COMP *ui_esc_render_button;
UI_COMP *ui_esc_control_root;
UI_COMP *ui_esc_control_button;
UI_COMP *ui_esc_difficulty_root;
UI_COMP *ui_difficulty_title_text;
UI_COMP *ui_difficulty_minus_button;
UI_COMP *ui_difficulty_text;
UI_COMP *ui_difficulty_plus_button;
static char difficulty_buffer[ESC_BUFFER_SIZE];

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_esc();
void toggle_esc();
void render_on_click();
void control_on_click();
void difficulty_minus_on_click();
void difficulty_plus_on_click();

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */
UI_COMP *init_blue_button(UI_COMP *, vec2, float, float, int);
