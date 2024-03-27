#ifndef __SKILL_TREE_STR_H__
#define __SKILL_TREE_STR_H__

#include <engine/ui_component.h>

/* DEFINES */

#define SKILL_TREE_TEXT_BUFFER_SIZE (128)

typedef enum skill_type {
  T_EMPTY_SKILL,
  T_SURVIVAL,
  T_COMBAT,
  T_EXPLORATION
} T_SKILL;

typedef struct skill {
  T_SKILL skill_type;
  struct skill *parent_skill;
  int unlocked;
  int skill_level;
  char skill_name[SKILL_TREE_TEXT_BUFFER_SIZE];
  char skill_content[SKILL_TREE_TEXT_BUFFER_SIZE];
} SKILL;

typedef struct skill_tree {
  UI_COMP *ui_skill_tree_root;

  UI_COMP *ui_skill_tree_background;

  UI_COMP *ui_skill_tree_info_background;
  UI_COMP *ui_skill_tree_info_title_background;
  UI_COMP *ui_skill_tree_info_title_text;
  UI_COMP *ui_skill_tree_info_content_background;
  UI_COMP *ui_skill_tree_info_content_text;

  UI_COMP *ui_skill_tree_sp_background;
  UI_COMP *ui_skill_tree_sp_text;
  UI_COMP *ui_skill_tree_page_background;
  UI_COMP *ui_skill_tree_survival_background;
  UI_COMP *ui_skill_tree_survival_text;
  UI_COMP *ui_skill_tree_combat_background;
  UI_COMP *ui_skill_tree_combat_text;
  UI_COMP *ui_skill_tree_exploration_background;
  UI_COMP *ui_skill_tree_exploration_text;

  UI_COMP *ui_skill_tree_lv_1_background;
  UI_COMP *ui_skill_tree_lv_1_enable_background;
  UI_COMP *ui_skill_tree_lv_1_enable_icon;
  SKILL skill_survival_lv1;
  SKILL skill_combat_lv1;
  SKILL skill_exploration_lv1;

  UI_COMP *ui_skill_tree_lv_1_skill_1_background;
  UI_COMP *ui_skill_tree_lv_1_skill_1_icon;
  SKILL skill_survival_lv1_skill_1;
  SKILL skill_combat_lv1_skill_1;
  SKILL skill_exploration_lv1_skill_1;

  UI_COMP *ui_skill_tree_lv_1_skill_2_background;
  UI_COMP *ui_skill_tree_lv_1_skill_2_icon;
  SKILL skill_survival_lv1_skill_2;
  SKILL skill_combat_lv1_skill_2;
  SKILL skill_exploration_lv1_skill_2;

  UI_COMP *ui_skill_tree_lv_2_background;
  UI_COMP *ui_skill_tree_lv_2_enable_background;
  UI_COMP *ui_skill_tree_lv_2_enable_icon;
  SKILL skill_survival_lv2;
  SKILL skill_combat_lv2;
  SKILL skill_exploration_lv2;

  UI_COMP *ui_skill_tree_lv_2_skill_1_background;
  UI_COMP *ui_skill_tree_lv_2_skill_1_icon;
  SKILL skill_survival_lv2_skill_1;
  SKILL skill_combat_lv2_skill_1;
  SKILL skill_exploration_lv2_skill_1;

  // UI_COMP *ui_skill_tree_lv_2_skill_2_background;
  // UI_COMP *ui_skill_tree_lv_2_skill_2_icon;
  // UI_COMP *ui_skill_tree_lv_2_skill_3_background;
  // UI_COMP *ui_skill_tree_lv_2_skill_3_icon;
  // UI_COMP *ui_skill_tree_lv_2_skill_4_background;
  // UI_COMP *ui_skill_tree_lv_2_skill_4_icon;
  // UI_COMP *ui_skill_tree_lv_2_skill_5_background;
  // UI_COMP *ui_skill_tree_lv_2_skill_5_icon;

  UI_COMP *ui_skill_tree_lv_3_background;
  UI_COMP *ui_skill_tree_lv_3_enable_background;
  UI_COMP *ui_skill_tree_lv_3_enable_icon;
  SKILL skill_survival_lv3;
  SKILL skill_combat_lv3;
  SKILL skill_exploration_lv3;

  // UI_COMP *ui_skill_tree_lv_3_skill_1_background;
  // UI_COMP *ui_skill_tree_lv_3_skill_1_icon;
  // UI_COMP *ui_skill_tree_lv_3_skill_2_background;
  // UI_COMP *ui_skill_tree_lv_3_skill_2_icon;
  // UI_COMP *ui_skill_tree_lv_3_skill_3_background;
  // UI_COMP *ui_skill_tree_lv_3_skill_3_icon;

  UI_COMP *ui_skill_tree_lv_4_background;
  UI_COMP *ui_skill_tree_lv_4_enable_background;
  UI_COMP *ui_skill_tree_lv_4_enable_icon;
  SKILL skill_survival_lv4;
  SKILL skill_combat_lv4;
  SKILL skill_exploration_lv4;

  // UI_COMP *ui_skill_tree_lv_4_skill_1_background;
  // UI_COMP *ui_skill_tree_lv_4_skill_1_icon;

  T_SKILL current_page;

  int skill_points;
} SKILL_TREE;

#endif
