#include <engine/ui_component.h>
#include <ui/structs/stats_ui_str.h>
#include <global_vars.h>
#include <const.h>

/*
                                   STATS
Implements the functionality for defining UI components for both ship mode
and station mode.
*/

/* GLOBALS */
STATS stats;

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_stats();
void update_stats();
void switch_space_hud();
void switch_station_hud();

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */

float calc_power_usage(SHIP *);
