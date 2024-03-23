#include <engine/ui_component.h>
#include <ui/structs/inventory_ui_str.h>
#include <global_vars.h>
#include <const.h>

/*
                                   INVENTORY
Implements the functionality for defining UI components for player's station 
mode inventory.
*/

/* GLOBALS */
INVENTORY inventory;

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_inventory();
void update_inventory();
void toggle_inventory();
void slot_on_hover(UI_COMP *ui_inventory_slot, void *unused);
void slot_off_hover(UI_COMP *ui_inventory_slot, void *unused);
void slot_on_click(UI_COMP *ui_inventory_slot, void *unused);
void update_slot(UI_COMP *ui_inventory_slot, I_SLOT *inventory_slot);

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */

