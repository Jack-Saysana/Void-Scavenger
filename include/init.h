#include <engine/engine.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

int init_scene();
int init_controls();

void init_ui_components();

int init_timer_queue();
void free_timer_queue();

void cleanup_gl();
void cleanup_scene();
