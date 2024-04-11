#include <stdio.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>


// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void handle_physics_collisions(COLLISION *, size_t);
void handle_combat_collisions(COLLISION *, size_t);
void handle_event_collisions(COLLISION *, size_t);

void prepare_object_movement();
void update_object_movement();
//void update_object_movement(int);

void decrement_player_shield(float, float);
void decrement_player_health(float, float);
void decrement_enemy_shield(size_t, float, float);
void decrement_enemy_health(size_t, float, float);

void update_query_spheres();

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void integrate_projectiles();
void start_proj_collision_anim(size_t);
void delete_projectile(size_t);
void projectile_remove_sim(size_t index);

void add_timer(float, void *, int, void *);
void set_coords_warning();
void stop_coords_warning();

void set_gamemode_station();
void set_terminal_ui(int);
void st_enemy_hurt_anim(void *);
void sp_enemy_shield_dmg(void *);
void sp_player_shield_dmg(void *);
void player_health_dmg();

float gen_rand_float_plus_minus(float);
void game_over();
void set_item_prompt(int);

void ship_shield_recharge_delay(void *);
void update_timer_args(void *, void *, void *);
