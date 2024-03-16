#pragma once

#include <stdio.h>
#include <engine/engine.h>

extern F_GLYPH *fixed_sys;
extern unsigned int coordinates_enabled;
extern unsigned int fps_enabled;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
void console_ui_initialize();
int init_stats();
int init_inventory();
int init_ship_parts();
int init_skill_tree();
void init_target_ui();
void init_radar_ui();
void init_waypoint_ui();
void coordinates_ui_initialize();
void fps_ui_initialize();
void init_terminal_ui();
void update_coordinates();
void update_stats();
void update_inventory();
void update_fps();
void update_ship_parts();
void update_skill_tree();
void update_target_ui();
void update_radar_ui();
void update_waypoint_ui();
