#include <glad/glad.h>
#include <cglm/cglm.h>
#include <global_vars.h>
#include <engine/engine.h>
#include <structs/camera_str.h>
#include <const.h>
#include <global_vars.h>

// ================================= GLOBALS =================================

// Shaders
static unsigned int entity_shader = 0;
static unsigned int model_shader = 0;
static unsigned int ui_shader = 0;
static unsigned int basic_shader = 0;
static unsigned int bone_shader = 0;
static unsigned int proj_shader = 0;

// Models
static MODEL *player_model = NULL;
static MODEL *alien_models[NUM_ALIEN_TYPES] = { NULL, NULL };
static MODEL *player_ship_model = NULL;
static MODEL *alien_ship_models[NUM_ALIEN_SHIP_TYPES] = { NULL, NULL };
static MODEL *projectile_models[NUM_PROJ_TYPES] = { NULL, NULL };
static MODEL *sphere_model = NULL;
static MODEL *render_sphere_model = NULL;
static MODEL *cube_model = NULL;
static MODEL *four_way_model = NULL;

// Common matrices
static mat4 ortho_proj = GLM_MAT4_IDENTITY_INIT;
static mat4 persp_proj = GLM_MAT4_IDENTITY_INIT;

// Render settings
static int hit_boxes = 0;
static int wire_frame = 0;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void query_render_sim();
void render_enemies();
void render_enemy_ships();
void render_projectiles();
void render_items();
void render_st_obstacles();
void render_sp_obstacles();
void render_game_entity(ENTITY *);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void get_cam_matrix(CAM *, mat4);
