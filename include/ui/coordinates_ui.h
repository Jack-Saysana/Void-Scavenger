#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <engine/engine.h>

#define COORDS_SIZE (128)
#define VEC3_RED    {1.0f, 0.0f, 0.0f}
#define VEC3_WHITE  {1.0f, 1.0f, 1.0f}
#define WARNING_TIME (0.15)

static UI_COMP *coordinates;
extern F_GLYPH *fixed_sys;
unsigned int coordinates_enabled;
static char coords[COORDS_SIZE];
static vec3 coords_color = GLM_VEC3_ZERO_INIT;
static unsigned int is_coords_colors_switching = 0;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================
void set_coords_warning();
void stop_coords_warning();
void set_coords_color_red();
void set_coords_color_white();

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
void get_player_coordinates(vec3);
void add_timer(float, void *, int, void *);
