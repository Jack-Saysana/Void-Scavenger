#pragma once

#include <engine/engine.h>

static UI_COMP *console;
extern F_GLYPH *fixed_sys;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================
int is_console_enabled();
void console_ui_initialize();

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
