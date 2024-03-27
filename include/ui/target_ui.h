#include <stdio.h>
#include <cglm/cglm.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

static UI_COMP *target_ui = NULL;
static UI_COMP *target_header = NULL;
static UI_COMP *target_shield_root = NULL;
static UI_COMP *target_shield_text = NULL;
static UI_COMP *target_shield_bar_bg = NULL;
static UI_COMP *target_shield_bar = NULL;
static UI_COMP *target_health_root = NULL;
static UI_COMP *target_health_text = NULL;
static UI_COMP *target_health_bar_bg = NULL;
static UI_COMP *target_health_bar = NULL;

static UI_COMP *target_waypoint = NULL;
static size_t target_enemy = INVALID_INDEX;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void to_screen_space(vec4, vec4);
