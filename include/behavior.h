#include <cglm/cglm.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

// Local Structs
typedef struct search_frame {
  size_t cd;
  size_t prev;
  int depth;
} SEARCH_FRAME;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void avoid_bounds(vec3, vec3, float, vec3, float *);
void chase_player(vec3, vec3, float, vec3, float *);
void get_shot_target(vec3, vec3, vec3, float, vec3);
void search_st_player(ST_ENEMY *, size_t, size_t *, size_t *);
size_t search_patrol_cd(size_t, vec3);
size_t search_evasion_cd(size_t, size_t);
int check_clear_shot(size_t, size_t);
int double_search_queue(SEARCH_FRAME **, size_t *, size_t *, size_t *);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

int add_timer(float, void *, int, void *);
void update_timer_args(void *, void *, void *);
void st_enemy_walk_cycle(void *);
size_t init_projectile(vec3, vec3, float, PROJ_SOURCE, S_WEAPON_T, float,
                       float, size_t);
int projectile_insert_sim(size_t);
