#include <engine/ui_component.h>
#include <ui/structs/skill_tree_ui_str.h>
#include <global_vars.h>
#include <const.h>

/*
                                   SKILL_TREE
Implements the functionality for defining UI components for station mode 
skill tree.
*/

/* GLOBALS */
SKILL_TREE skill_tree;

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_skill_tree();
void update_skill_tree();
void toggle_skill_tree();

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */

