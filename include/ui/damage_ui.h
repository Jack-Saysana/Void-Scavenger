#include <engine/engine.h>
#include <global_vars.h>

// Static variables

static int damage_state = 0;

// Local UI components
static UI_COMP *damage_ui = NULL;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

int add_timer(float, void *, int, void *);
