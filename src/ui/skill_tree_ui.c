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
    0.6, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_background, "assets/ui/test.png");

  skill_tree.ui_skill_tree_title_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.01, -0.02 }, // vec2 pos
    0.98, // float width
    0.176, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_title_background, "assets/ui/hud_color_bg.png");

  skill_tree.ui_skill_tree_title_text = add_ui_comp(
    skill_tree.ui_skill_tree_title_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_title_text, "assets/transparent.png");
  set_ui_text(skill_tree.ui_skill_tree_title_text, "branch name", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  skill_tree.ui_skill_tree_lv_1_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.01, -0.216 }, // vec2 pos
    0.98, // float width
    0.176, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_1_background, "assets/ui/hud_color_bg.png");

  skill_tree.ui_skill_tree_lv_1_text = add_ui_comp(
    skill_tree.ui_skill_tree_lv_1_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.2, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_1_text, "assets/transparent.png");
  set_ui_text(skill_tree.ui_skill_tree_lv_1_text, "Lv1", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  skill_tree.ui_skill_tree_lv_1_attribute_1_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_1_background, // UI_COMP *parent
    (vec2) { 0.4, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_1_attribute_1_icon, "assets/ui/parts_weapon_icon.png");

  skill_tree.ui_skill_tree_lv_1_attribute_2_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_1_background, // UI_COMP *parent
    (vec2) { 0.5, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_1_attribute_2_icon, "assets/ui/parts_weapon_icon.png");

  skill_tree.ui_skill_tree_lv_2_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.01, -0.412 }, // vec2 pos
    0.98, // float width
    0.176, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_2_background, "assets/ui/hud_color_bg.png");

  skill_tree.ui_skill_tree_lv_2_text = add_ui_comp(
    skill_tree.ui_skill_tree_lv_2_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.2, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_2_text, "assets/transparent.png");
  set_ui_text(skill_tree.ui_skill_tree_lv_2_text, "Lv2", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  skill_tree.ui_skill_tree_lv_2_attribute_1_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_2_background, // UI_COMP *parent
    (vec2) { 0.4, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_2_attribute_1_icon, "assets/ui/parts_weapon_icon.png");

  skill_tree.ui_skill_tree_lv_2_attribute_2_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_2_background, // UI_COMP *parent
    (vec2) { 0.5, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_2_attribute_2_icon, "assets/ui/parts_weapon_icon.png");

  skill_tree.ui_skill_tree_lv_2_attribute_3_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_2_background, // UI_COMP *parent
    (vec2) { 0.6, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_2_attribute_3_icon, "assets/ui/parts_weapon_icon.png");

  skill_tree.ui_skill_tree_lv_2_attribute_4_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_2_background, // UI_COMP *parent
    (vec2) { 0.7, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_2_attribute_4_icon, "assets/ui/parts_weapon_icon.png");

  skill_tree.ui_skill_tree_lv_2_attribute_5_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_2_background, // UI_COMP *parent
    (vec2) { 0.8, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_2_attribute_5_icon, "assets/ui/parts_weapon_icon.png");

  skill_tree.ui_skill_tree_lv_3_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.01, -0.608 }, // vec2 pos
    0.98, // float width
    0.176, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_3_background, "assets/ui/hud_color_bg.png");

  skill_tree.ui_skill_tree_lv_3_text = add_ui_comp(
    skill_tree.ui_skill_tree_lv_3_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.2, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_3_text, "assets/transparent.png");
  set_ui_text(skill_tree.ui_skill_tree_lv_3_text, "Lv3", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  skill_tree.ui_skill_tree_lv_3_attribute_1_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_3_background, // UI_COMP *parent
    (vec2) { 0.4, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_3_attribute_1_icon, "assets/ui/parts_weapon_icon.png");

  skill_tree.ui_skill_tree_lv_3_attribute_2_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_3_background, // UI_COMP *parent
    (vec2) { 0.5, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_3_attribute_2_icon, "assets/ui/parts_weapon_icon.png");

  skill_tree.ui_skill_tree_lv_3_attribute_3_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_3_background, // UI_COMP *parent
    (vec2) { 0.6, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_3_attribute_3_icon, "assets/ui/parts_weapon_icon.png");

  skill_tree.ui_skill_tree_lv_4_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.01, -0.804 }, // vec2 pos
    0.98, // float width
    0.176, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_4_background, "assets/ui/hud_color_bg.png");

  skill_tree.ui_skill_tree_lv_4_text = add_ui_comp(
    skill_tree.ui_skill_tree_lv_4_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.2, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_4_text, "assets/transparent.png");
  set_ui_text(skill_tree.ui_skill_tree_lv_4_text, "Lv4", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  skill_tree.ui_skill_tree_lv_4_attribute_1_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_4_background, // UI_COMP *parent
    (vec2) { 0.4, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_4_attribute_1_icon, "assets/ui/parts_weapon_icon.png");
  
  skill_tree.ui_skill_tree_info_background = add_ui_comp(
    skill_tree.ui_skill_tree_root, // UI_COMP *parent
    (vec2) { 0.5, -0.64 }, // vec2 pos
    0.4, // float width
    0.3, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_info_background, "assets/ui/test.png");

  skill_tree.ui_skill_tree_info_title_background = add_ui_comp(
    skill_tree.ui_skill_tree_info_background, // UI_COMP *parent
    (vec2) { 0.02, -0.05 }, // vec2 pos
    0.96, // float width
    0.2833, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_info_title_background, "assets/ui/hud_color.png");

  skill_tree.ui_skill_tree_info_title_text = add_ui_comp(
    skill_tree.ui_skill_tree_info_title_background, // UI_COMP *parent
    (vec2) { 0.1, -0.1 }, // vec2 pos
    0.8, // float width
    0.8, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_info_title_text, "assets/transparent.png");
  set_ui_text(skill_tree.ui_skill_tree_info_title_text, "skill name", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  skill_tree.ui_skill_tree_info_content_background = add_ui_comp(
    skill_tree.ui_skill_tree_info_background, // UI_COMP *parent
    (vec2) { 0.02, -0.3833 }, // vec2 pos
    0.96, // float width
    0.5666, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_info_content_background, "assets/ui/hud_color_bg.png");

  skill_tree.ui_skill_tree_info_content_text = add_ui_comp(
    skill_tree.ui_skill_tree_info_content_background, // UI_COMP *parent
    (vec2) { 0.1, -0.05 }, // vec2 pos
    0.8, // float width
    0.4, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_info_content_text, "assets/transparent.png");
  set_ui_text(skill_tree.ui_skill_tree_info_content_text, "skill content", 1.0, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  
  // set layer to front
  // set_manual_layer(skill_tree.ui_skill_tree_root, 0.01);

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
    CURSOR_ENABLED = 0;
  } else {
    set_ui_enabled(skill_tree.ui_skill_tree_root, 1);
    set_ui_enabled(inventory.ui_inventory_root, 0);
    CURSOR_ENABLED = 1;
  }
}
