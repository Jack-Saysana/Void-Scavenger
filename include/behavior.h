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

void search_st_player(ST_ENEMY *, size_t, size_t *, size_t *);
size_t search_patrol_cd(size_t, vec3);
size_t search_evasion_cd(size_t, size_t);
int check_clear_shot(size_t, size_t);
int double_search_queue(SEARCH_FRAME **, size_t *, size_t *, size_t *);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

int add_timer(float, void *, int, void *);
void update_timer_args(void *, void *, void *);
void st_enemy_walk_cycle(void *);
