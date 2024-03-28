#include <stdio.h>
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

// Local Constants
#define OFF   (0)
#define WHITE (1)
#define RED   (2)
#define WARNING_TIME (0.15)
#define WARNING_THRESHOLD (30.0)

// Static variables
static float SEARCH_RADIUS = 100.0;
static int warning_state = OFF;

// Framebuffer
static FRAMEBUFFER radar_ui_fb;

// Local UI components
static UI_COMP *radar_ui = NULL;
static UI_COMP *radar_warning = NULL;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

unsigned int render_radar_ui();
void update_radar_warning(void *);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

unsigned int render_radar_ui();
unsigned int get_basic_shader();
MODEL *get_sphere_model();
MODEL *get_tri_prism_model();
void add_timer(float, void *, int, void *);
