#pragma once
#include <stdio.h>
#include <pthread.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>
/*                              TICK.H

    tick.h houses all tick-based code which is executed on a tick
    basis instead of frame-by-frame

*/

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
void player_ship_thrust_move();
void enemy_behavior();
int delete_stale_objects();
void recharge_player_shield();

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

void add_timer(float, void *, int, void *);

void update_station_player_audio(vec3, versor);
void update_ship_noises();
void update_shield_tone();
void reactor_recharge_player();
