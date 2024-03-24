#include <pthread.h>
#include <math.h>
#include <string.h>
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <global_vars.h>
#include <engine/engine.h>
#include <structs/camera_str.h>
#include <const.h>
#include <global_vars.h>

// Local structs
typedef struct loaded_model {
  MODEL_DATA *md;
  MODEL *model;
} LOADED_MODEL;

// ================================= GLOBALS =================================

// Shaders
unsigned int cubemap_shader;
unsigned int entity_shader;
unsigned int model_shader;
unsigned int ui_shader;
unsigned int basic_shader;
unsigned int collider_shader;
unsigned int bone_shader;
unsigned int proj_shader;

// Common models
typedef struct common_models {
  LOADED_MODEL sphere_model;
  LOADED_MODEL render_sphere_model;
  LOADED_MODEL cube_model;
  LOADED_MODEL tri_prism_model;
  LOADED_MODEL dead_zone_model;
} COMMON_MODELS;
COMMON_MODELS c_mods;

// Space mode models
typedef struct sp_models {
  LOADED_MODEL asteroid_models[NUM_ASTEROID_TYPES];
  LOADED_MODEL player_ship_model;
  LOADED_MODEL alien_ship_models[NUM_ALIEN_SHIP_TYPES];
  LOADED_MODEL proj_model;
  LOADED_MODEL station_model;
} SP_MODELS;
SP_MODELS sp_mods;

// Station mode models
typedef struct st_models {
  LOADED_MODEL station_obstacles[NUM_STATION_OBSTACLE_TYPES];
  LOADED_MODEL corridor_models[NUM_CORRIDOR_TYPES];
  LOADED_MODEL alien_models[NUM_ALIEN_TYPES];
  LOADED_MODEL player_model;
  LOADED_MODEL proj_model;
  LOADED_MODEL terminal_model;
  LOADED_MODEL rifle_model;
  LOADED_MODEL shotgun_model;
} ST_MODELS;
ST_MODELS st_mods;

// Cubemaps
unsigned int skybox;

// Model loading state info
pthread_mutex_t load_state_lock;
int finished_loading = 0;
int load_error = 0;
size_t num_loaded = 0;

// Common matrices
static mat4 ortho_proj = GLM_MAT4_IDENTITY_INIT;
static mat4 persp_proj = GLM_MAT4_IDENTITY_INIT;

// Render settings
static int hit_boxes = 0;
static int wire_frame = 0;
static int render_arena = 0;
static int render_bounds = 0;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

LOADED_MODEL read_model(char *);
void init_model(LOADED_MODEL *);
void query_render_dist();
void render_game_entity(ENTITY *);
void render_oct_tree(SIMULATION *);
void render_dead_zones();
void get_bone_equip_mat(ENTITY *, size_t, mat4);
void render_skybox();
void render_shield(ENTITY *, float);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void get_cam_matrix(CAM *, mat4);
void player_ship_thrust_move();
ENTITY **get_dead_zones();
void get_player_gun_mat(mat4);
void update_radar_fb();
