#include <tick.h>

void tick() {
  if (mode != SPACE && mode != STATION) {
    return;
  }

  /* Combat and Event Collision Detection */
  #if 1
  COLLISION *combat_collisions = NULL;
  size_t num_c_col = get_sim_collisions(combat_sim, &combat_collisions,
                                        sim_sphere->translation,
                                        SIM_DIST, 0);
  prepare_object_movement();
  handle_combat_collisions(combat_collisions, num_c_col);
  update_object_movement();

  COLLISION *event_collisions = NULL;
  size_t num_e_col = get_sim_collisions(event_sim, &event_collisions,
                                        sim_sphere->translation,
                                        SIM_DIST, 0);
  handle_event_collisions(event_collisions, num_e_col);

  free(combat_collisions);
  free(event_collisions); 

#endif
  enemy_behavior();
  player_ship_thrust_move();
  recharge_player_shield();
  delete_stale_objects();

  add_timer(TICK_RATE, tick, FUNCTION_PTR, NULL);
}
