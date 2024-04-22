#include <pthread.h>
#include <engine/ui_component.h>
#include <ui/structs/inventory_ui_str.h>
#include <global_vars.h>
#include <const.h>
#include <stdio.h>
#include <string.h>
#include <inventory.h>

/*
                                   INVENTORY
Implements the functionality for defining UI components for player's station 
mode inventory.
*/

#define INVENTORY_TEXT_BUFFER_SIZE (256)
#define TEXT_LINE_HEIGHT (0.5)
#define CONTENT_LINE_HEIGHT (0.1)

/* GLOBALS */
INVENTORY inventory;
static char inventory_info_title_buffer[INVENTORY_TEXT_BUFFER_SIZE];
static char inventory_info_content_buffer[INVENTORY_TEXT_BUFFER_SIZE];

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_inventory();
void update_inventory();
void toggle_inventory();
void slot_on_hover_wrapper(UI_COMP *ui_comp, void *arg);
void slot_on_hover(UI_COMP *ui_inventory_slot, I_SLOT *inventory_slot);
void slot_off_hover_wrapper(UI_COMP *ui_comp, void *arg);
void slot_off_hover(UI_COMP *ui_inventory_slot, I_SLOT *inventory_slot);
void slot_on_click(UI_COMP *ui_inventory_slot, I_SLOT *inventory_slot);
void update_slot(UI_COMP *ui_inventory_slot, I_SLOT *inventory_slot);
void switch_slot(I_SLOT *slot_a, I_SLOT *slot_b);

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */

void ship_shield_recharge_delay(void *);
void update_timer_args(void *, void *, void *);
int add_timer(float, void *, int, void *);
void set_can_shoot(int is_can_shoot);
