#include <render.h>

/*                                 RENDER.C

  Handles the loading of all assets and shaders, as well as all rendering calls
  for the game. Also handles the major matrix calculations related to rendering
  elements to the screen.

*/


// ======================= INITIALIZATION AND CLEAN UP =======================

int init_scene() {
  // Init shaders below...
  entity_shader = init_shader_prog(shaders_dir "/entity/shader.vs", NULL,
                                   shaders_dir "/entity/shader.fs");
  model_shader = init_shader_prog(shaders_dir "/model/shader.vs", NULL,
                                  shaders_dir "/entity/shader.fs");
  ui_shader = init_shader_prog(shaders_dir "/ui/shader.vs", NULL,
                               shaders_dir "/ui/shader.fs");
  basic_shader = init_shader_prog(shaders_dir "/basic/shader.vs", NULL,
                                  shaders_dir "/basic/shader.fs");
  bone_shader = init_shader_prog(shaders_dir "/bone/shader.vs", NULL,
                                 shaders_dir "/bone/shader.fs");
  proj_shader = init_shader_prog(shaders_dir "/projectile/shader.vs", NULL,
                                 shaders_dir "/projectile/shader.fs");
  glow_entity_shader = init_shader_prog(shaders_dir "/entity/shader.vs", NULL,
                                        shaders_dir "/entity/glow.fs");
  glow_model_shader = init_shader_prog(shaders_dir "/model/shader.vs", NULL,
                                       shaders_dir "/entity/glow.fs");
                                            

  // Init models below...
  player_model = load_model(actors_dir "/player/player.obj");
  alien_models[0] = load_model(actors_dir "/alien_1/alien_1.obj");
  alien_models[1] = load_model(actors_dir "/alien_2/alien_2.obj");
  player_ship_model = load_model(actors_dir "/player_ship/player_ship.obj");
  alien_ship_models[0] = load_model(actors_dir "/alien_ship_1/alien_ship_1.obj");
  projectile_models[0] = load_model(misc_dir "/sp_projectile/sp_projectile.obj");
  projectile_models[1] = load_model(misc_dir "/st_projectile/st_projectile.obj");
  sphere_model = load_model(misc_dir "/sphere/sphere.obj");
  render_sphere_model = load_model(misc_dir "/render_sphere/render_sphere.obj");
  cube_model = load_model(misc_dir "/cube/cube.obj");
  station_model = load_model(setp_dir "/station/station.obj");
  terminal_model = load_model(setp_dir "/terminal/terminal.obj");
  dead_zone_model = load_model(misc_dir "/dead_zone/dead_zone.obj");
  shotgun_model = load_model(setp_dir "/shotgun/shotgun.obj");
  rifle_model = load_model(setp_dir "/rifle/rifle.obj");
  asteroid_models[0] = load_model(setp_dir "/asteroid_1/asteroid_1.obj");
  asteroid_models[1] = load_model(setp_dir "/asteroid_2/asteroid_2.obj");
  asteroid_models[2] = load_model(setp_dir "/asteroid_3/asteroid_3.obj");
  asteroid_models[3] = load_model(setp_dir "/asteroid_4/asteroid_4.obj");
  asteroid_models[4] = load_model(setp_dir "/asteroid_5/asteroid_5.obj");
  corridor_models[0] = load_model(setp_dir "/1_way/1_way.obj");
  corridor_models[1] = load_model(setp_dir "/4_way/4_way_0.obj");
  corridor_models[2] = load_model(setp_dir "/corner/corner_0.obj");
  corridor_models[3] = load_model(setp_dir "/t_junct/t_junct.obj");
  corridor_models[4] = load_model(setp_dir "/corridor/corridor_0.obj");
  station_obstacles[0] = load_model(st_obs_dir "/ammo_crate_0/ammo_crate_0.obj");
  station_obstacles[1] = load_model(st_obs_dir "/ammo_crate_1/ammo_crate_1.obj");
  station_obstacles[2] = load_model(st_obs_dir "/crate_0/crate_0.obj");
  station_obstacles[3] = load_model(st_obs_dir "/crate_1/crate_1.obj");
  station_obstacles[4] = load_model(st_obs_dir "/cryo_bed/cryo_bed.obj");
  station_obstacles[5] = load_model(st_obs_dir "/health_crate_0/health_crate_0.obj");
  station_obstacles[6] = load_model(st_obs_dir "/health_crate_1/health_crate_1.obj");
  station_obstacles[7] = load_model(st_obs_dir "/medical_arms/medical_arms.obj");
  station_obstacles[8] = load_model(st_obs_dir "/oxygen_tank_0/oxygen_tank_0.obj");
  station_obstacles[9] = load_model(st_obs_dir "/plant_vase/plant_vase.obj");
  station_obstacles[10] = load_model(st_obs_dir "/shield_crate_0/shield_crate_0.obj");
  station_obstacles[11] = load_model(st_obs_dir "/shield_crate_1/shield_crate_1.obj");
  station_obstacles[12] = load_model(st_obs_dir "/toilet/toilet.obj");
  station_obstacles[13] = load_model(st_obs_dir "/big_bug/big_bug.obj");
  station_obstacles[14] = load_model(st_obs_dir "/hose_0/hose_0.obj");
  station_obstacles[15] = load_model(st_obs_dir "/hose_1/hose_1.obj");
  station_obstacles[16] = load_model(st_obs_dir "/hose_2/hose_2.obj");
  station_obstacles[17] = load_model(st_obs_dir "/hose_3/hose_3.obj");
  station_obstacles[18] = load_model(st_obs_dir "/stool/stool.obj");
  station_obstacles[19] = load_model(st_obs_dir "/table/table.obj");
  station_ship_parts[0] = load_model(st_ship_parts_dir "/thrusters/thrusters.obj");
  station_ship_parts[1] = load_model(st_ship_parts_dir "/hull/hull.obj");
  station_ship_parts[2] = load_model(st_ship_parts_dir "/reactor/reactor.obj");
  station_ship_parts[3] = load_model(st_ship_parts_dir "/shield/shield.obj");
  station_ship_parts[4] = load_model(st_ship_parts_dir "/weapon/weapon.obj");
  station_ship_parts[5] = load_model(st_ship_parts_dir "/wing/wing.obj");

  if (CHECK_ASSETS_LOADED) {
    fprintf(stderr, "Error: failed to initialize game models\n");
    return -1;
  }

  // Init entities below...
  render_sphere = init_entity(render_sphere_model);
  if (!render_sphere) {
    fprintf(stderr, "Error: failed to initialize game entity\n");
    return -1;
  }
  render_sphere->type |= T_DRIVING;
  render_sphere->velocity[X] = 0.01;

  sim_sphere = init_entity(render_sphere_model);
  if (!sim_sphere) {
    fprintf(stderr, "Error: Failed to initialize game entity\n");
    return -1;
  }
  sim_sphere->type |= T_DRIVING;
  sim_sphere->velocity[X] = 0.01;

  // Initialize common matrices
  glm_ortho(-1.0, 1.0, -1.0, 1.0, 0.0, 100.0, ortho_proj);
  glm_perspective(glm_rad(45.0), RES_X / RES_Y, 0.1f, RENDER_DIST, persp_proj);

  // Initialize OpenGL options
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  CURSOR_ENABLED = 0;

  // Initialize engine UI features
  int status = init_ui("assets/misc/quad/quad.obj", "src/shaders/ui/shader.vs",
                       "src/shaders/ui/shader.fs",
                       "src/shaders/font/shader.vs",
                       "src/shaders/font/shader.fs");
  if (status) {
    return -1;
  }
  glm_vec3_copy((vec3) {0.0, 0.0, 0.0}, camera.pos);
  camera.pitch = 0.0;
  camera.yaw = -90.0;

  return 0;
}

