#pragma once
#include <global_vars.h>
#include <const.h>
#include <stdio.h>
#include <string.h>

#define NOT_WEAPON (8008135)
#define BALLISTIC  (0)
#define LASER      (1)
#define PLASMA     (2)

extern size_t i_size;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================
I_SLOT *inv_first_avail();

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
size_t sim_get_nearby(SIMULATION *sim, COLLISION **dest, vec3 pos, float range);
