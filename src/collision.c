#include <collision.h>

/*                                COLLISION.C

  Queries and handles all collision events in both the space and station mode
  simulations. Handles physical, combat-based and trigger-based collisions.

*/

void handle_collisions() {
  // Update simulations
  integrate_sim(physics_sim);

  COLLISION *physics_collisions = NULL;
  /*size_t num_p_col = */get_sim_collisions(physics_sim, &physics_collisions);

  COLLISION *combat_collisions = NULL;
  /*size_t num_c_col = */get_sim_collisions(combat_sim, &combat_collisions);

  COLLISION *event_collisions = NULL;
  /*size_t num_e_col = */get_sim_collisions(event_sim, &event_collisions);

  // Check collisions

  free(physics_collisions);
  free(combat_collisions);
  free(event_collisions);
}