void cleanup_scene() {
  free_model(player_model);
  free_model(alien_models[0]);
  free_model(alien_models[1]);
  free_model(player_ship_model);
  free_model(alien_ship_models[0]);
  for (int i = 0; i < 5; i++) {
    free_model(corridor_models[i]);
    free_model(asteroid_models[i]);
  }
  for (int i = 0; i < NUM_STATION_OBSTACLE_TYPES; i++) {
    free_model(station_obstacles[i]);
  }
  for (int i = 0; i < NUM_STATION_SHIP_PART_TYPES; i++) {
    free_model(station_ship_parts[i]);
  }

  free_ui();
}

// ================================ RENDERING ================================

void render_scene(GLFWwindow *window) {
  if (CURSOR_ENABLED) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  } else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Insert rendering logic below...
  mat4 view = GLM_MAT4_IDENTITY_INIT;
  get_cam_matrix(&camera, view);

  // Toggle for item rarity glowing
  if (item_glow) {
    populate_point_lights(glow_entity_shader);
    populate_point_lights(glow_model_shader);
  }
  unsigned int model_selected_shader =
    item_glow ? glow_model_shader : model_shader;
  unsigned int entity_selected_shader =
    item_glow ? glow_entity_shader : entity_shader;

  glUseProgram(entity_selected_shader);
  set_mat4("projection", persp_proj, entity_selected_shader);
  set_mat4("view", view, entity_selected_shader);
  set_vec3("camera_pos", camera.pos, entity_selected_shader);

  glUseProgram(model_selected_shader);
  set_mat4("projection", persp_proj, model_selected_shader);
  set_mat4("view", view, model_selected_shader);
  set_vec3("camera_pos", camera.pos, model_selected_shader);

  glUseProgram(basic_shader);
  set_mat4("projection", persp_proj, basic_shader);
  set_mat4("view", view, basic_shader);

  glUseProgram(proj_shader);
  set_mat4("projection", persp_proj, proj_shader);
  set_mat4("view", view, proj_shader);

  if (wire_frame) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  if (render_arena) {
    render_oct_tree(physics_sim);
  }
  if (render_bounds) {
    render_dead_zones();
  }
  if (mode == STATION) {
    mat4 gun_mat = GLM_MAT4_IDENTITY_INIT;
    get_player_gun_mat(gun_mat);
    glUseProgram(model_selected_shader);
    set_mat4("model", gun_mat, model_selected_shader);
    draw_model(model_selected_shader, rifle_model);
  }

  render_game_entity(render_sphere);
  render_game_entity(sim_sphere);
  query_render_dist();

  render_ui();

  glfwSwapBuffers(window);
  glfwPollEvents();
}

