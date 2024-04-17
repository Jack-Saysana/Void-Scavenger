#include <engine/engine.h>
#include <global_vars.h>

// Local Constants
#define NUM_PHRASES (13)

// Static variables
static char phrases[NUM_PHRASES][128] = {
  "Firing thrusters ...\0",
  "Arming weapons ...\0",
  "Initiating reactor ...\0",
  "Scanning stars ...\0",
  "Probing planets ...\0",
  "Training pilots ...\0",
  "Verifying radar ...\0",
  "Pre-flight checks ...\0",
  "Hatching aliens ...\0",
  "Re-charging shields ...\0",
  "Checking wings ...\0",
  "Avoiding asteroids ...\0",
  "Finding stations ...\0"
};

// Local UI components
static UI_COMP *loading_ui_bg = NULL;
static UI_COMP *loading_bar_bg = NULL;
static UI_COMP *loading_bar = NULL;
static UI_COMP *loading_phrase = NULL;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

float get_total_load_state();
int gen_rand_int(int);
void seed_random();
