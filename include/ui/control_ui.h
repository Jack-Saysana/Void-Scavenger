#include <engine/ui_component.h>
#include <global_vars.h>
#include <const.h>
#include <stdio.h>
#include <string.h>

/*
                                   CONTROL
Implements the functionality for defining UI components for control menu.
*/

#define CONTROL_BUFFER_SIZE (1024)
/* GLOBALS */
UI_COMP *ui_control_root;
UI_COMP *ui_control_background;
UI_COMP *ui_control_back_root;
UI_COMP *ui_control_back_button;
UI_COMP *ui_control_cheat_root;
UI_COMP *ui_control_cheat_button;
UI_COMP *ui_control_instruction_root;
UI_COMP *ui_control_instruction_title_text;
UI_COMP *ui_control_instruction_image;
UI_COMP *ui_control_instruction_key_text;
UI_COMP *ui_control_instruction_mouse_text;

static char control_instruction_title_buffer[CONTROL_BUFFER_SIZE];
static char control_instruction_key_buffer[CONTROL_BUFFER_SIZE];
static char control_instruction_mouse_buffer[CONTROL_BUFFER_SIZE];

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_control();
void control_back_on_click();
void control_cheat_on_click();

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */
UI_COMP *init_blue_button(UI_COMP *, vec2, float, float, int);
int get_cheats_state();
void update_cheats(int);
