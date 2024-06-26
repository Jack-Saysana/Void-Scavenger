#include <ui/skill_tree_ui.h>

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
  init_skills();
  skill_tree.current_page = T_SURVIVAL;

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
    0.64, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_background, "assets/ui/test.png");

  /*
  ================
    Skill Points
  ================
  */
  skill_tree.ui_skill_tree_sp_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.01, -0.02 }, // vec2 pos
    0.17, // float width
    0.16, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_sp_background, "assets/ui/hud_color.png");

  skill_tree.ui_skill_tree_sp_text = add_ui_comp(
    skill_tree.ui_skill_tree_sp_background, // UI_COMP *parent
    (vec2) { 0.2, -0.05 }, // vec2 pos
    0.6, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_sp_text, "assets/transparent.png");
  memset(skill_tree_sp_buffer, '\0', SKILL_TREE_TEXT_BUFFER_SIZE);
  snprintf(skill_tree_sp_buffer, SKILL_TREE_TEXT_BUFFER_SIZE, "SP %d", st_player.skill_points);
  set_ui_text(skill_tree.ui_skill_tree_sp_text, skill_tree_sp_buffer, 
              0.5, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  /*
  ===================
    Page Background
  ===================
  */
  skill_tree.ui_skill_tree_page_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.01, -0.18 }, // vec2 pos
    0.98, // float width
    0.80, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_page_background, "assets/ui/hud_color.png");

  /*
  ================
    Survival Tab
  ================
  */
  skill_tree.ui_skill_tree_survival_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.19, -0.02 }, // vec2 pos
    0.26, // float width
    0.16, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_survival_background, "assets/ui/hud_color.png");
  set_ui_on_click(skill_tree.ui_skill_tree_survival_background, switch_survival_tab, NULL);

  skill_tree.ui_skill_tree_survival_text = add_ui_comp(
    skill_tree.ui_skill_tree_survival_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_survival_text, "assets/transparent.png");
  set_ui_text(skill_tree.ui_skill_tree_survival_text, "SURVIVAL", 0.5, T_CENTER, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  /*
  ==============
    Combat Tab
  ==============
  */
  skill_tree.ui_skill_tree_combat_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.46, -0.02 }, // vec2 pos
    0.26, // float width
    0.16, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_combat_background, "assets/ui/hud_color_bg.png");
  set_ui_on_click(skill_tree.ui_skill_tree_combat_background, switch_combat_tab, NULL);

  skill_tree.ui_skill_tree_combat_text = add_ui_comp(
    skill_tree.ui_skill_tree_combat_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_combat_text, "assets/transparent.png");
  set_ui_text(skill_tree.ui_skill_tree_combat_text, "COMBAT", 0.5, T_CENTER, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  /*
  ===================
    Exploration Tab
  ===================
  */
  skill_tree.ui_skill_tree_exploration_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.73, -0.02 }, // vec2 pos
    0.26, // float width
    0.16, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_exploration_background, "assets/ui/hud_color_bg.png");
  set_ui_on_click(skill_tree.ui_skill_tree_exploration_background, switch_exploration_tab, NULL);

  skill_tree.ui_skill_tree_exploration_text = add_ui_comp(
    skill_tree.ui_skill_tree_exploration_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_exploration_text, "assets/transparent.png");
  set_ui_text(skill_tree.ui_skill_tree_exploration_text, "EXPLORATION", 0.5, T_CENTER, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

  /*
  =====================
    Lv1 Enable Button
  =====================
  */
  skill_tree.ui_skill_tree_lv_1_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.01, -0.21 }, // vec2 pos
    0.98, // float width
    0.17, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_1_background, "assets/transparent.png");

  skill_tree.ui_skill_tree_lv_1_enable_background = add_ui_comp(
    skill_tree.ui_skill_tree_lv_1_background, // UI_COMP *parent
    (vec2) { 0.06, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_1_enable_background, "assets/ui/hud_color.png");
  set_ui_on_hover(skill_tree.ui_skill_tree_lv_1_enable_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv1);
  set_ui_no_hover(skill_tree.ui_skill_tree_lv_1_enable_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv1);
  set_ui_on_click(skill_tree.ui_skill_tree_lv_1_enable_background, (void *) skill_on_click, &skill_tree.skill_survival_lv1);

  skill_tree.ui_skill_tree_lv_1_enable_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_1_enable_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_1_enable_icon, "assets/ui/skill/lv1_disable_survival.png");

  /*
  ==============
    Lv1 Skills
  ==============
  */
  skill_tree.ui_skill_tree_lv_1_skill_1_background = add_ui_comp(
    skill_tree.ui_skill_tree_lv_1_background, // UI_COMP *parent
    (vec2) { 0.24, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_1_background, "assets/ui/hud_color.png");
  set_ui_on_hover(skill_tree.ui_skill_tree_lv_1_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv1_skill_1);
  set_ui_no_hover(skill_tree.ui_skill_tree_lv_1_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv1_skill_1);
  set_ui_on_click(skill_tree.ui_skill_tree_lv_1_skill_1_background, (void *) skill_on_click, &skill_tree.skill_survival_lv1_skill_1);

  skill_tree.ui_skill_tree_lv_1_skill_1_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_1_skill_1_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  // set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_1_icon, "assets/ui/skill/survival_hp_disable.png");

  skill_tree.ui_skill_tree_lv_1_skill_2_background = add_ui_comp(
    skill_tree.ui_skill_tree_lv_1_background, // UI_COMP *parent
    (vec2) { 0.32, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_2_background, "assets/ui/hud_color.png");
  set_ui_on_hover(skill_tree.ui_skill_tree_lv_1_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv1_skill_2);
  set_ui_no_hover(skill_tree.ui_skill_tree_lv_1_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv1_skill_2);
  set_ui_on_click(skill_tree.ui_skill_tree_lv_1_skill_2_background, (void *) skill_on_click, &skill_tree.skill_survival_lv1_skill_2);

  skill_tree.ui_skill_tree_lv_1_skill_2_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_1_skill_2_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  // set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_2_icon, "assets/ui/skill/survival_shield_disable.png");

  /*
  =====================
    Lv2 Enable Button
  =====================
  */
  skill_tree.ui_skill_tree_lv_2_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.01, -0.40 }, // vec2 pos
    0.98, // float width
    0.17, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_2_background, "assets/transparent.png");

  skill_tree.ui_skill_tree_lv_2_enable_background = add_ui_comp(
    skill_tree.ui_skill_tree_lv_2_background, // UI_COMP *parent
    (vec2) { 0.06, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_2_enable_background, "assets/ui/hud_color.png");
  set_ui_on_hover(skill_tree.ui_skill_tree_lv_2_enable_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv2);
  set_ui_no_hover(skill_tree.ui_skill_tree_lv_2_enable_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv2);
  set_ui_on_click(skill_tree.ui_skill_tree_lv_2_enable_background, (void *) skill_on_click, &skill_tree.skill_survival_lv2);

  skill_tree.ui_skill_tree_lv_2_enable_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_2_enable_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_2_enable_icon, "assets/ui/skill/lv2_disable_survival.png");

  /*
  ==============
    Lv2 Skills
  ==============
  */
  skill_tree.ui_skill_tree_lv_2_skill_1_background = add_ui_comp(
    skill_tree.ui_skill_tree_lv_2_background, // UI_COMP *parent
    (vec2) { 0.24, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_1_background, "assets/ui/hud_color.png");
  set_ui_on_hover(skill_tree.ui_skill_tree_lv_2_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv2_skill_1);
  set_ui_no_hover(skill_tree.ui_skill_tree_lv_2_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv2_skill_1);
  set_ui_on_click(skill_tree.ui_skill_tree_lv_2_skill_1_background, (void *) skill_on_click, &skill_tree.skill_survival_lv2_skill_1);

  skill_tree.ui_skill_tree_lv_2_skill_1_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_2_skill_1_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  // set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_1_icon, "assets/ui/skill/survival_hp_shield_disable.png");

  skill_tree.ui_skill_tree_lv_2_skill_2_background = add_ui_comp(
    skill_tree.ui_skill_tree_lv_2_background, // UI_COMP *parent
    (vec2) { 0.32, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_2_background, "assets/ui/hud_color.png");
  set_ui_on_hover(skill_tree.ui_skill_tree_lv_2_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv2_skill_2);
  set_ui_no_hover(skill_tree.ui_skill_tree_lv_2_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv2_skill_2);
  set_ui_on_click(skill_tree.ui_skill_tree_lv_2_skill_2_background, (void *) skill_on_click, &skill_tree.skill_survival_lv2_skill_2);

  skill_tree.ui_skill_tree_lv_2_skill_2_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_2_skill_2_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  // set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_2_icon, "assets/ui/skill/survival_hp_shield_disable.png");
  /*
  =====================
    Lv3 Enable Button
  =====================
  */
  skill_tree.ui_skill_tree_lv_3_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.01, -0.59 }, // vec2 pos
    0.98, // float width
    0.17, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_3_background, "assets/transparent.png");

  skill_tree.ui_skill_tree_lv_3_enable_background = add_ui_comp(
    skill_tree.ui_skill_tree_lv_3_background, // UI_COMP *parent
    (vec2) { 0.06, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_3_enable_background, "assets/ui/hud_color.png");
  set_ui_on_hover(skill_tree.ui_skill_tree_lv_3_enable_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv3);
  set_ui_no_hover(skill_tree.ui_skill_tree_lv_3_enable_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv3);
  set_ui_on_click(skill_tree.ui_skill_tree_lv_3_enable_background, (void *) skill_on_click, &skill_tree.skill_survival_lv3);


  skill_tree.ui_skill_tree_lv_3_enable_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_3_enable_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_3_enable_icon, "assets/ui/skill/lv3_disable_survival.png");

  /*
  =============
    Lv3 Skills
  =============
  */

  skill_tree.ui_skill_tree_lv_3_skill_1_background = add_ui_comp(
    skill_tree.ui_skill_tree_lv_3_background, // UI_COMP *parent
    (vec2) { 0.24, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_1_background, "assets/ui/hud_color.png");
  set_ui_on_hover(skill_tree.ui_skill_tree_lv_3_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv3_skill_1);
  set_ui_no_hover(skill_tree.ui_skill_tree_lv_3_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv3_skill_1);
  set_ui_on_click(skill_tree.ui_skill_tree_lv_3_skill_1_background, (void *) skill_on_click, &skill_tree.skill_survival_lv3_skill_1);

  skill_tree.ui_skill_tree_lv_3_skill_1_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_3_skill_1_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  // set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_1_icon, "assets/ui/skill/survival_hp_shield_disable.png");

  skill_tree.ui_skill_tree_lv_3_skill_2_background = add_ui_comp(
    skill_tree.ui_skill_tree_lv_3_background, // UI_COMP *parent
    (vec2) { 0.32, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_2_background, "assets/ui/hud_color.png");
  set_ui_on_hover(skill_tree.ui_skill_tree_lv_3_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv3_skill_2);
  set_ui_no_hover(skill_tree.ui_skill_tree_lv_3_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv3_skill_2);
  set_ui_on_click(skill_tree.ui_skill_tree_lv_3_skill_2_background, (void *) skill_on_click, &skill_tree.skill_survival_lv3_skill_2);

  skill_tree.ui_skill_tree_lv_3_skill_2_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_3_skill_2_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  // set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_2_icon, "assets/ui/skill/survival_hp_shield_disable.png");


  /*
  =====================
    Lv4 Enable Button
  =====================
  */
  skill_tree.ui_skill_tree_lv_4_background = add_ui_comp(
    skill_tree.ui_skill_tree_background, // UI_COMP *parent
    (vec2) { 0.01, -0.78 }, // vec2 pos
    0.98, // float width
    0.17, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_4_background, "assets/transparent.png");

  skill_tree.ui_skill_tree_lv_4_enable_background = add_ui_comp(
    skill_tree.ui_skill_tree_lv_4_background, // UI_COMP *parent
    (vec2) { 0.06, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_4_enable_background, "assets/ui/hud_color.png");
  set_ui_on_hover(skill_tree.ui_skill_tree_lv_4_enable_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv4);
  set_ui_no_hover(skill_tree.ui_skill_tree_lv_4_enable_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv4);
  set_ui_on_click(skill_tree.ui_skill_tree_lv_4_enable_background, (void *) skill_on_click, &skill_tree.skill_survival_lv4);

  skill_tree.ui_skill_tree_lv_4_enable_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_4_enable_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_4_enable_icon, "assets/ui/skill/lv4_disable_survival.png");

  /*
  =============
    Lv4 Skills
  =============
  */

  skill_tree.ui_skill_tree_lv_4_skill_1_background = add_ui_comp(
    skill_tree.ui_skill_tree_lv_4_background, // UI_COMP *parent
    (vec2) { 0.24, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_1_background, "assets/ui/hud_color.png");
  set_ui_on_hover(skill_tree.ui_skill_tree_lv_4_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv4_skill_1);
  set_ui_no_hover(skill_tree.ui_skill_tree_lv_4_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv4_skill_1);
  set_ui_on_click(skill_tree.ui_skill_tree_lv_4_skill_1_background, (void *) skill_on_click, &skill_tree.skill_survival_lv4_skill_1);

  skill_tree.ui_skill_tree_lv_4_skill_1_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_4_skill_1_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  // set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_1_icon, "assets/ui/skill/survival_hp_shield_disable.png");

  skill_tree.ui_skill_tree_lv_4_skill_2_background = add_ui_comp(
    skill_tree.ui_skill_tree_lv_4_background, // UI_COMP *parent
    (vec2) { 0.32, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_2_background, "assets/ui/hud_color.png");
  set_ui_on_hover(skill_tree.ui_skill_tree_lv_4_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv4_skill_2);
  set_ui_no_hover(skill_tree.ui_skill_tree_lv_4_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv4_skill_2);
  set_ui_on_click(skill_tree.ui_skill_tree_lv_4_skill_2_background, (void *) skill_on_click, &skill_tree.skill_survival_lv4_skill_2);

  skill_tree.ui_skill_tree_lv_4_skill_2_icon = add_ui_comp(
    skill_tree.ui_skill_tree_lv_4_skill_2_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_Y | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_Y
  );
  // set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_2_icon, "assets/ui/skill/survival_hp_shield_disable.png");

  /*
  ========
    Info
  ========
  */
  skill_tree.ui_skill_tree_info_background = add_ui_comp(
    skill_tree.ui_skill_tree_root, // UI_COMP *parent
    (vec2) { 0.7, -0.7 }, // vec2 pos
    0.24, // float width
    0.24, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_info_background, "assets/ui/test.png");

  skill_tree.ui_skill_tree_info_title_background = add_ui_comp(
    skill_tree.ui_skill_tree_info_background, // UI_COMP *parent
    (vec2) { 0.025, -0.05 }, // vec2 pos
    0.95, // float width
    0.2, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_info_title_background, "assets/ui/hud_color.png");

  skill_tree.ui_skill_tree_info_title_text = add_ui_comp(
    skill_tree.ui_skill_tree_info_title_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_X
  );
  set_ui_texture(skill_tree.ui_skill_tree_info_title_text, "assets/transparent.png");
  memset(skill_tree_info_title_buffer, '\0', SKILL_TREE_TEXT_BUFFER_SIZE);
  snprintf(skill_tree_info_title_buffer, SKILL_TREE_TEXT_BUFFER_SIZE, "SKILL NAME");
  set_ui_text(skill_tree.ui_skill_tree_info_title_text,
              skill_tree_info_title_buffer, 0.08, T_LEFT, fixed_sys, 
              (vec3) { 0.0, 0.0, 0.0 });

  skill_tree.ui_skill_tree_info_content_background = add_ui_comp(
    skill_tree.ui_skill_tree_info_background, // UI_COMP *parent
    (vec2) { 0.025, -0.3 }, // vec2 pos
    0.95, // float width
    0.65, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y
  );
  set_ui_texture(skill_tree.ui_skill_tree_info_content_background, "assets/ui/hud_color_bg.png");

  skill_tree.ui_skill_tree_info_content_text = add_ui_comp(
    skill_tree.ui_skill_tree_info_content_background, // UI_COMP *parent
    (vec2) { 0.05, -0.05 }, // vec2 pos
    0.9, // float width
    0.9, // float height
    ABSOLUTE_POS | POS_UNIT_RATIO | WIDTH_UNIT_RATIO_X | HEIGHT_UNIT_RATIO_Y | LINE_UNIT_RATIO_X
  );
  set_ui_texture(skill_tree.ui_skill_tree_info_content_text, "assets/transparent.png");
  memset(skill_tree_info_content_buffer, '\0', SKILL_TREE_TEXT_BUFFER_SIZE);
  snprintf(skill_tree_info_content_buffer, SKILL_TREE_TEXT_BUFFER_SIZE, "EMPTY");
  set_ui_text(skill_tree.ui_skill_tree_info_content_text, skill_tree_info_content_buffer, 
              0.08, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });

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
    set_ui_enabled(skill_tree.ui_skill_tree_root, 0);
  } else if (mode == STATION) {
    update_skill_tabs();
    // update sp text
    snprintf(skill_tree_sp_buffer, SKILL_TREE_TEXT_BUFFER_SIZE, "SP %d",
             st_player.skill_points);
    set_ui_text(skill_tree.ui_skill_tree_sp_text, skill_tree_sp_buffer,
                0.5, T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  }
}

void toggle_skill_tree() {
  if (ui_intermediate_root->enabled) {
    return;
  }
  if (skill_tree.ui_skill_tree_root->enabled) {
    set_ui_enabled(skill_tree.ui_skill_tree_root, 0);
    CURSOR_ENABLED = 0;
  } else {
    set_ui_enabled(skill_tree.ui_skill_tree_root, 1);
    set_ui_enabled(inventory.ui_inventory_root, 0);
    set_ui_enabled(ui_esc_root, 0);
    set_ui_enabled(ui_render_root, 0);
    set_ui_enabled(ui_control_root, 0);
    CURSOR_ENABLED = 1;
  }
}

void init_skills() {
  /*
  ===================
    Survival Skills
  ===================
  */
  // LEVEL 1
  skill_tree.skill_survival_lv1.parent_skill = NULL;
  skill_tree.skill_survival_lv1.is_unlocked = 0;
  snprintf(skill_tree.skill_survival_lv1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE SURVIVAL LV1");
  snprintf(skill_tree.skill_survival_lv1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE SURVIVAL LV1\nSKILLS");
  skill_tree.skill_survival_lv1.skill_level = 1;
  skill_tree.skill_survival_lv1.skill_type = T_SURVIVAL;
  skill_tree.skill_survival_lv1.skill_id = ID_NOT_SKILL;

  skill_tree.skill_survival_lv1_skill_1.parent_skill = &skill_tree.skill_survival_lv1;
  skill_tree.skill_survival_lv1_skill_1.is_unlocked = 0;
  snprintf(skill_tree.skill_survival_lv1_skill_1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "HEALTH BOOSTER");
  snprintf(skill_tree.skill_survival_lv1_skill_1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ADD 20 HP");
  skill_tree.skill_survival_lv1_skill_1.skill_level = 1;
  skill_tree.skill_survival_lv1_skill_1.skill_type = T_SURVIVAL;
  skill_tree.skill_survival_lv1_skill_1.skill_id = ID_SURVIVAL_LV1_SKILL_1;

  skill_tree.skill_survival_lv1_skill_2.parent_skill = &skill_tree.skill_survival_lv1;
  skill_tree.skill_survival_lv1_skill_2.is_unlocked = 0;
  snprintf(skill_tree.skill_survival_lv1_skill_2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "SHIELD BOOSTER");
  snprintf(skill_tree.skill_survival_lv1_skill_2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ADD 20 SHIELD");
  skill_tree.skill_survival_lv1_skill_2.skill_level = 1;
  skill_tree.skill_survival_lv1_skill_2.skill_type = T_SURVIVAL;
  skill_tree.skill_survival_lv1_skill_2.skill_id = ID_SURVIVAL_LV1_SKILL_2;

  // LEVEL 2
  skill_tree.skill_survival_lv2.parent_skill = &skill_tree.skill_survival_lv1;
  skill_tree.skill_survival_lv2.is_unlocked = 0;
  snprintf(skill_tree.skill_survival_lv2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE SURVIVAL LV2");
  snprintf(skill_tree.skill_survival_lv2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE SURVIVAL LV2\nSKILLS");
  skill_tree.skill_survival_lv2.skill_level = 2;
  skill_tree.skill_survival_lv2.skill_type = T_SURVIVAL;
  skill_tree.skill_survival_lv2.skill_id = ID_NOT_SKILL;

  skill_tree.skill_survival_lv2_skill_1.parent_skill = &skill_tree.skill_survival_lv2;
  skill_tree.skill_survival_lv2_skill_1.is_unlocked = 0;
  snprintf(skill_tree.skill_survival_lv2_skill_1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "HEART SHIELD");
  snprintf(skill_tree.skill_survival_lv2_skill_1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ADD 20 HP AND 20 SHIELD");
  skill_tree.skill_survival_lv2_skill_1.skill_level = 2;
  skill_tree.skill_survival_lv2_skill_1.skill_type = T_SURVIVAL;
  skill_tree.skill_survival_lv2_skill_1.skill_id = ID_SURVIVAL_LV2_SKILL_1;

  skill_tree.skill_survival_lv2_skill_2.parent_skill = &skill_tree.skill_survival_lv2;
  skill_tree.skill_survival_lv2_skill_2.is_unlocked = 0;
  snprintf(skill_tree.skill_survival_lv2_skill_2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "HEALTH BOOSTER");
  snprintf(skill_tree.skill_survival_lv2_skill_2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ADD 20 HP");
  skill_tree.skill_survival_lv2_skill_2.skill_level = 2;
  skill_tree.skill_survival_lv2_skill_2.skill_type = T_SURVIVAL;
  skill_tree.skill_survival_lv2_skill_2.skill_id = ID_SURVIVAL_LV2_SKILL_2;

  // LEVEL 3
  skill_tree.skill_survival_lv3.parent_skill = &skill_tree.skill_survival_lv2;
  skill_tree.skill_survival_lv3.is_unlocked = 0;
  snprintf(skill_tree.skill_survival_lv3.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE SURVIVAL LV3");
  snprintf(skill_tree.skill_survival_lv3.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE SURVIVAL LV3\nSKILLS");
  skill_tree.skill_survival_lv3.skill_level = 3;
  skill_tree.skill_survival_lv3.skill_type = T_SURVIVAL;
  skill_tree.skill_survival_lv3.skill_id = ID_NOT_SKILL;

  skill_tree.skill_survival_lv3_skill_1.parent_skill = &skill_tree.skill_survival_lv3;
  skill_tree.skill_survival_lv3_skill_1.is_unlocked = 0;
  snprintf(skill_tree.skill_survival_lv3_skill_1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "SPAWN SLASHER");
  snprintf(skill_tree.skill_survival_lv3_skill_1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "REDUCE ENEMY SPAWN\nRATE BY 2%%");
  skill_tree.skill_survival_lv3_skill_1.skill_level = 3;
  skill_tree.skill_survival_lv3_skill_1.skill_type = T_SURVIVAL;
  skill_tree.skill_survival_lv3_skill_1.skill_id = ID_SURVIVAL_LV3_SKILL_1;

  skill_tree.skill_survival_lv3_skill_2.parent_skill = &skill_tree.skill_survival_lv3;
  skill_tree.skill_survival_lv3_skill_2.is_unlocked = 0;
  snprintf(skill_tree.skill_survival_lv3_skill_2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "SPAWN SLAYER");
  snprintf(skill_tree.skill_survival_lv3_skill_2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "REDUCE ENEMY SPAWN\nRATE BY 3%%");
  skill_tree.skill_survival_lv3_skill_2.skill_level = 3;
  skill_tree.skill_survival_lv3_skill_2.skill_type = T_SURVIVAL;
  skill_tree.skill_survival_lv3_skill_2.skill_id = ID_SURVIVAL_LV3_SKILL_2;

  // LEVEL 4
  skill_tree.skill_survival_lv4.parent_skill = &skill_tree.skill_survival_lv3;
  skill_tree.skill_survival_lv4.is_unlocked = 0;
  snprintf(skill_tree.skill_survival_lv4.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE SURVIVAL LV4");
  snprintf(skill_tree.skill_survival_lv4.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE SURVIVAL LV4\nSKILLS");
  skill_tree.skill_survival_lv4.skill_level = 4;
  skill_tree.skill_survival_lv4.skill_type = T_SURVIVAL;
  skill_tree.skill_survival_lv4.skill_id = ID_NOT_SKILL;

  skill_tree.skill_survival_lv4_skill_1.parent_skill = &skill_tree.skill_survival_lv4;
  skill_tree.skill_survival_lv4_skill_1.is_unlocked = 0;
  snprintf(skill_tree.skill_survival_lv4_skill_1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "BEAR STANCE");
  snprintf(skill_tree.skill_survival_lv4_skill_1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "REDUCE ENEMY SPAWN\nRATE BY 1%%\nADD 20 HP");
  skill_tree.skill_survival_lv4_skill_1.skill_level = 4;
  skill_tree.skill_survival_lv4_skill_1.skill_type = T_SURVIVAL;
  skill_tree.skill_survival_lv4_skill_1.skill_id = ID_SURVIVAL_LV3_SKILL_1;

  skill_tree.skill_survival_lv4_skill_2.parent_skill = &skill_tree.skill_survival_lv4;
  skill_tree.skill_survival_lv4_skill_2.is_unlocked = 0;
  snprintf(skill_tree.skill_survival_lv4_skill_2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "TURTLE STANCE");
  snprintf(skill_tree.skill_survival_lv4_skill_2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "REDUCE ENEMY SPAWN\nRATE BY 1%%\nADD 20 SHIELD");
  skill_tree.skill_survival_lv4_skill_2.skill_level = 4;
  skill_tree.skill_survival_lv4_skill_2.skill_type = T_SURVIVAL;
  skill_tree.skill_survival_lv4_skill_2.skill_id = ID_SURVIVAL_LV3_SKILL_2;

  /*
  =================
    Combat Skills
  =================
  */
  // LEVEL 1
  skill_tree.skill_combat_lv1.parent_skill = NULL;
  skill_tree.skill_combat_lv1.is_unlocked = 0;
  snprintf(skill_tree.skill_combat_lv1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE COMBAT LV1");
  snprintf(skill_tree.skill_combat_lv1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE COMBAT LV1\nSKILLS");
  skill_tree.skill_combat_lv1.skill_level = 1;
  skill_tree.skill_combat_lv1.skill_type = T_COMBAT;
  skill_tree.skill_combat_lv1.skill_id = ID_NOT_SKILL;

  skill_tree.skill_combat_lv1_skill_1.parent_skill = &skill_tree.skill_combat_lv1;
  skill_tree.skill_combat_lv1_skill_1.is_unlocked = 0;
  snprintf(skill_tree.skill_combat_lv1_skill_1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "SILVER BULLET");
  snprintf(skill_tree.skill_combat_lv1_skill_1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ADD 20%% ATTACK DAMAGE");
  skill_tree.skill_combat_lv1_skill_1.skill_level = 1;
  skill_tree.skill_combat_lv1_skill_1.skill_type = T_COMBAT;
  skill_tree.skill_combat_lv1_skill_1.skill_id = ID_COMBAT_LV1_SKILL_1;

  skill_tree.skill_combat_lv1_skill_2.parent_skill = &skill_tree.skill_combat_lv1;
  skill_tree.skill_combat_lv1_skill_2.is_unlocked = 0;
  snprintf(skill_tree.skill_combat_lv1_skill_2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "POWERED TRIGGER");
  snprintf(skill_tree.skill_combat_lv1_skill_2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "INCREASE 20%% FIRE RATE");
  skill_tree.skill_combat_lv1_skill_2.skill_level = 1;
  skill_tree.skill_combat_lv1_skill_2.skill_type = T_COMBAT;
  skill_tree.skill_combat_lv1_skill_2.skill_id = ID_COMBAT_LV1_SKILL_2;

  // LEVEL 2
  skill_tree.skill_combat_lv2.parent_skill = &skill_tree.skill_combat_lv1;
  skill_tree.skill_combat_lv2.is_unlocked = 0;
  snprintf(skill_tree.skill_combat_lv2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE COMBAT LV2");
  snprintf(skill_tree.skill_combat_lv2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE COMBAT LV2\nSKILLS");
  skill_tree.skill_combat_lv2.skill_level = 2;
  skill_tree.skill_combat_lv2.skill_type = T_COMBAT;
  skill_tree.skill_combat_lv2.skill_id = ID_NOT_SKILL;

  skill_tree.skill_combat_lv2_skill_1.parent_skill = &skill_tree.skill_combat_lv2;
  skill_tree.skill_combat_lv2_skill_1.is_unlocked = 0;
  snprintf(skill_tree.skill_combat_lv2_skill_1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "BULLET VOLLEYFIRE");
  snprintf(skill_tree.skill_combat_lv2_skill_1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE,
           "ADD 20%% ATTACK DAMAGE\nAND INCREASE 20%% FIRE\nRATE");
  skill_tree.skill_combat_lv2_skill_1.skill_level = 2;
  skill_tree.skill_combat_lv2_skill_1.skill_type = T_COMBAT;
  skill_tree.skill_combat_lv2_skill_1.skill_id = ID_COMBAT_LV2_SKILL_1;

  skill_tree.skill_combat_lv2_skill_2.parent_skill = &skill_tree.skill_combat_lv2;
  skill_tree.skill_combat_lv2_skill_2.is_unlocked = 0;
  snprintf(skill_tree.skill_combat_lv2_skill_2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, ".45 ACP BULLET");
  snprintf(skill_tree.skill_combat_lv2_skill_2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE,
           "50%% LARGER ROUNDS");
  skill_tree.skill_combat_lv2_skill_2.skill_level = 2;
  skill_tree.skill_combat_lv2_skill_2.skill_type = T_COMBAT;
  skill_tree.skill_combat_lv2_skill_2.skill_id = ID_COMBAT_LV2_SKILL_2;

  // LEVEL 3
  skill_tree.skill_combat_lv3.parent_skill = &skill_tree.skill_combat_lv2;
  skill_tree.skill_combat_lv3.is_unlocked = 0;
  snprintf(skill_tree.skill_combat_lv3.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE COMBAT LV3");
  snprintf(skill_tree.skill_combat_lv3.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE COMBAT LV3\nSKILLS");
  skill_tree.skill_combat_lv3.skill_level = 3;
  skill_tree.skill_combat_lv3.skill_type = T_COMBAT;
  skill_tree.skill_combat_lv3.skill_id = ID_NOT_SKILL;

  skill_tree.skill_combat_lv3_skill_1.parent_skill = &skill_tree.skill_combat_lv3;
  skill_tree.skill_combat_lv3_skill_1.is_unlocked = 0;
  snprintf(skill_tree.skill_combat_lv3_skill_1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, ".50 BMG BULLET");
  snprintf(skill_tree.skill_combat_lv3_skill_1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE,
           "100%% LARGER ROUNDS");
  skill_tree.skill_combat_lv3_skill_1.skill_level = 3;
  skill_tree.skill_combat_lv3_skill_1.skill_type = T_COMBAT;
  skill_tree.skill_combat_lv3_skill_1.skill_id = ID_COMBAT_LV3_SKILL_1;

  skill_tree.skill_combat_lv3_skill_2.parent_skill = &skill_tree.skill_combat_lv3;
  skill_tree.skill_combat_lv3_skill_2.is_unlocked = 0;
  snprintf(skill_tree.skill_combat_lv3_skill_2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "CANNON SHOT");
  snprintf(skill_tree.skill_combat_lv3_skill_2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE,
           "ADD 25%% ATTACK DAMAGE\nDAMAGE");
  skill_tree.skill_combat_lv3_skill_2.skill_level = 3;
  skill_tree.skill_combat_lv3_skill_2.skill_type = T_COMBAT;
  skill_tree.skill_combat_lv3_skill_2.skill_id = ID_COMBAT_LV3_SKILL_2;

  // LEVEL 4
  skill_tree.skill_combat_lv4.parent_skill = &skill_tree.skill_combat_lv3;
  skill_tree.skill_combat_lv4.is_unlocked = 0;
  snprintf(skill_tree.skill_combat_lv4.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE COMBAT LV4");
  snprintf(skill_tree.skill_combat_lv4.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE COMBAT LV4\nSKILLS");
  skill_tree.skill_combat_lv4.skill_level = 4;
  skill_tree.skill_combat_lv4.skill_type = T_COMBAT;
  skill_tree.skill_combat_lv4.skill_id = ID_NOT_SKILL;

  skill_tree.skill_combat_lv4_skill_1.parent_skill = &skill_tree.skill_combat_lv4;
  skill_tree.skill_combat_lv4_skill_1.is_unlocked = 0;
  snprintf(skill_tree.skill_combat_lv4_skill_1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "DEAD EYE");
  snprintf(skill_tree.skill_combat_lv4_skill_1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE,
           "ADD 30%% ATTACK DAMAGE");
  skill_tree.skill_combat_lv4_skill_1.skill_level = 4;
  skill_tree.skill_combat_lv4_skill_1.skill_type = T_COMBAT;
  skill_tree.skill_combat_lv4_skill_1.skill_id = ID_COMBAT_LV4_SKILL_1;

  skill_tree.skill_combat_lv4_skill_2.parent_skill = &skill_tree.skill_combat_lv4;
  skill_tree.skill_combat_lv4_skill_2.is_unlocked = 0;
  snprintf(skill_tree.skill_combat_lv4_skill_2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "TIGER STANCE");
  snprintf(skill_tree.skill_combat_lv4_skill_2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE,
           "ADD 20%% ATTACK DAMAGE\nAND INCREASE 20%% FIRE\nRATE");
  skill_tree.skill_combat_lv4_skill_2.skill_level = 4;
  skill_tree.skill_combat_lv4_skill_2.skill_type = T_COMBAT;
  skill_tree.skill_combat_lv4_skill_2.skill_id = ID_COMBAT_LV4_SKILL_2;

  /*
  ======================
    Exploration Skills
  ======================
  */
  // LEVEL 1
  skill_tree.skill_exploration_lv1.parent_skill = NULL;
  skill_tree.skill_exploration_lv1.is_unlocked = 0;
  snprintf(skill_tree.skill_exploration_lv1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE EXPLORATION LV1");
  snprintf(skill_tree.skill_exploration_lv1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE EXPLORATION LV1\nSKILLS");
  skill_tree.skill_exploration_lv1.skill_level = 1;
  skill_tree.skill_exploration_lv1.skill_type = T_EXPLORATION;
  skill_tree.skill_exploration_lv1.skill_id = ID_NOT_SKILL;

  skill_tree.skill_exploration_lv1_skill_1.parent_skill = &skill_tree.skill_exploration_lv1;
  skill_tree.skill_exploration_lv1_skill_1.is_unlocked = 0;
  snprintf(skill_tree.skill_exploration_lv1_skill_1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "SPRINT");
  snprintf(skill_tree.skill_exploration_lv1_skill_1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ADD 20%% SPEED");
  skill_tree.skill_exploration_lv1_skill_1.skill_level = 1;
  skill_tree.skill_exploration_lv1_skill_1.skill_type = T_EXPLORATION;
  skill_tree.skill_exploration_lv1_skill_1.skill_id = ID_EXPLORATION_LV1_SKILL_1;

  skill_tree.skill_exploration_lv1_skill_2.parent_skill = &skill_tree.skill_exploration_lv1;
  skill_tree.skill_exploration_lv1_skill_2.is_unlocked = 0;
  snprintf(skill_tree.skill_exploration_lv1_skill_2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "FORTUNE");
  snprintf(skill_tree.skill_exploration_lv1_skill_2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "EASIER TO FIND RARER ITEMS (2%%)");
  skill_tree.skill_exploration_lv1_skill_2.skill_level = 1;
  skill_tree.skill_exploration_lv1_skill_2.skill_type = T_EXPLORATION;
  skill_tree.skill_exploration_lv1_skill_2.skill_id = ID_EXPLORATION_LV1_SKILL_2;

  // LEVEL 2
  skill_tree.skill_exploration_lv2.parent_skill = &skill_tree.skill_exploration_lv1;
  skill_tree.skill_exploration_lv2.is_unlocked = 0;
  snprintf(skill_tree.skill_exploration_lv2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE EXPLORATION LV2");
  snprintf(skill_tree.skill_exploration_lv2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE EXPLORATION LV2\nSKILLS");
  skill_tree.skill_exploration_lv2.skill_level = 2;
  skill_tree.skill_exploration_lv2.skill_type = T_EXPLORATION;
  skill_tree.skill_exploration_lv2.skill_id = ID_NOT_SKILL;

  skill_tree.skill_exploration_lv2_skill_1.parent_skill = &skill_tree.skill_exploration_lv2;
  skill_tree.skill_exploration_lv2_skill_1.is_unlocked = 0;
  snprintf(skill_tree.skill_exploration_lv2_skill_1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "TREASURE HUNTER");
  snprintf(skill_tree.skill_exploration_lv2_skill_1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE,
           "ADD 20%% SPEED AND FIND\nRARER ITEMS EASIER (2%%)");
  skill_tree.skill_exploration_lv2_skill_1.skill_level = 2;
  skill_tree.skill_exploration_lv2_skill_1.skill_type = T_EXPLORATION;
  skill_tree.skill_exploration_lv2_skill_1.skill_id = ID_EXPLORATION_LV2_SKILL_1;

  skill_tree.skill_exploration_lv2_skill_2.parent_skill = &skill_tree.skill_exploration_lv2;
  skill_tree.skill_exploration_lv2_skill_2.is_unlocked = 0;
  snprintf(skill_tree.skill_exploration_lv2_skill_2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "TREASURE MAP");
  snprintf(skill_tree.skill_exploration_lv2_skill_2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE,
           "FIND RARER ITEMS\n 4%% EASIER");
  skill_tree.skill_exploration_lv2_skill_2.skill_level = 2;
  skill_tree.skill_exploration_lv2_skill_2.skill_type = T_EXPLORATION;
  skill_tree.skill_exploration_lv2_skill_2.skill_id = ID_EXPLORATION_LV2_SKILL_2;

  // LEVEL 3
  skill_tree.skill_exploration_lv3.parent_skill = &skill_tree.skill_exploration_lv2;
  skill_tree.skill_exploration_lv3.is_unlocked = 0;
  snprintf(skill_tree.skill_exploration_lv3.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE EXPLORATION LV3");
  snprintf(skill_tree.skill_exploration_lv3.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE EXPLORATION LV3\nSKILLS");
  skill_tree.skill_exploration_lv3.skill_level = 3;
  skill_tree.skill_exploration_lv3.skill_type = T_EXPLORATION;
  skill_tree.skill_exploration_lv3.skill_id = ID_NOT_SKILL;

  skill_tree.skill_exploration_lv3_skill_1.parent_skill = &skill_tree.skill_exploration_lv3;
  skill_tree.skill_exploration_lv3_skill_1.is_unlocked = 0;
  snprintf(skill_tree.skill_exploration_lv3_skill_1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "LEVEL CHASER");
  snprintf(skill_tree.skill_exploration_lv3_skill_1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE,
           "GAIN XP 5%%\nFASTER");
  skill_tree.skill_exploration_lv3_skill_1.skill_level = 3;
  skill_tree.skill_exploration_lv3_skill_1.skill_type = T_EXPLORATION;
  skill_tree.skill_exploration_lv3_skill_1.skill_id = ID_EXPLORATION_LV3_SKILL_1;

  skill_tree.skill_exploration_lv3_skill_2.parent_skill = &skill_tree.skill_exploration_lv3;
  skill_tree.skill_exploration_lv3_skill_2.is_unlocked = 0;
  snprintf(skill_tree.skill_exploration_lv3_skill_2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "LEVEL BREAKER");
  snprintf(skill_tree.skill_exploration_lv3_skill_2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE,
           "GAIN XP 10%%\nFASTER");
  skill_tree.skill_exploration_lv3_skill_2.skill_level = 3;
  skill_tree.skill_exploration_lv3_skill_2.skill_type = T_EXPLORATION;
  skill_tree.skill_exploration_lv3_skill_2.skill_id = ID_EXPLORATION_LV3_SKILL_2;

  // LEVEL 4
  skill_tree.skill_exploration_lv4.parent_skill = &skill_tree.skill_exploration_lv3;
  skill_tree.skill_exploration_lv4.is_unlocked = 0;
  snprintf(skill_tree.skill_exploration_lv4.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE EXPLORATION LV4");
  snprintf(skill_tree.skill_exploration_lv4.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE, "ENABLE EXPLORATION LV4\nSKILLS");
  skill_tree.skill_exploration_lv4.skill_level = 4;
  skill_tree.skill_exploration_lv4.skill_type = T_EXPLORATION;
  skill_tree.skill_exploration_lv4.skill_id = ID_NOT_SKILL;

  skill_tree.skill_exploration_lv4_skill_1.parent_skill = &skill_tree.skill_exploration_lv4;
  skill_tree.skill_exploration_lv4_skill_1.is_unlocked = 0;
  snprintf(skill_tree.skill_exploration_lv4_skill_1.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "STAR MEDAL");
  snprintf(skill_tree.skill_exploration_lv4_skill_1.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE,
           "GAIN XP 50%%\nFASTER");
  skill_tree.skill_exploration_lv4_skill_1.skill_level = 4;
  skill_tree.skill_exploration_lv4_skill_1.skill_type = T_EXPLORATION;
  skill_tree.skill_exploration_lv4_skill_1.skill_id = ID_EXPLORATION_LV4_SKILL_1;

  skill_tree.skill_exploration_lv4_skill_2.parent_skill = &skill_tree.skill_exploration_lv4;
  skill_tree.skill_exploration_lv4_skill_2.is_unlocked = 0;
  snprintf(skill_tree.skill_exploration_lv4_skill_2.skill_name,
           SKILL_TREE_TEXT_BUFFER_SIZE, "EXOSKELETON LEG");
  snprintf(skill_tree.skill_exploration_lv4_skill_2.skill_content,
           SKILL_TREE_TEXT_BUFFER_SIZE,
           "MOVE 50%% FASTER");
  skill_tree.skill_exploration_lv4_skill_2.skill_level = 4;
  skill_tree.skill_exploration_lv4_skill_2.skill_type = T_EXPLORATION;
  skill_tree.skill_exploration_lv4_skill_2.skill_id = ID_EXPLORATION_LV4_SKILL_2;
}

void switch_survival_tab(UI_COMP *ui_tab_comp, void *unused) {
  skill_tree.current_page = T_SURVIVAL;
}

void switch_combat_tab(UI_COMP *ui_tab_comp, void *unused) {
  skill_tree.current_page = T_COMBAT;
}

void switch_exploration_tab(UI_COMP *ui_tab_comp, void *unused) {
  skill_tree.current_page = T_EXPLORATION;
}

void update_skill_tabs() {
  switch (skill_tree.current_page) {
    case T_SURVIVAL:
      set_ui_texture(skill_tree.ui_skill_tree_survival_background, "assets/ui/hud_color.png");
      set_ui_texture(skill_tree.ui_skill_tree_combat_background, "assets/ui/hud_color_bg.png");
      set_ui_texture(skill_tree.ui_skill_tree_exploration_background, "assets/ui/hud_color_bg.png");

      // Lv1
      if (skill_tree.skill_survival_lv1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_1_enable_icon, "assets/ui/skill/lv1_enable_survival.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_1_enable_icon, "assets/ui/skill/lv1_disable_survival.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_1_enable_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_1_enable_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_1_enable_background, (void *) skill_on_click, &skill_tree.skill_survival_lv1);
      if (skill_tree.skill_survival_lv1_skill_1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_1_icon, "assets/ui/skill/survival_hp_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_1_icon, "assets/ui/skill/survival_hp_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_1_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv1_skill_1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_1_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv1_skill_1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_1_skill_1_background, (void *) skill_on_click, &skill_tree.skill_survival_lv1_skill_1);
      if (skill_tree.skill_survival_lv1_skill_2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_2_icon, "assets/ui/skill/survival_shield_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_2_icon, "assets/ui/skill/survival_shield_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_1_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv1_skill_2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_1_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv1_skill_2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_1_skill_2_background, (void *) skill_on_click, &skill_tree.skill_survival_lv1_skill_2);

      // Lv2
      if (skill_tree.skill_survival_lv2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_2_enable_icon, "assets/ui/skill/lv2_enable_survival.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_2_enable_icon, "assets/ui/skill/lv2_disable_survival.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_2_enable_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_2_enable_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_2_enable_background, (void *) skill_on_click, &skill_tree.skill_survival_lv2);
      if (skill_tree.skill_survival_lv2_skill_1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_1_icon, "assets/ui/skill/survival_hp_shield_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_1_icon, "assets/ui/skill/survival_hp_shield_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_2_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv2_skill_1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_2_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv2_skill_1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_2_skill_1_background, (void *) skill_on_click, &skill_tree.skill_survival_lv2_skill_1);
      if (skill_tree.skill_survival_lv2_skill_2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_2_icon, "assets/ui/skill/survival_hp_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_2_icon, "assets/ui/skill/survival_hp_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_2_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv2_skill_2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_2_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv2_skill_2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_2_skill_2_background, (void *) skill_on_click, &skill_tree.skill_survival_lv2_skill_2);

      // Lv3
      if (skill_tree.skill_survival_lv3.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_3_enable_icon, "assets/ui/skill/lv3_enable_survival.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_3_enable_icon, "assets/ui/skill/lv3_disable_survival.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_3_enable_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv3);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_3_enable_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv3);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_3_enable_background, (void *) skill_on_click, &skill_tree.skill_survival_lv3);
      if (skill_tree.skill_survival_lv3_skill_1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_1_icon, "assets/ui/skill/survival_reduce_enemy_spawn_2_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_1_icon, "assets/ui/skill/survival_reduce_enemy_spawn_2_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_3_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv3_skill_1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_3_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv3_skill_1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_3_skill_1_background, (void *) skill_on_click, &skill_tree.skill_survival_lv3_skill_1);
      if (skill_tree.skill_survival_lv3_skill_2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_2_icon, "assets/ui/skill/survival_reduce_enemy_spawn_3_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_2_icon, "assets/ui/skill/survival_reduce_enemy_spawn_3_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_3_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv3_skill_2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_3_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv3_skill_2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_3_skill_2_background, (void *) skill_on_click, &skill_tree.skill_survival_lv3_skill_2);

      // Lv4
      if (skill_tree.skill_survival_lv4.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_4_enable_icon, "assets/ui/skill/lv4_enable_survival.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_4_enable_icon, "assets/ui/skill/lv4_disable_survival.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_4_enable_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv4);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_4_enable_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv4);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_4_enable_background, (void *) skill_on_click, &skill_tree.skill_survival_lv4);
      if (skill_tree.skill_survival_lv4_skill_1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_1_icon, "assets/ui/skill/survival_bear_stance_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_1_icon, "assets/ui/skill/survival_bear_stance_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_4_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv4_skill_1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_4_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv4_skill_1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_4_skill_1_background, (void *) skill_on_click, &skill_tree.skill_survival_lv4_skill_1);
      if (skill_tree.skill_survival_lv4_skill_2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_2_icon, "assets/ui/skill/survival_turtle_stance_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_2_icon, "assets/ui/skill/survival_turtle_stance_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_4_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_survival_lv4_skill_2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_4_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_survival_lv4_skill_2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_4_skill_2_background, (void *) skill_on_click, &skill_tree.skill_survival_lv4_skill_2);
      break;
    case T_COMBAT:
      set_ui_texture(skill_tree.ui_skill_tree_survival_background, "assets/ui/hud_color_bg.png");
      set_ui_texture(skill_tree.ui_skill_tree_combat_background, "assets/ui/hud_color.png");
      set_ui_texture(skill_tree.ui_skill_tree_exploration_background, "assets/ui/hud_color_bg.png");

      // Lv1
      if (skill_tree.skill_combat_lv1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_1_enable_icon, "assets/ui/skill/lv1_enable_combat.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_1_enable_icon, "assets/ui/skill/lv1_disable_combat.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_1_enable_background, skill_on_hover_wrapper, &skill_tree.skill_combat_lv1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_1_enable_background, skill_off_hover_wrapper, &skill_tree.skill_combat_lv1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_1_enable_background, (void *) skill_on_click, &skill_tree.skill_combat_lv1);
      if (skill_tree.skill_combat_lv1_skill_1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_1_icon, "assets/ui/skill/combat_atk_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_1_icon, "assets/ui/skill/combat_atk_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_1_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_combat_lv1_skill_1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_1_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_combat_lv1_skill_1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_1_skill_1_background, (void *) skill_on_click, &skill_tree.skill_combat_lv1_skill_1);
      if (skill_tree.skill_combat_lv1_skill_2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_2_icon, "assets/ui/skill/combat_fire_rate_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_2_icon, "assets/ui/skill/combat_fire_rate_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_1_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_combat_lv1_skill_2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_1_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_combat_lv1_skill_2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_1_skill_2_background, (void *) skill_on_click, &skill_tree.skill_combat_lv1_skill_2);

      // Lv2
      if (skill_tree.skill_combat_lv2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_2_enable_icon, "assets/ui/skill/lv2_enable_combat.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_2_enable_icon, "assets/ui/skill/lv2_disable_combat.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_2_enable_background, skill_on_hover_wrapper, &skill_tree.skill_combat_lv2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_2_enable_background, skill_off_hover_wrapper, &skill_tree.skill_combat_lv2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_2_enable_background, (void *) skill_on_click, &skill_tree.skill_combat_lv2);
      if (skill_tree.skill_combat_lv2_skill_1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_1_icon, "assets/ui/skill/combat_atk_fire_rate_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_1_icon, "assets/ui/skill/combat_atk_fire_rate_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_2_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_combat_lv2_skill_1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_2_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_combat_lv2_skill_1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_2_skill_1_background, (void *) skill_on_click, &skill_tree.skill_combat_lv2_skill_1);
      if (skill_tree.skill_combat_lv2_skill_2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_2_icon, "assets/ui/skill/combat_round_size_50_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_2_icon, "assets/ui/skill/combat_round_size_50_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_2_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_combat_lv2_skill_2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_2_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_combat_lv2_skill_2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_2_skill_2_background, (void *) skill_on_click, &skill_tree.skill_combat_lv2_skill_2);

      // Lv3
      if (skill_tree.skill_combat_lv3.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_3_enable_icon, "assets/ui/skill/lv3_enable_combat.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_3_enable_icon, "assets/ui/skill/lv3_disable_combat.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_3_enable_background, skill_on_hover_wrapper, &skill_tree.skill_combat_lv3);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_3_enable_background, skill_off_hover_wrapper, &skill_tree.skill_combat_lv3);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_3_enable_background, (void *) skill_on_click, &skill_tree.skill_combat_lv3);
      if (skill_tree.skill_combat_lv3_skill_1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_1_icon, "assets/ui/skill/combat_round_size_100_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_1_icon, "assets/ui/skill/combat_round_size_100_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_3_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_combat_lv3_skill_1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_3_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_combat_lv3_skill_1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_3_skill_1_background, (void *) skill_on_click, &skill_tree.skill_combat_lv3_skill_1);
      if (skill_tree.skill_combat_lv3_skill_2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_2_icon, "assets/ui/skill/combat_25_atk_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_2_icon, "assets/ui/skill/combat_25_atk_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_3_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_combat_lv3_skill_2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_3_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_combat_lv3_skill_2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_3_skill_2_background, (void *) skill_on_click, &skill_tree.skill_combat_lv3_skill_2);

      // Lv4
      if (skill_tree.skill_combat_lv4.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_4_enable_icon, "assets/ui/skill/lv4_enable_combat.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_4_enable_icon, "assets/ui/skill/lv4_disable_combat.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_4_enable_background, skill_on_hover_wrapper, &skill_tree.skill_combat_lv4);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_4_enable_background, skill_off_hover_wrapper, &skill_tree.skill_combat_lv4);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_4_enable_background, (void *) skill_on_click, &skill_tree.skill_combat_lv4);
      if (skill_tree.skill_combat_lv4_skill_1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_1_icon, "assets/ui/skill/combat_deadeye_enabled.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_1_icon, "assets/ui/skill/combat_deadeye_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_4_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_combat_lv4_skill_1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_4_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_combat_lv4_skill_1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_4_skill_1_background, (void *) skill_on_click, &skill_tree.skill_combat_lv4_skill_1);
      if (skill_tree.skill_combat_lv4_skill_2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_2_icon, "assets/ui/skill/combat_tiger_stance_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_2_icon, "assets/ui/skill/combat_tiger_stance_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_4_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_combat_lv4_skill_2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_4_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_combat_lv4_skill_2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_4_skill_2_background, (void *) skill_on_click, &skill_tree.skill_combat_lv4_skill_2);
      break;
    case T_EXPLORATION:
      set_ui_texture(skill_tree.ui_skill_tree_survival_background, "assets/ui/hud_color_bg.png");
      set_ui_texture(skill_tree.ui_skill_tree_combat_background, "assets/ui/hud_color_bg.png");
      set_ui_texture(skill_tree.ui_skill_tree_exploration_background, "assets/ui/hud_color.png");
      // Lv1
      if (skill_tree.skill_exploration_lv1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_1_enable_icon, "assets/ui/skill/lv1_enable_exploration.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_1_enable_icon, "assets/ui/skill/lv1_disable_exploration.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_1_enable_background, skill_on_hover_wrapper, &skill_tree.skill_exploration_lv1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_1_enable_background, skill_off_hover_wrapper, &skill_tree.skill_exploration_lv1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_1_enable_background, (void *) skill_on_click, &skill_tree.skill_exploration_lv1);
      if (skill_tree.skill_exploration_lv1_skill_1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_1_icon, "assets/ui/skill/exploration_sprint_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_1_icon, "assets/ui/skill/exploration_sprint_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_1_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_exploration_lv1_skill_1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_1_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_exploration_lv1_skill_1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_1_skill_1_background, (void *) skill_on_click, &skill_tree.skill_exploration_lv1_skill_1);
      if (skill_tree.skill_exploration_lv1_skill_2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_2_icon, "assets/ui/skill/exploration_loot_rate_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_1_skill_2_icon, "assets/ui/skill/exploration_loot_rate_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_1_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_exploration_lv1_skill_2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_1_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_exploration_lv1_skill_2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_1_skill_2_background, (void *) skill_on_click, &skill_tree.skill_exploration_lv1_skill_2);

      // Lv2
      if (skill_tree.skill_exploration_lv2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_2_enable_icon, "assets/ui/skill/lv2_enable_exploration.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_2_enable_icon, "assets/ui/skill/lv2_disable_exploration.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_2_enable_background, skill_on_hover_wrapper, &skill_tree.skill_exploration_lv2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_2_enable_background, skill_off_hover_wrapper, &skill_tree.skill_exploration_lv2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_2_enable_background, (void *) skill_on_click, &skill_tree.skill_exploration_lv2);
      if (skill_tree.skill_exploration_lv2_skill_1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_1_icon, "assets/ui/skill/exploration_speed_loot_rate_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_1_icon, "assets/ui/skill/exploration_speed_loot_rate_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_2_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_exploration_lv2_skill_1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_2_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_exploration_lv2_skill_1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_2_skill_1_background, (void *) skill_on_click, &skill_tree.skill_exploration_lv2_skill_1);
      if (skill_tree.skill_exploration_lv2_skill_2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_2_icon, "assets/ui/skill/exploration_loot_rate_4_enabled.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_2_skill_2_icon, "assets/ui/skill/exploration_loot_rate_4_disabled.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_2_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_exploration_lv2_skill_2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_2_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_exploration_lv2_skill_2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_2_skill_2_background, (void *) skill_on_click, &skill_tree.skill_exploration_lv2_skill_2);

      // Lv3
      if (skill_tree.skill_exploration_lv3.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_3_enable_icon, "assets/ui/skill/lv3_enable_exploration.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_3_enable_icon, "assets/ui/skill/lv3_disable_exploration.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_3_enable_background, skill_on_hover_wrapper, &skill_tree.skill_exploration_lv3);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_3_enable_background, skill_off_hover_wrapper, &skill_tree.skill_exploration_lv3);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_3_enable_background, (void *) skill_on_click, &skill_tree.skill_exploration_lv3);
      if (skill_tree.skill_exploration_lv3_skill_1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_1_icon, "assets/ui/skill/exploration_exp_5_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_1_icon, "assets/ui/skill/exploration_exp_5_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_3_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_exploration_lv3_skill_1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_3_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_exploration_lv3_skill_1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_3_skill_1_background, (void *) skill_on_click, &skill_tree.skill_exploration_lv3_skill_1);
      if (skill_tree.skill_exploration_lv3_skill_2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_2_icon, "assets/ui/skill/exploration_exp_50_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_3_skill_2_icon, "assets/ui/skill/exploration_exp_50_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_3_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_exploration_lv3_skill_2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_3_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_exploration_lv3_skill_2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_3_skill_2_background, (void *) skill_on_click, &skill_tree.skill_exploration_lv3_skill_2);

      // Lv4
      if (skill_tree.skill_exploration_lv4.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_4_enable_icon, "assets/ui/skill/lv4_enable_exploration.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_4_enable_icon, "assets/ui/skill/lv4_disable_exploration.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_4_enable_background, skill_on_hover_wrapper, &skill_tree.skill_exploration_lv4);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_4_enable_background, skill_off_hover_wrapper, &skill_tree.skill_exploration_lv4);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_4_enable_background, (void *) skill_on_click, &skill_tree.skill_exploration_lv4);
      if (skill_tree.skill_exploration_lv4_skill_1.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_1_icon, "assets/ui/skill/exploration_star_medal_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_1_icon, "assets/ui/skill/exploration_star_medal_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_4_skill_1_background, skill_on_hover_wrapper, &skill_tree.skill_exploration_lv4_skill_1);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_4_skill_1_background, skill_off_hover_wrapper, &skill_tree.skill_exploration_lv4_skill_1);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_4_skill_1_background, (void *) skill_on_click, &skill_tree.skill_exploration_lv4_skill_1);
      if (skill_tree.skill_exploration_lv4_skill_2.is_unlocked) set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_2_icon, "assets/ui/skill/exploration_speed_enable.png");
      else set_ui_texture(skill_tree.ui_skill_tree_lv_4_skill_2_icon, "assets/ui/skill/exploration_speed_disable.png");
      set_ui_on_hover(skill_tree.ui_skill_tree_lv_4_skill_2_background, skill_on_hover_wrapper, &skill_tree.skill_exploration_lv4_skill_2);
      set_ui_no_hover(skill_tree.ui_skill_tree_lv_4_skill_2_background, skill_off_hover_wrapper, &skill_tree.skill_exploration_lv4_skill_2);
      set_ui_on_click(skill_tree.ui_skill_tree_lv_4_skill_2_background, (void *) skill_on_click, &skill_tree.skill_exploration_lv4_skill_2);
      break;
    default:
      break;
  }
}

void skill_on_hover_wrapper(UI_COMP *ui_comp, void *arg) {
  skill_on_hover(ui_comp, (SKILL *)arg);
}

void skill_on_hover(UI_COMP *ui_comp, SKILL *skill_slot) {
  set_ui_texture(ui_comp, "assets/ui/test.png");
  snprintf(skill_tree_info_title_buffer, SKILL_TREE_TEXT_BUFFER_SIZE,
                 "%s", skill_slot->skill_name);
  set_ui_text(skill_tree.ui_skill_tree_info_title_text,
              skill_tree_info_title_buffer, 0.08,
              T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
  snprintf(skill_tree_info_content_buffer, SKILL_TREE_TEXT_BUFFER_SIZE,
                 "%s", skill_slot->skill_content);
  set_ui_text(skill_tree.ui_skill_tree_info_content_text,
              skill_tree_info_content_buffer, 0.08,
              T_LEFT, fixed_sys, (vec3) { 0.0, 0.0, 0.0 });
}

void skill_off_hover_wrapper(UI_COMP *ui_comp, void *arg) {
  skill_off_hover(ui_comp, (SKILL *)arg);
}

void skill_off_hover(UI_COMP *ui_comp, SKILL *skill_slot) {
  set_ui_texture(ui_comp, "assets/ui/hud_color.png");
}

void skill_on_click(UI_COMP *ui_comp, SKILL *skill_slot) {
  // return if already is_unlocked
  if (skill_slot->is_unlocked) {
    return;
  } else {
    // check if can unlock
    if (st_player.skill_points > 0 && (skill_slot->parent_skill == NULL ||
        skill_slot->parent_skill->is_unlocked)) {
      st_player.skill_points -= 1;
      skill_slot->is_unlocked = 1;
      enable_skill(skill_slot);
      printf("%s UNLOCKED\n", skill_slot->skill_name);
    } else if (st_player.skill_points == 0) {
      // TODO: add popup prompt
      printf("DO NOT HAVE ENOUGH SKILL POINTS\n");
    } else if (!skill_slot->parent_skill->is_unlocked) {
      // TODO: add popup prompt
      printf("DO NOT UNLOCK PREREQUISITE SKILL\n");
    }
  }
}

void enable_skill(SKILL *skill_slot) {
  switch (skill_slot->skill_id) {
    // Survival Skills
    case ID_SURVIVAL_LV1_SKILL_1:
      st_player.max_health += 20;
      st_player.cur_health = st_player.max_health;
      break;
    case ID_SURVIVAL_LV1_SKILL_2:
      st_player.max_shield += 20;
      st_player.recharging_shield = 1;
      break;
    case ID_SURVIVAL_LV2_SKILL_1:
      st_player.max_health += 20;
      st_player.cur_health = st_player.max_health;
      st_player.max_shield += 20;
      st_player.recharging_shield = 1;
      break;
    case ID_SURVIVAL_LV2_SKILL_2:
      /* HEALTH BOOSTER */
      st_player.max_health += 20;
      st_player.cur_health = st_player.max_health;
      break;
    case ID_SURVIVAL_LV3_SKILL_1:
      /* SPAWN SLASHER */
      enemy_lower_spawn_chance += 2;
      break;
    case ID_SURVIVAL_LV3_SKILL_2:
      /* SPAWN SLAYER */
      enemy_lower_spawn_chance += 3;
      break;
    case ID_SURVIVAL_LV4_SKILL_1:
      /* BEAR STANCE */
      enemy_lower_spawn_chance += 1;
      st_player.max_health += 20;
      st_player.cur_health = st_player.max_health;
      break;
    case ID_SURVIVAL_LV4_SKILL_2:
      /* TURTLE STANCE */
      enemy_lower_spawn_chance += 1;
      st_player.max_shield += 20;
      st_player.recharging_shield = 1;
      break;
    // Combat Skills
    case ID_COMBAT_LV1_SKILL_1:
      st_player.damage += 20;
      break;
    case ID_COMBAT_LV1_SKILL_2:
      st_player.fire_rate -= 0.02;
      break;
    case ID_COMBAT_LV2_SKILL_1:
      st_player.damage += 20;
      st_player.fire_rate -= 0.02;
      break;
    case ID_COMBAT_LV2_SKILL_2:
      /* .45 ACP BULLET */
      station_mode_proj_size += 0.5;
      break;
    case ID_COMBAT_LV3_SKILL_1:
      /* .50 BMG BULLET */
      station_mode_proj_size += 1.0;
      break;
    case ID_COMBAT_LV3_SKILL_2:
      /* CANNON SHOT */
      st_player.damage += 25;
      break;
    case ID_COMBAT_LV4_SKILL_1:
      /* DEAD EYE */
      st_player.damage += 30;
      break;
    case ID_COMBAT_LV4_SKILL_2:
      /* TIGER STANCE */
      st_player.damage += 10;
      st_player.fire_rate -= 0.02;
    //Exploration Skills
    case ID_EXPLORATION_LV1_SKILL_1:
      st_player.speed += 2;
      break;
    case ID_EXPLORATION_LV1_SKILL_2:
      for (int i = 0; i < RARITY_LEVELS; i++) {
        // Rarirty Table Each Type Possibility +2%
        part_spawn_chance[i] += 2;
      }
      break;
    case ID_EXPLORATION_LV2_SKILL_1:
      st_player.speed += 2;
      for (int i = 0; i < RARITY_LEVELS; i++) {
        // Rarirty Table Each Type Possibility +2%
        part_spawn_chance[i] += 2;
      }
      break;
    case ID_EXPLORATION_LV2_SKILL_2:
      /* TREASURE MAP */
      for (int i = 0; i < RARITY_LEVELS; i++) {
        part_spawn_chance[i] += 4;
      }
      break;
    case ID_EXPLORATION_LV3_SKILL_1:
      /* LEVEL CHASER */
      station_mode_xp_offset += 0.05;
      break;
    case ID_EXPLORATION_LV3_SKILL_2:
      /* LEVEL BREAKER */
      station_mode_xp_offset += 0.1;
      break;
    case ID_EXPLORATION_LV4_SKILL_1:
      /* STAR MEDAL */
      station_mode_xp_offset += 0.5;
      break;
    case ID_EXPLORATION_LV4_SKILL_2:
      /* EXOSKELETON LEG */
      st_player.speed += 5;
    default:
      return;
  }
}

// ============================= SKILL HELPERS ===============================

int enemy_skill_diff() {
  return enemy_lower_spawn_chance;
}

void reset_enemy_skill_diff() {
  enemy_lower_spawn_chance = 0;
}

float enemy_xp_diff() {
  return station_mode_xp_offset;
}

void reset_enemy_xp_diff() {
  station_mode_xp_offset = 1.0;
}

float player_proj_size_diff() {
  return station_mode_proj_size;
}

void reset_player_proj_size_diff() {
  station_mode_proj_size = 1.0;
}
