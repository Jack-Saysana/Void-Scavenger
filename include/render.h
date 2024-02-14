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
static MODEL *asteroid_models[NUM_ASTEROID_TYPES] = { NULL, NULL, NULL, NULL,
                                                      NULL };
static MODEL *corridor_models[NUM_CORRIDOR_TYPES] = { NULL, NULL, NULL, NULL,
                                                      NULL };

// Common matrices
static mat4 ortho_proj = GLM_MAT4_IDENTITY_INIT;
static mat4 persp_proj = GLM_MAT4_IDENTITY_INIT;

// Render settings
static int hit_boxes = 0;
static int wire_frame = 0;

#define CHECK_ASSETS_LOADED (\
!player_model || !alien_models[0] || !alien_models[1] || !player_ship_model || \
!alien_ship_models[0] || !projectile_models[0] || !projectile_models[1] || \
!sphere_model || !render_sphere_model || !cube_model || \
!asteroid_models[0] || !asteroid_models[1] || !asteroid_models[2] || \
!asteroid_models[3] || !asteroid_models[4] || !corridor_models[0] || \
!corridor_models[1] || !corridor_models[2] || !corridor_models[3] || \
!corridor_models[4])

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
void player_ship_thrust_move();
