#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

#define STALL_BUFFER_SIZE (128)
#define WARNING_TIME (0.15)

static UI_COMP *stallwarning;
extern F_GLYPH *fixed_sys;
unsigned int stallwarning_enabled;
static char stallwarning_text[STALL_BUFFER_SIZE];

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void enable_stallwarning();
void disable_stallwarning();

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
void add_timer(float, void *, int, void *);
