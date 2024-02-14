#ifndef __ENGINE_SIMULATION_H__
#define __ENGINE_SIMULATION_H__

#include "./simulation_str.h"
#include "./entity_str.h"

SIMULATION *init_sim(float max_extent, unsigned int max_depth);
void free_sim(SIMULATION *sim);

int sim_add_entity(SIMULATION *sim, ENTITY *entity, int collider_filter);
int sim_remove_entity(SIMULATION *sim, ENTITY *entity);
void sim_add_force(SIMULATION *sim, vec3 force);
void sim_clear_force(SIMULATION* sim);
void integrate_sim(SIMULATION *sim);
size_t get_sim_collisions(SIMULATION *sim, COLLISION **dest);
void impulse_resolution(SIMULATION *sim, COLLISION col);
void refresh_collider(SIMULATION *sim, ENTITY *entity, size_t collider_offset);

void draw_oct_tree(MODEL *cube, OCT_TREE *tree, vec3 pos, float scale,
                   unsigned int shader, size_t offset, int depth);
#endif
