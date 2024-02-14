#ifndef __SHIP_PARTS_STR_H__
#define __SHIP_PARTS_STR_H__

#include <engine/ui_component.h>

/* DEFINES */

typedef struct ship_parts {
  UI_COMP *ui_ship_parts_root;

  UI_COMP *ui_reactor_background;
  UI_COMP *ui_reactor_icon;

  UI_COMP *ui_hull_background;
  UI_COMP *ui_hull_icon;

  UI_COMP *ui_shield_background;
  UI_COMP *ui_shield_icon;

  UI_COMP *ui_weapon_background;
  UI_COMP *ui_weapon_icon;

  UI_COMP *ui_wing_background;
  UI_COMP *ui_wing_icon;

  UI_COMP *ui_thruster_background;
  UI_COMP *ui_thruster_icon;
  
} SHIP_PARTS;

#endif
