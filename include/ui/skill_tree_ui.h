#include <engine/ui_component.h>
#include <ui/structs/skill_tree_ui_str.h>
#include <global_vars.h>
#include <const.h>
#include <stdio.h>
#include <string.h>

/*
                                   SKILL_TREE
Implements the functionality for defining UI components for station mode 
skill tree.
*/

/* GLOBALS */
SKILL_TREE skill_tree;

static char skill_tree_sp_buffer[SKILL_TREE_TEXT_BUFFER_SIZE];
static char skill_tree_info_title_buffer[SKILL_TREE_TEXT_BUFFER_SIZE];
static char skill_tree_info_content_buffer[SKILL_TREE_TEXT_BUFFER_SIZE];

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_skill_tree();
void init_skills();
void update_skill_tree();
void toggle_skill_tree();
void skill_on_hover_wrapper(UI_COMP *ui_comp, void *arg);
void skill_on_hover(UI_COMP *ui_comp, SKILL *skill_slot);
void skill_off_hover_wrapper(UI_COMP *ui_comp, void *arg);
void skill_off_hover(UI_COMP *ui_comp, SKILL *skill_slot);
void skill_on_click(UI_COMP *ui_comp, SKILL *skill_slot);
void switch_survival_tab(UI_COMP *ui_tab_comp, void *unused);
void switch_combat_tab(UI_COMP *ui_tab_comp, void *unused);
void switch_exploration_tab(UI_COMP *ui_tab_comp, void *unused);
void update_skill_tabs();

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */

