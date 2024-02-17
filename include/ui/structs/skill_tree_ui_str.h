#ifndef __SKILL_TREE_STR_H__
#define __SKILL_TREE_STR_H__

#include <engine/ui_component.h>

/* DEFINES */

typedef struct skill_tree {
  UI_COMP *ui_skill_tree_root;

  UI_COMP *ui_skill_tree_background;

  UI_COMP *ui_skill_tree_info_background;
  UI_COMP *ui_skill_tree_info_text;

  UI_COMP *ui_skill_tree_title_background;
  UI_COMP *ui_skill_tree_title_text;

  UI_COMP *ui_skill_tree_lv_1_background;
  UI_COMP *ui_skill_tree_lv_1_text;
  UI_COMP *ui_skill_tree_lv_1_attribute_1_background;
  UI_COMP *ui_skill_tree_lv_1_attribute_1_icon;
  UI_COMP *ui_skill_tree_lv_1_attribute_2_background;
  UI_COMP *ui_skill_tree_lv_1_attribute_2_icon;

  UI_COMP *ui_skill_tree_lv_2_background;
  UI_COMP *ui_skill_tree_lv_2_text;
  UI_COMP *ui_skill_tree_lv_2_attribute_1_background;
  UI_COMP *ui_skill_tree_lv_2_attribute_1_icon;
  UI_COMP *ui_skill_tree_lv_2_attribute_2_background;
  UI_COMP *ui_skill_tree_lv_2_attribute_2_icon;
  UI_COMP *ui_skill_tree_lv_2_attribute_3_background;
  UI_COMP *ui_skill_tree_lv_2_attribute_3_icon;
  UI_COMP *ui_skill_tree_lv_2_attribute_4_background;
  UI_COMP *ui_skill_tree_lv_2_attribute_4_icon;
  UI_COMP *ui_skill_tree_lv_2_attribute_5_background;
  UI_COMP *ui_skill_tree_lv_2_attribute_5_icon;

  UI_COMP *ui_skill_tree_lv_3_background;
  UI_COMP *ui_skill_tree_lv_3_text;
  UI_COMP *ui_skill_tree_lv_3_attribute_1_background;
  UI_COMP *ui_skill_tree_lv_3_attribute_1_icon;
  UI_COMP *ui_skill_tree_lv_3_attribute_2_background;
  UI_COMP *ui_skill_tree_lv_3_attribute_2_icon;
  UI_COMP *ui_skill_tree_lv_3_attribute_3_background;
  UI_COMP *ui_skill_tree_lv_3_attribute_3_icon;

  UI_COMP *ui_skill_tree_lv_4_background;
  UI_COMP *ui_skill_tree_lv_4_text;
  UI_COMP *ui_skill_tree_lv_4_attribute_1_background;
  UI_COMP *ui_skill_tree_lv_4_attribute_1_icon;
  
} SKILL_TREE;

#endif
