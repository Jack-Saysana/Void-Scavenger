#ifndef __STATS_STR_H__
#define __STATS_STR_H__

#include <engine/ui_component.h>

/* DEFINES */

typedef struct stats {
  UI_COMP *ui_stats_root;

  UI_COMP *ui_shield_root;
  UI_COMP *ui_shield_icon;
  UI_COMP *ui_shield_border;
  UI_COMP *ui_shield_bar;

  UI_COMP *ui_health_root;
  UI_COMP *ui_health_icon;
  UI_COMP *ui_health_border;
  UI_COMP *ui_health_bar;
  UI_COMP *ui_velocity_text;

  UI_COMP *ui_exp_root;
  UI_COMP *ui_exp_border;
  UI_COMP *ui_exp_bar;

  UI_COMP *ui_energy_root;
  UI_COMP *ui_energy_border;
  UI_COMP *ui_energy_bar;

  UI_COMP *ui_thruster_root;
  UI_COMP *ui_thruster_border;
  UI_COMP *ui_thruster_bar;

} STATS;

#endif
