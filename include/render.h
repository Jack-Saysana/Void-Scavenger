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
static unsigned int collider_shader = 0;
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
static MODEL *tri_prism_model = NULL;
static MODEL *asteroid_models[NUM_ASTEROID_TYPES] = { NULL, NULL, NULL, NULL,
                                                      NULL };
static MODEL *corridor_models[NUM_CORRIDOR_TYPES] = { NULL, NULL, NULL, NULL,
                                                      NULL };
static MODEL *station_model = NULL;
static MODEL *terminal_model = NULL;
static MODEL *dead_zone_model = NULL;
static MODEL *rifle_model = NULL;
static MODEL *shotgun_model = NULL;
static MODEL *station_obstacles[NUM_STATION_OBSTACLE_TYPES] = {
  NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL,
};

// Common matrices
static mat4 ortho_proj = GLM_MAT4_IDENTITY_INIT;
static mat4 persp_proj = GLM_MAT4_IDENTITY_INIT;

// Render settings
static int hit_boxes = 0;
static int wire_frame = 0;
static int render_arena = 0;
static int render_bounds = 0;

#define CHECK_ASSETS_LOADED (\
!player_model || !alien_models[0] || !alien_models[1] || !player_ship_model || \
!alien_ship_models[0] || !projectile_models[0] || !projectile_models[1] || \
!sphere_model || !render_sphere_model || !cube_model || !tri_prism_model || \
!station_model || !terminal_model || !rifle_model || !shotgun_model || \
!asteroid_models[0] || !asteroid_models[1] || !asteroid_models[2] || \
!asteroid_models[3] || !asteroid_models[4] || !corridor_models[0] || \
!corridor_models[1] || !corridor_models[2] || !corridor_models[3] || \
!corridor_models[4] || !dead_zone_model || \
!station_obstacles[0] || !station_obstacles[1] || !station_obstacles[2] || \
!station_obstacles[3] || !station_obstacles[4] || !station_obstacles[5] || \
!station_obstacles[6] || !station_obstacles[7] || !station_obstacles[8] || \
!station_obstacles[9] || !station_obstacles[10] || !station_obstacles[11] || \
!station_obstacles[12] || !station_obstacles[13] || !station_obstacles[14] || \
!station_obstacles[15] || !station_obstacles[16] || !station_obstacles[17] || \
!station_obstacles[18] || !station_obstacles[19] \
)

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void query_render_dist();
void render_game_entity(ENTITY *);
void render_oct_tree(SIMULATION *);
void render_dead_zones();
void get_bone_equip_mat(ENTITY *, size_t, mat4);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void get_cam_matrix(CAM *, mat4);
void player_ship_thrust_move();
ENTITY **get_dead_zones();
void get_player_gun_mat(mat4);
void update_radar_fb();
