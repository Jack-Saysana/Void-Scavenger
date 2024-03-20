#pragma once

#include <engine/engine.h>
#include <global_vars.h>
#include <time.h>

#define OFF (0)
#define ON  (1)

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
void set_keyboard_enabledness(int);
void cursor_on(int);
void set_game_over_screen();
void set_game_over_stats();
void clear_space_mode();
void init_space_mode();
void clear_station_mode();
void reset_player();