#include <stdio.h>
#include <pthread.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

// Static variables
static int station_waypoint_enabled = 0;

// Local UI components
static UI_COMP *station_waypoint = NULL;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void to_screen_space(vec4, vec4);
void get_sp_station_pos(vec3);
