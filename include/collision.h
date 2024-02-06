#include <engine/engine.h>
#include <global_vars.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void handle_physics_collisions(COLLISION *, size_t);
void handle_combat_collisions(COLLISION *, size_t);
void handle_event_collisions(COLLISION *, size_t);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void integrate_projectiles();
void delete_projectile(size_t);
void projectile_remove_sim(size_t index);
