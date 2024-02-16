#include <stdio.h>
#include <engine/engine.h>
#include <global_vars.h>

// ======================= INTERNALLY DEFINED FUNCTIONS ======================



// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

void sim_refresh_player();
void sim_refresh_player_ship();
void sim_refresh_st_enemy(size_t);
void sim_refresh_sp_enemy(size_t);
void sim_refresh_st_obstacle(size_t);
void sim_refresh_sp_obstacle(size_t);
void sim_refresh_proj(size_t);
void sim_refresh_corridor(size_t);
