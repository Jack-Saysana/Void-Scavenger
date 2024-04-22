#ifndef __INVENTORY_STR_H__
#define __INVENTORY_STR_H__

#include <engine/ui_component.h>

/* DEFINES */
#define NUM_INV_INFO_LINES (7)

typedef struct inventory {
  UI_COMP *ui_inventory_root;

  UI_COMP *ui_inventory_info_background;
  UI_COMP *ui_inventory_info_title_background;
  UI_COMP *ui_inventory_info_title_text;
  UI_COMP *ui_inventory_info_content_background;
  //UI_COMP *ui_inventory_info_content_text;
  UI_COMP *ui_inventory_info_content;
  UI_COMP *ui_inventory_info_lines[NUM_INV_INFO_LINES];
  UI_COMP *ui_inventory_modifier_lines[NUM_INV_INFO_LINES];

  UI_COMP *ui_inventory_background;
  UI_COMP *ui_inventory_slot_background[9];
  UI_COMP *ui_inventory_slot_icon[9];

} INVENTORY;

#endif
