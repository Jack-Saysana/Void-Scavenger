/*
                              LOAD_ASSETS.H

  **IMPORTATNT**: THIS FILE SHOULD ONLY BE INCLUDED IN RENDER.H

  Load and initialize game assets here. Assets are broken into 3 main
  categories:

  - common: Assets used across both station and space mode

  - space: Assets used in only space mode

  - station: Assets used only in station mode

  In order to add an asset to game, you must first add a member of the
  resective asset struct in "render.h".

  Secondly, in the respective load_*_assets() function, use the read_model()
  function to load the asset file data into memory.

  Thirdly, in the respective init_*_assets() function, use the init_model()
  function to initialize the model in OpenGL.

  Fourthly, in the respective free_*_assets() function, use the free_model()
  function to free the data upon application close.
*/

void load_common_assets() {
  c_mods.sphere_model = read_model("./assets/misc/sphere/sphere.obj");
  c_mods.render_sphere_model = read_model("./assets/misc/render_sphere/render_sphere.obj");
  c_mods.cube_model = read_model("./assets/misc/cube/cube.obj");
  c_mods.tri_prism_model = read_model("./assets/misc/tri_prism/tri_prism.obj");
  c_mods.dead_zone_model = read_model("./assets/misc/dead_zone/dead_zone.obj");
}
void init_common_assets() {
  init_model(&c_mods.sphere_model);
  init_model(&c_mods.render_sphere_model);
  init_model(&c_mods.cube_model);
  init_model(&c_mods.tri_prism_model);
  init_model(&c_mods.dead_zone_model);
}
void free_common_assets() {
  free_model(c_mods.sphere_model.model);
  free_model(c_mods.render_sphere_model.model);
  free_model(c_mods.cube_model.model);
  free_model(c_mods.tri_prism_model.model);
  free_model(c_mods.dead_zone_model.model);
}

void load_sp_assets() {
  sp_mods.player_ship_model = read_model("./assets/actors/player_ship/player_ship.obj");
  sp_mods.alien_ship_models[0] = read_model("./assets/actors/alien_ship_1/alien_ship_1.obj");
  sp_mods.alien_ship_models[1] = read_model("./assets/actors/alien_ship_2/alien_ship_2.obj");
  sp_mods.alien_ship_models[2] = read_model("./assets/actors/alien_ship_3/alien_ship_3.obj");
  sp_mods.proj_model = read_model("./assets/misc/sp_projectile/sp_projectile.obj");
  sp_mods.station_model = read_model("./assets/set_pieces/station/station.obj");
  sp_mods.asteroid_models[0] = read_model("./assets/set_pieces/asteroid_1/asteroid_1.obj");
  sp_mods.asteroid_models[1] = read_model("./assets/set_pieces/asteroid_2/asteroid_2.obj");
  sp_mods.asteroid_models[2] = read_model("./assets/set_pieces/asteroid_3/asteroid_3.obj");
  sp_mods.asteroid_models[3] = read_model("./assets/set_pieces/asteroid_4/asteroid_4.obj");
  sp_mods.asteroid_models[4] = read_model("./assets/set_pieces/asteroid_5/asteroid_5.obj");
}
void init_sp_assets() {
  init_model(&sp_mods.player_ship_model);
  init_model(&sp_mods.alien_ship_models[0]);
  init_model(&sp_mods.proj_model);
  init_model(&sp_mods.station_model);
  for (size_t i = 0; i < NUM_ASTEROID_TYPES; i++) {
    init_model(&sp_mods.asteroid_models[i]);
  }
}
void free_sp_assets() {
  free_model(sp_mods.player_ship_model.model);
  free_model(sp_mods.alien_ship_models[0].model);
  free_model(sp_mods.proj_model.model);
  free_model(sp_mods.station_model.model);
  for (size_t i = 0; i < NUM_ASTEROID_TYPES; i++) {
    free_model(sp_mods.asteroid_models[i].model);
  }
}

