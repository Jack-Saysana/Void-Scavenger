#include <stdio.h>
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

// Static variables
static float SEARCH_RADIUS = 100.0;

// Framebuffer
static FRAMEBUFFER radar_ui_fb;

// Local UI components
static UI_COMP *radar_ui = NULL;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

unsigned int render_radar_ui();

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

unsigned int render_radar_ui();
unsigned int get_basic_shader();
MODEL *get_sphere_model();
MODEL *get_tri_prism_model();
