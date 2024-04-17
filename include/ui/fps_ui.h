#pragma once

#include <pthread.h>
#include <engine/engine.h>
#include <globals.h>
#include <stdio.h>
#include <string.h>

#define FPS_BUFFER_SIZE (128)

static UI_COMP *fps;
unsigned int fps_enabled;
extern F_GLYPH *fixed_sys;
static char fps_buffer[FPS_BUFFER_SIZE];
