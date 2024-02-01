#include <engine/engine.h>
#include <global_vars.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void handle_physics_collisions();
void handle_combat_collisions();

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void integrate_projectiles();
void delete_projectile(size_t);
void projectile_remove_sim(size_t index);
