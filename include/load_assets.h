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

#define st_obs_dir "./assets/station_obstacles"
#define misc_dir "./assets/misc"
#define actors_dir "./assets/actors"
#define setp_dir "./assets/set_pieces"
#define st_ship_parts_dir "./assets/station_ship_parts"
#define shaders_dir "./src/shaders"
#define audio_dir "./assets/audio"

void load_common_assets() {
  c_mods.sphere_model = read_model(misc_dir"/sphere/sphere.obj");
  c_mods.render_sphere_model = read_model(misc_dir"/render_sphere/render_sphere.obj");
  c_mods.cube_model = read_model(misc_dir"/cube/cube.obj");
  c_mods.tri_prism_model = read_model(misc_dir"/tri_prism/tri_prism.obj");
  c_mods.dead_zone_model = read_model(misc_dir"/dead_zone/dead_zone.obj");
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
  sp_mods.player_ship_model = read_model(actors_dir"/player_ship/player_ship.obj");
  sp_mods.alien_ship_models[0] = read_model(actors_dir"/alien_ship_1/alien_ship_1.obj");
  sp_mods.alien_ship_models[1] = read_model(actors_dir"/alien_ship_2/alien_ship_2.obj");
  sp_mods.alien_ship_models[2] = read_model(actors_dir"/alien_ship_3/alien_ship_3.obj");
  sp_mods.proj_model = read_model(misc_dir"/sp_projectile/sp_projectile.obj");
  sp_mods.station_model = read_model(setp_dir"/station/station.obj");
  sp_mods.asteroid_models[0] = read_model(setp_dir"/asteroid_1/asteroid_1.obj");
  sp_mods.asteroid_models[1] = read_model(setp_dir"/asteroid_2/asteroid_2.obj");
  sp_mods.asteroid_models[2] = read_model(setp_dir"/asteroid_3/asteroid_3.obj");
  sp_mods.asteroid_models[3] = read_model(setp_dir"/asteroid_4/asteroid_4.obj");
  sp_mods.asteroid_models[4] = read_model(setp_dir"/asteroid_5/asteroid_5.obj");
}
void init_sp_assets() {
  init_model(&sp_mods.player_ship_model);
  init_model(&sp_mods.proj_model);
  init_model(&sp_mods.station_model);
  for (size_t i = 0; i < NUM_ASTEROID_TYPES; i++) {
    init_model(&sp_mods.asteroid_models[i]);
  }
  for (size_t i = 0; i < NUM_ALIEN_SHIP_TYPES; i++) {
    init_model(&sp_mods.alien_ship_models[i]);
  }
}
void free_sp_assets() {
  free_model(sp_mods.player_ship_model.model);
  free_model(sp_mods.proj_model.model);
  free_model(sp_mods.station_model.model);
  for (size_t i = 0; i < NUM_ASTEROID_TYPES; i++) {
    free_model(sp_mods.asteroid_models[i].model);
  }
  for (size_t i = 0; i < NUM_ALIEN_SHIP_TYPES; i++) {
    free_model(sp_mods.alien_ship_models[i].model);
  }
}

