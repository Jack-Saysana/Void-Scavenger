#pragma once

#include <pthread.h>
#include <engine/engine.h>
#include <globals.h>
#include <stdio.h>
#include <string.h>

#define LEVEL_BUFFER_SIZE (128)

static UI_COMP *level;
extern F_GLYPH *fixed_sys;
static char level_buffer[LEVEL_BUFFER_SIZE];
