#pragma once

#include <stdio.h>
#include <engine/engine.h>

extern F_GLYPH *fixed_sys;
extern unsigned int coordinates_enabled;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
void console_ui_initialize();
int init_stats();
int init_inventory();
int init_ship_parts();
void coordinates_ui_initialize();
void update_coordinates();
void update_stats();
void update_inventory();
