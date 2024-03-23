#include <pthread.h>
#include <GLFW/glfw3.h>
#include <global_vars.h>

// Static globals
static pthread_t loading_thread;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void reset_load_state();
int get_finished_loading();
void *load_assets(void *);
int init_game();
void init_loading_ui();
