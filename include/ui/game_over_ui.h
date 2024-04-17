#pragma once

#include <pthread.h>
#include <engine/engine.h>
#include <global_vars.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define GAME_OVER_STATS_SIZE (1024)
#define INVERSE_GOLDEN_RATIO (0.618)
#define OFF                  (0)
#define ON                   (1)

static UI_COMP *game_over_root;
static UI_COMP *game_over_restart;
static UI_COMP *game_over_quit;
static UI_COMP *game_over_title;
static UI_COMP *game_over_stats;
extern F_GLYPH *fixed_sys;
char game_over_stats_buffer[GAME_OVER_STATS_SIZE];

// ======================= INTERNALLY DEFINED FUNCTIONS ======================


// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
void quit();
void reset_game();