// ============================== RENDER HELPERS =============================

void query_render_dist() {
  COLLISION *render_query = NULL;
  size_t query_len = get_sim_collisions(render_sim, &render_query,
                                        render_sphere->translation,
                                        SIM_RANGE_INF, 0);
  for (size_t i = 0; i < query_len; i++) {
    if (render_query[i].a_ent == render_sphere ||
        render_query[i].b_ent == render_sphere) {
      if (render_query[i].a_ent != render_sphere &&
          render_query[i].a_ent != sim_sphere) {
        render_game_entity(render_query[i].a_ent);
      } else if (render_query[i].b_ent != render_sphere &&
                 render_query[i].b_ent != sim_sphere) {
        render_game_entity(render_query[i].b_ent);
      }
    }
  }

  free(render_query);
}

void render_game_entity(ENTITY *ent) {
  unsigned int model_selected_shader =
    item_glow ? glow_model_shader : model_shader;
  unsigned int entity_selected_shader =
    item_glow ? glow_entity_shader : entity_shader;
  SOBJ *wrapper = object_wrappers + (size_t) ent->data;
  if (wrapper->type == PROJ_OBJ) {
    if (projectiles[(size_t) wrapper->data].collision) {
      glUseProgram(proj_shader);
      mat4 model = GLM_MAT4_IDENTITY_INIT;
      glm_translate(model, ent->translation);
      glm_quat_rotate(model, ent->rotation, model);
      glm_scale(model, ent->scale);
      set_mat4("model", model, proj_shader);
      draw_model(proj_shader, sphere_model);
    } else {
      draw_entity(proj_shader, ent);
    }
  } else if (wrapper->type == ENEMY_OBJ) {
    ST_ENEMY *enemy = st_enemies + (size_t) wrapper->data;
    glUseProgram(model_selected_shader);
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    if (enemy->max_health > 100.0) {
      get_bone_equip_mat(ent, 14, model);
      set_mat4("model", model, model_selected_shader);
      draw_model(model_selected_shader, shotgun_model);
    } else {
      get_bone_equip_mat(ent, 15, model);
      set_mat4("model", model, model_selected_shader);
      draw_model(model_selected_shader, rifle_model);
    }
    draw_entity(entity_selected_shader, ent);
  } else {
    draw_entity(entity_selected_shader, ent);
  }
  if (hit_boxes) {
    glUseProgram(basic_shader);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    set_vec3("test_col", (vec3) { 1.0, 0.0, 1.0 }, basic_shader);
    draw_colliders(basic_shader, ent, sphere_model);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void render_dead_zones() {
  ENTITY **dead_zones = get_dead_zones();
  if (dead_zones == NULL) {
    return;
  }

  for (int i = 0; i < 6; i++) {
    glUseProgram(basic_shader);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    set_vec3("test_col", (vec3) { 0.0, 1.0, 0.0 }, basic_shader);
    draw_colliders(basic_shader, dead_zones[i], sphere_model);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void render_oct_tree(SIMULATION *sim) {
  unsigned int model_selected_shader =
    item_glow ? glow_model_shader : model_shader;
  glUseProgram(model_selected_shader);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  set_vec3("col", (vec3) { 1.0, 1.0, 0.0 }, model_selected_shader);
  draw_oct_tree(cube_model, sim->oct_tree, (vec3) { 0.0, 0.0, 0.0 },
                sim->oct_tree->max_extent, model_selected_shader, 0, 1);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// ================================= HELPERS =================================

void get_bone_equip_mat(ENTITY *ent, size_t index, mat4 dest) {
  mat4 to_world_space = GLM_MAT4_IDENTITY_INIT;
  glm_translate(to_world_space, ent->translation);
  glm_quat_rotate(to_world_space, ent->rotation, to_world_space);
  glm_scale(to_world_space, ent->scale);

  BONE *bone = NULL;
  mat4 to_entity_space = GLM_MAT4_IDENTITY_INIT;
  bone = ent->model->bones + index;
  glm_mat4_mul(to_world_space, ent->final_b_mats[index], to_world_space);
  glm_translate(to_entity_space, bone->base);

  glm_mat4_mul(to_world_space, to_entity_space, dest);
}

ENTITY *init_player_ent() {
  return init_entity(player_model);
}

ENTITY *init_player_ship_ent() {
  return init_entity(player_ship_model);
}

ENTITY *init_alien_ent(size_t index) {
  return init_entity(alien_models[index]);
}

ENTITY *init_alien_ship_ent(size_t index) {
  return init_entity(alien_ship_models[index]);
}

ENTITY *init_proj_ent(size_t index) {
  return init_entity(projectile_models[index]);
}

ENTITY *init_obstacle_ent(size_t index) {
  return init_entity(asteroid_models[index]);
}

ENTITY *init_station_obstacle_ent(size_t index) {
  return init_entity(station_obstacles[index]);
}

ENTITY *init_corridor_ent(size_t index) {
  return init_entity(corridor_models[index]);
}

ENTITY *init_dead_zone_ent() {
  return init_entity(dead_zone_model);
}

ENTITY *init_station_ent() {
  return init_entity(station_model);
}

ENTITY *init_terminal_ent() {
  return init_entity(terminal_model);
}

ENTITY *init_item_ent(PART_T type) {
  if (type == PART_WEAPON_PLASMA || 
      type == PART_WEAPON_BALLISTIC ||
      type == PART_WEAPON_LASER) {
    return init_entity(station_ship_parts[TYPE_WEAPON]);
  }
  return init_entity(station_ship_parts[type]);
}

void toggle_hit_boxes() {
  hit_boxes = !hit_boxes;
}

void toggle_wire_frame() {
  wire_frame = !wire_frame;
}

void toggle_render_arena() {
  render_arena = !render_arena;
}

void toggle_render_bounds() {
  render_bounds = !render_bounds;
}

void update_perspective() {
  glm_perspective(glm_rad(45.0), RES_X / RES_Y, 0.1f, RENDER_DIST, persp_proj);
}

