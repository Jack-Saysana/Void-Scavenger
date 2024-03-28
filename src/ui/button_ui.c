#include <ui/button_ui.h>

UI_COMP *init_blue_button(UI_COMP *parent, vec2 pos, float width, float height,
                          int options) {
  UI_COMP *root = add_ui_comp(parent, pos, width, height, options);
  set_ui_texture(root, "./assets/ui/blue_btn/bg.png");

  UI_COMP *top = add_ui_comp(root, (vec2) { 0.5, 0.0 }, 1.0, 0.05,
                             ABSOLUTE_POS | POS_UNIT_RATIO |
                             SIZE_UNIT_RATIO);
  set_ui_texture(top, "./assets/ui/blue_btn/top.png");
  set_ui_pivot(top, PIVOT_TOP);

  UI_COMP *bottom = add_ui_comp(root, (vec2) { 0.5, -1.0 }, 1.0, 0.05,
                                ABSOLUTE_POS | POS_UNIT_RATIO |
                                SIZE_UNIT_RATIO);
  set_ui_texture(bottom, "./assets/ui/blue_btn/bottom.png");
  set_ui_pivot(bottom, PIVOT_BOTTOM);

  UI_COMP *right = add_ui_comp(root, (vec2) { 1.0, -0.5 }, 0.05, 0.9,
                               ABSOLUTE_POS | POS_UNIT_RATIO |
                               SIZE_UNIT_RATIO_Y);
  set_ui_texture(right, "./assets/ui/blue_btn/right.png");
  set_ui_pivot(right, PIVOT_RIGHT);

  UI_COMP *left = add_ui_comp(root, (vec2) { 0.0, -0.5 }, 0.05, 0.9,
                              ABSOLUTE_POS | POS_UNIT_RATIO |
                              SIZE_UNIT_RATIO_Y);
  set_ui_texture(left, "./assets/ui/blue_btn/left.png");
  set_ui_pivot(left, PIVOT_LEFT);

  UI_COMP *top_left = add_ui_comp(root, (vec2) { 0.0, 0.0 }, 0.05, 0.05,
                                  ABSOLUTE_POS | POS_UNIT_RATIO |
                                  SIZE_UNIT_RATIO_Y);
  set_ui_texture(top_left, "./assets/ui/blue_btn/tl.png");

  UI_COMP *top_right = add_ui_comp(root, (vec2) { 1.0, 0.0 }, 0.05, 0.05,
                                   ABSOLUTE_POS | POS_UNIT_RATIO |
                                   SIZE_UNIT_RATIO_Y);
  set_ui_texture(top_right, "./assets/ui/blue_btn/bl_tr.png");
  set_ui_pivot(top_right, PIVOT_TOP_RIGHT);

  UI_COMP *bottom_left = add_ui_comp(root, (vec2) { 0.0, -1.0 }, 0.05, 0.05,
                                     ABSOLUTE_POS | POS_UNIT_RATIO |
                                     SIZE_UNIT_RATIO_Y);
  set_ui_texture(bottom_left, "./assets/ui/blue_btn/bl_tr.png");
  set_ui_pivot(bottom_left, PIVOT_BOTTOM_LEFT);

  UI_COMP *bottom_right = add_ui_comp(root, (vec2) { 1.0, -1.0 }, 0.05, 0.05,
                                      ABSOLUTE_POS | POS_UNIT_RATIO |
                                      SIZE_UNIT_RATIO_Y);
  set_ui_texture(bottom_right, "./assets/ui/blue_btn/br.png");
  set_ui_pivot(bottom_right, PIVOT_BOTTOM_RIGHT);

  return root;
}
