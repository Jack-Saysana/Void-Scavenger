#pragma once

#include <pthread.h>
#include <engine/engine.h>

static UI_COMP *console;
static UI_COMP *console_root;
static UI_COMP *console_error;
static UI_COMP *console_cursor;
unsigned int cons_cursor_enabled;
unsigned int cons_cursor_pos = 0;
extern F_GLYPH *fixed_sys;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================
int is_console_enabled();
void console_ui_initialize();

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
