#include <glad/glad.h>
#include <cglm/cglm.h>
#include <global_vars.h>
#include <engine/engine.h>
#include <structs/camera_str.h>

// ================================ CONSTANTS= ===============================

#define NUM_ALIEN_TYPES (2)
#define NUM_ALIEN_SHIP_TYPES (2)

// ================================= GLOBALS =================================

// Shaders
static unsigned int entity_shader = 0;
static unsigned int model_shader = 0;
static unsigned int ui_shader = 0;
static unsigned int basic_shader = 0;
static unsigned int bone_shader = 0;

// Models
static MODEL *player_model = NULL;
static MODEL *alien_models[NUM_ALIEN_TYPES] = { NULL, NULL };
static MODEL *player_ship_model = NULL;
static MODEL *alien_ship_models[NUM_ALIEN_SHIP_TYPES] = { NULL, NULL };

// Common matrices
static mat4 ortho_proj = GLM_MAT4_IDENTITY_INIT;
static mat4 persp_proj = GLM_MAT4_IDENTITY_INIT;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void get_cam_matrix(CAM *, mat4);
