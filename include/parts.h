#include <engine/ui_component.h>
#include <ui/structs/inventory_ui_str.h>
#include <global_vars.h>
#include <const.h>

/*
                                   PARTS
Implements the list and functionality for equippable parts.
*/

#define MAX_LIST (300)

/* GLOBALS */
I_SLOT parts_list[MAX_LIST];  // Stores the parts that pre-generated globally
                              // Each parts type has generated 50 randomized parts
                              // Result of [i % 6] returns the parts with same types
                              // 0 = I_SLOT_REACTOR     1 = I_SLOT_HULL
                              // 2 = I_SLOT_SHIELD      3 = I_SLOT_WEAPON
                              // 4 = I_SLOT_WING        5 = I_SLOT_THRUSTER

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_parts_list();
int generate_parts(I_SLOT_ID parts_type, I_SLOT slot);

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */

