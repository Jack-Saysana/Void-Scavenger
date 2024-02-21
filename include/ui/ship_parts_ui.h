#include <engine/ui_component.h>
#include <ui/structs/ship_parts_ui_str.h>
#include <global_vars.h>
#include <const.h>

/*
                                   SHIP_PARTS
Implements the functionality for defining UI components for player's space 
mode ship parts.
*/

/* GLOBALS */
SHIP_PARTS ship_parts;

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_ship_parts();
void update_ship_parts();
void toggle_ship_parts();

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */

