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

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */

