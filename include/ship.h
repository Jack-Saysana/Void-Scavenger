#include <stdio.h>
#include <pthread.h>
#include <engine/engine.h>
#include <global_vars.h>
#include <const.h>
#include <cglm/cglm.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void use_power(float, int, SHIP *);
void stall_ship(SHIP *);
void destall_ship(SHIP *);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

size_t init_projectile(vec3, vec3, float, PROJ_SOURCE, S_WEAPON_T, float,
                       float, size_t);
int projectile_insert_sim(size_t);
void add_timer(float, void *, int, void *);
void update_timer_memory(void *, void *);
void enable_stallwarning();
void disable_stallwarning();
void start_stallwarning();
void end_stallwarning();
void reset_stallwarning();