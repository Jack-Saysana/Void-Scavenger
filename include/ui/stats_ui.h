#include <engine/ui_component.h>
#include <ui/structs/stats_ui_str.h>
#include <global_vars.h>
#include <const.h>
#include <stdio.h>

/*
                                   STATS
Implements the functionality for defining UI components for both ship mode
and station mode.
*/

#define LEVEL_BUFFER_SIZE (128)
/* GLOBALS */
STATS stats;
static char level_buffer[LEVEL_BUFFER_SIZE];
static char xp_buffer[LEVEL_BUFFER_SIZE];

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_stats();
void update_stats();
void switch_space_hud();
void switch_station_hud();

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */

float calc_power_usage(SHIP *);
