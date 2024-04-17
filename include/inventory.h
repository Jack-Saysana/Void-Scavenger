#pragma once
#include <pthread.h>
#include <global_vars.h>
#include <const.h>
#include <stdio.h>
#include <string.h>


extern size_t i_size;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================
I_SLOT *inv_first_avail();
void drop_item(size_t inv_slot);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
size_t sim_get_nearby(SIMULATION *sim, COLLISION **dest, vec3 pos, float range);
size_t restore_item(size_t);
int item_insert_sim(size_t);
