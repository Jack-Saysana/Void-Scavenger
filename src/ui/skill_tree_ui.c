#include <ui/skill_tree_ui.h>
#include <stdio.h>

/*
                                   SKILL_TREE
Implements the functionality for defining UI components for station mode 
skill tree.
*/

/*
  Init skill tree UI globaly, call by general_ui.c init_ui_components()

  Return
    0 if successful
    otherwise unsuccessful
*/
int init_skill_tree() {
  skill_tree.ui_skill_tree_root = add_ui_comp(
    UI_ROOT_COMP, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_root, "assets/transparent.png");
  
  skill_tree.ui_skill_tree_background = add_ui_comp(
    skill_tree.ui_skill_tree_root, // UI_COMP *parent
    (vec2) { 0.0, 0.0 }, // vec2 pos
    1.0, // float width
    1.0, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_background, "assets/ui/hud_color_50.png");

  // set init visibility
  set_ui_enabled(skill_tree.ui_skill_tree_root, 0);
  
  return 0;
}

/*
  Update skill tree UI per frame, call by general_ui.c update_ui_components()
*/
void update_skill_tree() {
  // check current game mode
  if (mode == SPACE) {
    // set visibility
    set_ui_enabled(skill_tree.ui_skill_tree_root, 0);
    
  } else if (mode == STATION) {
    // update inventory slots
    // TODO: Should be functional in sprint 2
    
  }
}

void toggle_skill_tree() {
  if (skill_tree.ui_skill_tree_root->enabled) {
    set_ui_enabled(skill_tree.ui_skill_tree_root, 0);
  } else {
    set_ui_enabled(skill_tree.ui_skill_tree_root, 1);
  }
}
