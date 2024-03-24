#include <engine/engine.h>
#include <global_vars.h>

// Local UI components
static UI_COMP *btn_root = NULL;
static UI_COMP *start_btn = NULL;
static UI_COMP *close_btn = NULL;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void start_game(UI_COMP *, void *);
void close_game(UI_COMP *, void *);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

UI_COMP *init_blue_button(UI_COMP *, vec2, float, float, int);
void quit();
void loading_init();