void load_st_assets() {
  st_mods.player_model = read_model("./assets/actors/player/player.obj");
  st_mods.alien_models[0] = read_model("./assets/actors/alien_1/alien_1.obj");
  st_mods.alien_models[1] = read_model("./assets/actors/alien_2/alien_2.obj");
  st_mods.proj_model = read_model("./assets/misc/st_projectile/st_projectile.obj");
  st_mods.terminal_model = read_model("./assets/set_pieces/terminal/terminal.obj");
  st_mods.shotgun_model = read_model("./assets/set_pieces/shotgun/shotgun.obj");
  st_mods.rifle_model = read_model("./assets/set_pieces/rifle/rifle.obj");
  st_mods.corridor_models[0] = read_model("./assets/set_pieces/1_way/1_way.obj");
  st_mods.corridor_models[1] = read_model("./assets/set_pieces/4_way/4_way_0.obj");
  st_mods.corridor_models[2] = read_model("./assets/set_pieces/corner/corner_0.obj");
  st_mods.corridor_models[3] = read_model("./assets/set_pieces/t_junct/t_junct.obj");
  st_mods.corridor_models[4] = read_model("./assets/set_pieces/corridor/corridor_0.obj");
  st_mods.station_obstacles[0] = read_model("./assets/station_obstacles/ammo_crate_0/ammo_crate_0.obj");
  st_mods.station_obstacles[1] = read_model("./assets/station_obstacles/ammo_crate_1/ammo_crate_1.obj");
  st_mods.station_obstacles[2] = read_model("./assets/station_obstacles/crate_0/crate_0.obj");
  st_mods.station_obstacles[3] = read_model("./assets/station_obstacles/crate_1/crate_1.obj");
  st_mods.station_obstacles[4] = read_model("./assets/station_obstacles/cryo_bed/cryo_bed.obj");
  st_mods.station_obstacles[5] = read_model("./assets/station_obstacles/health_crate_0/health_crate_0.obj");
  st_mods.station_obstacles[6] = read_model("./assets/station_obstacles/health_crate_1/health_crate_1.obj");
  st_mods.station_obstacles[7] = read_model("./assets/station_obstacles/medical_arms/medical_arms.obj");
  st_mods.station_obstacles[8] = read_model("./assets/station_obstacles/oxygen_tank_0/oxygen_tank_0.obj");
  st_mods.station_obstacles[9] = read_model("./assets/station_obstacles/plant_vase/plant_vase.obj");
  st_mods.station_obstacles[10] = read_model("./assets/station_obstacles/shield_crate_0/shield_crate_0.obj");
  st_mods.station_obstacles[11] = read_model("./assets/station_obstacles/shield_crate_1/shield_crate_1.obj");
  st_mods.station_obstacles[12] = read_model("./assets/station_obstacles/toilet/toilet.obj");
  st_mods.station_obstacles[13] = read_model("./assets/station_obstacles/big_bug/big_bug.obj");
  st_mods.station_obstacles[14] = read_model("./assets/station_obstacles/hose_0/hose_0.obj");
  st_mods.station_obstacles[15] = read_model("./assets/station_obstacles/hose_1/hose_1.obj");
  st_mods.station_obstacles[16] = read_model("./assets/station_obstacles/hose_2/hose_2.obj");
  st_mods.station_obstacles[17] = read_model("./assets/station_obstacles/hose_3/hose_3.obj");
  st_mods.station_obstacles[18] = read_model("./assets/station_obstacles/stool/stool.obj");
  st_mods.station_obstacles[19] = read_model("./assets/station_obstacles/table/table.obj");
}
void init_st_assets() {
  init_model(&st_mods.player_model);
  init_model(&st_mods.alien_models[0]);
  init_model(&st_mods.alien_models[1]);
  init_model(&st_mods.proj_model);
  init_model(&st_mods.terminal_model);
  init_model(&st_mods.shotgun_model);
  init_model(&st_mods.rifle_model);
  for (size_t i = 0; i < NUM_CORRIDOR_TYPES; i++) {
    init_model(&st_mods.corridor_models[i]);
  }
  for (size_t i = 0; i < NUM_STATION_OBSTACLE_TYPES; i++) {
    init_model(&st_mods.station_obstacles[i]);
  }
}
void free_st_assets() {
  free_model(st_mods.player_model.model);
  free_model(st_mods.alien_models[0].model);
  free_model(st_mods.alien_models[1].model);
  free_model(st_mods.proj_model.model);
  free_model(st_mods.terminal_model.model);
  free_model(st_mods.shotgun_model.model);
  free_model(st_mods.rifle_model.model);
  for (size_t i = 0; i < NUM_CORRIDOR_TYPES; i++) {
    free_model(st_mods.corridor_models[i].model);
  }
  for (size_t i = 0; i < NUM_STATION_OBSTACLE_TYPES; i++) {
    free_model(st_mods.station_obstacles[i].model);
  }
}

void *load_assets(void *arg) {
  load_error = 0;

  load_common_assets();
  load_sp_assets();
  load_st_assets();

  pthread_mutex_lock(&load_state_lock);
  finished_loading = 1;
  pthread_mutex_unlock(&load_state_lock);
  if (load_error) {
    fprintf(stderr, "Error: failed to load game assets\n");
    return (void *) -1;
  }

  return 0;
}

