#ifndef __SHIP_PARTS_UI__
#define __SHIP_PARTS_UI__

#include <engine/ui_component.h>
#include <ui/structs/ship_parts_ui_str.h>
#include <global_vars.h>
#include <const.h>
#include <stdio.h>
#include <string.h>

/*
                                   SHIP_PARTS
Implements the functionality for defining UI components for player's space 
mode ship parts.
*/

#define SHIP_PARTS_TEXT_BUFFER_SIZE (256)

/* GLOBALS */
SHIP_PARTS ship_parts;

static char ship_parts_info_title_buffer[SHIP_PARTS_TEXT_BUFFER_SIZE];
static char ship_parts_info_content_buffer[SHIP_PARTS_TEXT_BUFFER_SIZE];

void update_ship_parts_icons();

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_ship_parts();
void update_ship_parts();
void toggle_ship_parts();
void ship_parts_on_hover_wrapper(UI_COMP *ui_ship_parts, void *arg);
void ship_parts_on_hover(UI_COMP *ui_ship_parts, I_SLOT *equipped_ship_parts);
void ship_parts_off_hover_wrapper(UI_COMP *ui_ship_parts, void *arg);
void ship_parts_off_hover(UI_COMP *ui_ship_parts, I_SLOT *equipped_ship_parts);
void ship_parts_on_click(UI_COMP *ui_ship_parts, I_SLOT *equipped_ship_parts);
void update_ship_stats();

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */
void switch_slot(I_SLOT *slot_a, I_SLOT *slot_b);
I_SLOT *inv_first_avail();
void ship_shield_recharge_delay(void *);
void update_timer_args(void *, void *, void *);
int add_timer(float, void *, int, void *);

#endif
