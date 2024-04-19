#include <cglm/cglm.h>
#include <pthread.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

// Local Structs
typedef struct search_frame {
  size_t cd;
  int depth;
  int searchable;
} SEARCH_FRAME;

typedef struct cell_data {
  size_t prev;
  char visited;
} CELL_DATA;

// Local constants
static const int SEARCH_FLAGS[] = {
  SEARCHABLE_TL,
  SEARCHABLE_T,
  SEARCHABLE_TR,
  SEARCHABLE_L,
  SEARCHABLE_R,
  SEARCHABLE_BL,
  SEARCHABLE_B,
  SEARCHABLE_BR,
};

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void avoid_bounds(vec3, vec3, float, vec3, float *);
void avoid_obstacles(COLLISION *, size_t, SHIP *, vec3, vec3, float, vec3,
                     float *);
void chase_player(vec3, vec3, vec3, float, float, vec3, float *);
void get_shot_target(vec3, vec3, vec3, float, vec3);
void search_st_player(ST_ENEMY *, size_t, size_t *, size_t *);
size_t search_patrol_cd(size_t, vec3);
size_t search_evasion_cd(size_t, size_t);
int check_clear_shot(size_t, size_t);
int double_search_queue(SEARCH_FRAME **, size_t *, size_t *, size_t *);
int can_access(size_t *, size_t);
int gen_searchable_neighbors(size_t *, size_t);
void print_cell_data(CELL_DATA *);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

int add_timer(float, void *, int, void *);
void update_timer_args(void *, void *, void *);
size_t init_projectile(vec3, vec3, float, PROJ_SOURCE, S_WEAPON_T, float,
                       float, size_t);
int projectile_insert_sim(size_t);
void use_power(float, int, SHIP *);
void set_st_enemy_can_shoot(void *);
void st_enemy_shoot_anim(void *);
void st_enemy_swing_anim(void *);
void st_enemy_walk_cycle(void *);
void set_sp_enemy_can_shoot(void *);

void enemy_speak(size_t);