void load_st_assets() {
  st_mods.player_model = read_model(actors_dir"/player/player.obj");
  st_mods.alien_models[0] = read_model(actors_dir"/alien_1/alien_1.obj");
  st_mods.alien_models[1] = read_model(actors_dir"/alien_2/alien_2.obj");
  st_mods.proj_model = read_model(misc_dir"/st_projectile/st_projectile.obj");
  st_mods.terminal_model = read_model(setp_dir"/terminal/terminal.obj");
  st_mods.shotgun_model = read_model(setp_dir"/shotgun/shotgun.obj");
  st_mods.rifle_model = read_model(setp_dir"/rifle/rifle.obj");
  st_mods.sword_model = read_model(setp_dir"/sword/sword.obj");
  st_mods.corridor_models[0] = read_model(setp_dir"/1_way/1_way.obj");
  st_mods.corridor_models[1] = read_model(setp_dir"/4_way/4_way_0.obj");
  st_mods.corridor_models[2] = read_model(setp_dir"/corner/corner_0.obj");
  st_mods.corridor_models[3] = read_model(setp_dir"/t_junct/t_junct.obj");
  st_mods.corridor_models[4] = read_model(setp_dir"/corridor/corridor_0.obj");
  st_mods.station_obstacles[0] = read_model(st_obs_dir"/ammo_crate_0/ammo_crate_0.obj");
  st_mods.station_obstacles[1] = read_model(st_obs_dir"/ammo_crate_1/ammo_crate_1.obj");
  st_mods.station_obstacles[2] = read_model(st_obs_dir"/crate_0/crate_0.obj");
  st_mods.station_obstacles[3] = read_model(st_obs_dir"/crate_1/crate_1.obj");
  st_mods.station_obstacles[4] = read_model(st_obs_dir"/cryo_bed/cryo_bed.obj");
  st_mods.station_obstacles[5] = read_model(st_obs_dir"/health_crate_0/health_crate_0.obj");
  st_mods.station_obstacles[6] = read_model(st_obs_dir"/health_crate_1/health_crate_1.obj");
  st_mods.station_obstacles[7] = read_model(st_obs_dir"/medical_arms/medical_arms.obj");
  st_mods.station_obstacles[8] = read_model(st_obs_dir"/oxygen_tank_0/oxygen_tank_0.obj");
  st_mods.station_obstacles[9] = read_model(st_obs_dir"/plant_vase/plant_vase.obj");
  st_mods.station_obstacles[10] = read_model(st_obs_dir"/shield_crate_0/shield_crate_0.obj");
  st_mods.station_obstacles[11] = read_model(st_obs_dir"/shield_crate_1/shield_crate_1.obj");
  st_mods.station_obstacles[12] = read_model(st_obs_dir"/toilet/toilet.obj");
  st_mods.station_obstacles[13] = read_model(st_obs_dir"/big_bug/big_bug.obj");
  st_mods.station_obstacles[14] = read_model(st_obs_dir"/hose_0/hose_0.obj");
  st_mods.station_obstacles[15] = read_model(st_obs_dir"/hose_1/hose_1.obj");
  st_mods.station_obstacles[16] = read_model(st_obs_dir"/hose_2/hose_2.obj");
  st_mods.station_obstacles[17] = read_model(st_obs_dir"/hose_3/hose_3.obj");
  st_mods.station_obstacles[18] = read_model(st_obs_dir"/stool/stool.obj");
  st_mods.station_obstacles[19] = read_model(st_obs_dir"/table/table.obj");
  st_mods.station_ship_parts[0] = read_model(st_ship_parts_dir "/thrusters/thrusters.obj");
  st_mods.station_ship_parts[1] = read_model(st_ship_parts_dir "/hull/hull.obj");
  st_mods.station_ship_parts[2] = read_model(st_ship_parts_dir "/reactor/reactor.obj");
  st_mods.station_ship_parts[3] = read_model(st_ship_parts_dir "/shield/shield.obj");
  st_mods.station_ship_parts[4] = read_model(st_ship_parts_dir "/weapon/weapon.obj");
  st_mods.station_ship_parts[5] = read_model(st_ship_parts_dir "/wing/wing.obj");
}
void init_st_assets() {
  init_model(&st_mods.player_model);
  init_model(&st_mods.alien_models[0]);
  init_model(&st_mods.alien_models[1]);
  init_model(&st_mods.proj_model);
  init_model(&st_mods.terminal_model);
  init_model(&st_mods.shotgun_model);
  init_model(&st_mods.rifle_model);
  init_model(&st_mods.sword_model);
  for (size_t i = 0; i < NUM_CORRIDOR_TYPES; i++) {
    init_model(&st_mods.corridor_models[i]);
  }
  for (size_t i = 0; i < NUM_STATION_OBSTACLE_TYPES; i++) {
    init_model(&st_mods.station_obstacles[i]);
  }
  for (size_t i = 0; i < NUM_STATION_SHIP_PART_TYPES; i++) {
    init_model(&st_mods.station_ship_parts[i]);
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
  free_model(st_mods.sword_model.model);
  for (size_t i = 0; i < NUM_CORRIDOR_TYPES; i++) {
    free_model(st_mods.corridor_models[i].model);
  }
  for (size_t i = 0; i < NUM_STATION_OBSTACLE_TYPES; i++) {
    free_model(st_mods.station_obstacles[i].model);
  }
  for (size_t i = 0; i < NUM_STATION_SHIP_PART_TYPES; i++) {
    free_model(st_mods.station_ship_parts[i].model);
  }
}

void load_audio_tracks() {
  add_audio(audio_dir"/ballistic_spaceship_gun.wav");
  add_audio(audio_dir"/laser_spaceship_gun.wav");
  add_audio(audio_dir"/plasma_spaceship_gun.wav");
  add_audio(audio_dir"/station_mode_weapon.wav");
  add_audio(audio_dir"/spaceship_explosion.wav");
  add_audio(audio_dir"/shield_station_mode_hit.wav");
  add_audio(audio_dir"/spaceship_hull_hit.wav");
  add_audio(audio_dir"/world_exit.wav");
  add_audio(audio_dir"/player_death_1.wav");
  add_audio(audio_dir"/player_death_2.wav");
  add_audio(audio_dir"/player_hurt_1.wav");
  add_audio(audio_dir"/player_hurt_2.wav");
  add_audio(audio_dir"/player_hurt_3.wav");
  add_audio(audio_dir"/player_hurt_4.wav");
  add_audio(audio_dir"/alien_normal_talking.wav");
  add_audio(audio_dir"/alien_normal_death.wav");
  add_audio(audio_dir"/alien_brute_talking.wav");
  add_audio(audio_dir"/alien_brute_death.wav");
  add_audio(audio_dir"/StarWars60.wav");
  generate_ship_noises();
}

void *load_assets(void *arg) {
  load_error = 0;

  load_common_assets();
  load_sp_assets();
  load_st_assets();
  load_audio_tracks();

  pthread_mutex_lock(&load_state_lock);
  finished_loading = 1;
  pthread_mutex_unlock(&load_state_lock);
  if (load_error) {
    fprintf(stderr, "Error: failed to load game assets\n");
    return (void *) -1;
  }

  return 0;
}


