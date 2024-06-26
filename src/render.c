#include <render.h>

/*                                 RENDER.C

  Handles the loading of all assets and shaders, as well as all rendering calls
  for the game. Also handles the major matrix calculations related to rendering
  elements to the screen.

*/


// ======================= INITIALIZATION AND CLEAN UP =======================

// Functions used for loading/initializing assets
#include <load_assets.h>

void clear_models() {
  memset(&c_mods, 0, sizeof(COMMON_MODELS));
  memset(&sp_mods, 0, sizeof(SP_MODELS));
  memset(&st_mods, 0, sizeof(ST_MODELS));
}

int init_scene() {
  // Init shaders below...
  cubemap_shader = init_shader_prog(shaders_dir "/cubemap/shader.vs", NULL,
                                    shaders_dir "/cubemap/shader.fs");
  entity_shader = init_shader_prog(shaders_dir "/entity/shader.vs", NULL,
                                   shaders_dir "/entity/shader.fs");
  model_shader = init_shader_prog(shaders_dir "/model/shader.vs", NULL,
                                  shaders_dir "/entity/shader.fs");
  ui_shader = init_shader_prog(shaders_dir "/ui/shader.vs", NULL,
                               shaders_dir "/ui/shader.fs");
  basic_shader = init_shader_prog(shaders_dir "/model/shader.vs", NULL,
                                  shaders_dir "/basic/shader.fs");
  collider_shader = init_shader_prog(shaders_dir "/basic/shader.vs", NULL,
                                     shaders_dir "/basic/shader.fs");
  bone_shader = init_shader_prog(shaders_dir "/bone/shader.vs", NULL,
                                 shaders_dir "/bone/shader.fs");
  proj_shader = init_shader_prog(shaders_dir "/projectile/shader.vs", NULL,
                                 shaders_dir "/projectile/shader.fs");
  glow_entity_shader = init_shader_prog(shaders_dir "/entity/shader.vs", NULL,
                                        shaders_dir "/entity/glow.fs");
  glow_model_shader = init_shader_prog(shaders_dir "/model/shader.vs", NULL,
                                       shaders_dir "/entity/glow.fs");
  fire_shader = init_shader_prog(shaders_dir "/fire/shader.vs", NULL,
                                 shaders_dir "/fire/shader.fs");

  // Init cubemaps below...
  char *sb_paths[] = {
    "./assets/textures/skybox_right.png",
    "./assets/textures/skybox_left.png",
    "./assets/textures/skybox_up.png",
    "./assets/textures/skybox_down.png",
    "./assets/textures/skybox_front.png",
    "./assets/textures/skybox_back.png"
  };
  char *sb_paths_01[] = {
    "./assets/textures/PolygonSciFiSpace_Skybox_01_Left.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_01_Right.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_01_Down.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_01_Up.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_01_Front.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_01_Back.png"
  };
  char *sb_paths_02[] = {
    "./assets/textures/PolygonSciFiSpace_Skybox_02_Left.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_02_Right.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_02_Down.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_02_Up.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_02_Front.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_02_Back.png"
  };
  char *sb_paths_03[] = {
    "./assets/textures/PolygonSciFiSpace_Skybox_03_Left.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_03_Right.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_03_Down.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_03_Up.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_03_Front.png",
    "./assets/textures/PolygonSciFiSpace_Skybox_03_Back.png"
  };
  gen_cubemap(sb_paths, &skybox);
  gen_cubemap(sb_paths_03, &skybox);
  gen_cubemap(sb_paths_02, &skybox);
  gen_cubemap(sb_paths_01, &skybox);

  // Init models below...
  init_common_assets();
  init_sp_assets();
  init_st_assets();

  // Init entities below...
  render_sphere = init_entity(c_mods.render_sphere_model.model);
  if (!render_sphere) {
    fprintf(stderr, "Error: failed to initialize game entity\n");
    return -1;
  }
  render_sphere->type |= T_DRIVING;
  render_sphere->velocity[X] = 0.01;

  sim_sphere = init_entity(c_mods.render_sphere_model.model);
  if (!sim_sphere) {
    fprintf(stderr, "Error: Failed to initialize game entity\n");
    return -1;
  }
  sim_sphere->type |= T_DRIVING;
  sim_sphere->velocity[X] = 0.01;

  // Initialize common matrices
  glm_ortho(-1.0, 1.0, -1.0, 1.0, 0.0, 100.0, ortho_proj);
  glm_perspective(glm_rad(45.0), RES_X / RES_Y, 0.1f, RENDER_DIST, persp_proj);

  glm_vec3_copy((vec3) {0.0, 0.0, 0.0}, camera.pos);
  camera.pitch = 0.0;
  camera.yaw = -90.0;

  // Initialize particle system for thruster fire
  vec2 particles[NUM_PARTICLES];
  int width = sqrt(NUM_PARTICLES);
  for (int i = 0; i < NUM_PARTICLES; i++) {
    glm_vec2_copy((vec2) { i % width, i / width }, particles[i]);
  }
  float quad_particle[] = {
    -0.0125f,  0.0125f,
     0.0125f, -0.0125f,
    -0.0125f, -0.0125f,
    -0.0125f,  0.0125f,
     0.0125f, -0.0125f,
     0.0125f,  0.0125f
  };
  unsigned int qVBO;
  glGenBuffers(1, &qVBO);
  glGenVertexArrays(1, &fire_particles);
  glBindVertexArray(fire_particles);
  glBindBuffer(GL_ARRAY_BUFFER, qVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad_particle), quad_particle,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                        (void *) 0);
  glEnableVertexAttribArray(0);
  unsigned int iVBO;
  glGenBuffers(1, &iVBO);
  glBindBuffer(GL_ARRAY_BUFFER, iVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                        (void *) 0);
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glVertexAttribDivisor(1, 1);

  return 0;
}

void init_opengl_options() {
  // Enable depth testing and blending
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void cleanup_scene() {
  free_common_assets();
  free_sp_assets();
  free_st_assets();

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

  // Render to main scene
  if (mode == SPACE || mode == STATION) {
    mat4 view = GLM_MAT4_IDENTITY_INIT;
    get_cam_matrix(&camera, view);
    mat4 skybox_view = GLM_MAT4_IDENTITY_INIT;
    glm_mat4_copy(view, skybox_view);
    glm_vec3_zero(skybox_view[3]);

    // Toggle for item rarity glowing
    if (item_glow) {
      populate_point_lights(glow_entity_shader);
      populate_point_lights(glow_model_shader);
    }
    unsigned int model_selected_shader =
      item_glow ? glow_model_shader : model_shader;
    unsigned int entity_selected_shader =
      item_glow ? glow_entity_shader : entity_shader;

    glUseProgram(cubemap_shader);
    set_mat4("projection", persp_proj, cubemap_shader);
    set_mat4("view", skybox_view, cubemap_shader);
    set_vec3("camera_pos", camera.pos, cubemap_shader);

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

    glUseProgram(collider_shader);
    set_mat4("projection", persp_proj, collider_shader);
    set_mat4("view", view, collider_shader);

    glUseProgram(proj_shader);
    set_mat4("projection", persp_proj, proj_shader);
    set_mat4("view", view, proj_shader);

    glUseProgram(fire_shader);
    set_mat4("projection", persp_proj, fire_shader);
    set_mat4("view", view, fire_shader);

    if (wire_frame) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (mode == SPACE) {
      render_skybox();
    }
    if (render_arena) {
      render_oct_tree(combat_sim);
    }
    if (render_bounds) {
      render_dead_zones();
    }
    if (mode == STATION) {
      mat4 gun_mat = GLM_MAT4_IDENTITY_INIT;
      get_player_gun_mat(gun_mat);
      glUseProgram(model_selected_shader);
      set_mat4("model", gun_mat, model_selected_shader);
      draw_model(model_selected_shader, st_mods.rifle_model.model);
    }

    render_game_entity(render_sphere);
    render_game_entity(sim_sphere);
    query_render_dist();
  }

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
    glUseProgram(proj_shader);
    if (projectiles[(size_t) wrapper->data].type == BALLISTIC) {
      set_vec3("col",(vec3){0.98, 0.98, 0.02}, proj_shader);
    } else if ( projectiles[(size_t) wrapper->data].type == PLASMA) {
      set_vec3("col",(vec3){0.0, 0.0, 1.0}, proj_shader);
    } else if ( projectiles[(size_t) wrapper->data].type == LASER) {
      set_vec3("col",(vec3){1.0, 0.0, 0.0}, proj_shader);
    }
    if (projectiles[(size_t) wrapper->data].type != T_MELEE) {
      if (projectiles[(size_t) wrapper->data].collision) {
        mat4 model = GLM_MAT4_IDENTITY_INIT;
        glm_translate(model, ent->translation);
        glm_quat_rotate(model, ent->rotation, model);
        glm_scale(model, ent->scale);
        set_mat4("model", model, proj_shader);
        draw_model(proj_shader, c_mods.sphere_model.model);
      } else {
        draw_entity(proj_shader, ent);
      }
    }
  } else if (wrapper->type == ENEMY_OBJ) {
    ST_ENEMY *enemy = st_enemies + (size_t) wrapper->data;
    glUseProgram(model_selected_shader);
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    if (enemy->max_health > 100.0) {
      get_bone_equip_mat(ent, 14, model);
      set_mat4("model", model, model_selected_shader);
      if (enemy->weapon_type == RANGED) {
        draw_model(model_selected_shader, st_mods.shotgun_model.model);
      } else {
        draw_model(model_selected_shader, st_mods.sword_model.model);
      }
    } else {
      get_bone_equip_mat(ent, 15, model);
      set_mat4("model", model, model_selected_shader);
      if (enemy->weapon_type == RANGED) {
        draw_model(model_selected_shader, st_mods.rifle_model.model);
      } else {
        draw_model(model_selected_shader, st_mods.sword_model.model);
      }
    }
    draw_entity(entity_selected_shader, ent);
  } else if (wrapper->type == ITEM_OBJ) {
    ST_ITEM *part = items + (size_t) wrapper->data;
    glUseProgram(model_selected_shader);
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model, ent->translation);
    glm_quat_rotate(model, ent->rotation, model);
    glm_scale(model, ent->scale);
    set_mat4("model", model, model_selected_shader);
    if (part->type == PART_WEAPON_BALLISTIC ||
        part->type == PART_WEAPON_LASER ||
        part->type == PART_WEAPON_PLASMA) {
      draw_model(model_selected_shader,
                 st_mods.station_ship_parts[TYPE_WEAPON].model);
    } else {
      draw_model(model_selected_shader,
                 st_mods.station_ship_parts[part->type].model);
    }
  } else if (wrapper->type == PLAYER_SHIP_OBJ) {
    draw_entity(entity_selected_shader, ent);

    glUseProgram(fire_shader);
    float particle_scale = 1.0 + (1.5 * player_ship.cur_speed /
                           player_ship.thruster.max_vel);
    set_float("particle_scale", particle_scale, fire_shader);
    set_float("time", glfwGetTime(), fire_shader);

    mat4 f_model = GLM_MAT4_IDENTITY_INIT;
    mat4 to_ship = GLM_MAT4_IDENTITY_INIT;
    mat4 to_thruster = GLM_MAT4_IDENTITY_INIT;

    glm_translate(to_ship, player_ship.ent->translation);
    glm_quat_rotate(to_ship, player_ship.ent->rotation, to_ship);

    vec3 positions[] = {
      { 2.78, 0.0, 1.2 },
      { 2.78, 0.0, -1.2 },
      { 2.78, -1.0, 0.93 },
      { 2.78, -1.0, -0.93},
      { -0.15, -0.87, 6.34},
      { -0.15, -0.87, -6.34}
    };

    for (int i = 0; i < 6; i++) {
      glm_mat4_identity(to_thruster);
      glBindVertexArray(fire_particles);
      glm_translate(to_thruster, positions[i]);
      glm_rotate_z(to_thruster, glm_rad(-90.0), to_thruster);
      glm_mat4_mul(to_ship, to_thruster, f_model);
      set_mat4("model", f_model, fire_shader);
      glDrawArraysInstanced(GL_TRIANGLES, 0, 6, NUM_PARTICLES);
    }
    glBindVertexArray(0);
  } else if (wrapper->type == ENEMY_SHIP_OBJ) {
    draw_entity(entity_selected_shader, ent);

    SHIP *enemy = sp_enemies + (size_t) wrapper->data;
    glUseProgram(fire_shader);
    float particle_scale = 1.0 + (enemy->cur_speed / enemy->thruster.max_vel);
    set_float("time", glfwGetTime(), fire_shader);

    mat4 f_model = GLM_MAT4_IDENTITY_INIT;
    mat4 to_ship = GLM_MAT4_IDENTITY_INIT;
    mat4 to_thruster = GLM_MAT4_IDENTITY_INIT;

    glm_translate(to_ship, enemy->ent->translation);
    glm_quat_rotate(to_ship, enemy->ent->rotation, to_ship);

    vec4 positions[4];
    int num_used = 4;
    if (enemy->ent->model == sp_mods.alien_ship_models[0].model) {
      glm_vec4_copy((vec4) { 9.89, 0.0, 6.38, 2.0 }, positions[0]);
      glm_vec4_copy((vec4) { 9.89, 0.0, -6.38, 2.0 }, positions[1]);
      glm_vec4_copy((vec4) { 8.84, 0.0, 8.80 , 2.0 }, positions[2]);
      glm_vec4_copy((vec4) { 8.84, 0.0, -8.80, 2.0 }, positions[3]);
    } else if (enemy->ent->model == sp_mods.alien_ship_models[1].model) {
      glm_vec4_copy((vec4) { 2.77, 0.42, 1.26, 1.0 }, positions[0]);
      glm_vec4_copy((vec4) { 2.77, 0.42, -1.26, 1.0 }, positions[1]);
      glm_vec4_copy((vec4) { 4.75, 0.50, 0.0, 2.0 }, positions[2]);
      glm_vec4_copy((vec4) { 5.22, -0.71, 0.0, 2.0 }, positions[3]);
    } else if (enemy->ent->model == sp_mods.alien_ship_models[2].model) {
      glm_vec4_copy((vec4) { 7.94, 0.0, 4.09, 1.0 }, positions[0]);
      glm_vec4_copy((vec4) { 7.94, 0.0, -4.09, 1.0 }, positions[1]);
      glm_vec4_copy((vec4) { 7.94, 0.0, 0.0, 3.0 }, positions[2]);
      num_used = 3;
    }

    for (int i = 0; i < num_used; i++) {
      glm_mat4_identity(to_thruster);
      glBindVertexArray(fire_particles);
      glm_translate(to_thruster, positions[i]);
      glm_rotate_z(to_thruster, glm_rad(-90.0), to_thruster);
      glm_mat4_mul(to_ship, to_thruster, f_model);
      set_mat4("model", f_model, fire_shader);
      set_float("particle_scale", positions[i][W] * particle_scale,
                fire_shader);
      glDrawArraysInstanced(GL_TRIANGLES, 0, 6, NUM_PARTICLES);
    }
    glBindVertexArray(0);
  } else {
    draw_entity(entity_selected_shader, ent);
  }
  if (wrapper->type == ENEMY_SHIP_OBJ) {
    SHIP *enemy = sp_enemies + (size_t) wrapper->data;
    if (enemy->render_shield > 0.0) {
      render_shield(ent, enemy->render_shield);
    }
  } else if (wrapper->type == PLAYER_SHIP_OBJ) {
    if (player_ship.render_shield > 0.0) {
      render_shield(ent, player_ship.render_shield);
    }
  }
  if (hit_boxes) {
    glUseProgram(collider_shader);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    set_vec4("col", (vec4) { 1.0, 0.0, 1.0, 1.0 }, collider_shader);
    draw_colliders(collider_shader, ent, c_mods.sphere_model.model);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void render_skybox() {
  glDepthMask(GL_FALSE);
  glUseProgram(cubemap_shader);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
  set_mat4("model", GLM_MAT4_IDENTITY, cubemap_shader);
  set_int("cube_map", 0, cubemap_shader);
  draw_model(cubemap_shader, c_mods.cube_model.model);
  glDepthMask(GL_TRUE);
}

void render_shield(ENTITY *ent, float shield_state) {
  MODEL *shield_model = ent->model;
  mat4 model = GLM_MAT4_IDENTITY_INIT;
  glm_translate(model, ent->translation);
  glm_quat_rotate(model, ent->rotation, model);
  glm_scale(model, ent->scale);
  glm_scale(model, (vec3) { 1.1, 1.1, 1.1 });

  glUseProgram(basic_shader);
  set_mat4("model", model, basic_shader);
  set_vec4("col", (vec4) { 0.0, 1.0, 1.0, 0.1 * sin(shield_state * M_PI) },
           basic_shader);
  draw_model(basic_shader, shield_model);
}

void render_dead_zones() {
  ENTITY **dead_zones = get_dead_zones();
  if (dead_zones == NULL) {
    return;
  }

  for (int i = 0; i < 6; i++) {
    glUseProgram(collider_shader);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    set_vec4("col", (vec4) { 0.0, 1.0, 0.0, 1.0 }, collider_shader);
    draw_colliders(collider_shader, dead_zones[i], c_mods.sphere_model.model);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void render_oct_tree(SIMULATION *sim) {
  glUseProgram(basic_shader);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  set_vec4("col", (vec4) { 1.0, 1.0, 0.0, 1.0 }, basic_shader);
  draw_oct_tree(c_mods.cube_model.model, sim->oct_tree,
                (vec3) { 0.0, 0.0, 0.0 }, sim->oct_tree->max_extent,
                basic_shader, 0, 1);
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

inline LOADED_MODEL read_model(char *path) {
  LOADED_MODEL ret;
  ret.md = load_model_data(path);
  ret.model = NULL;

  pthread_mutex_lock(&load_state_lock);
  num_loaded++;
  pthread_mutex_unlock(&load_state_lock);
  return ret;
}

inline void init_model(LOADED_MODEL *mod) {
  mod->model = gen_model(mod->md);
  free(mod->md->vertices);
  free(mod->md->indices);
  free(mod->md);
}

ENTITY *init_player_ent() {
  return init_entity(st_mods.player_model.model);
}

ENTITY *init_player_ship_ent() {
  return init_entity(sp_mods.player_ship_model.model);
}

ENTITY *init_alien_ent(size_t index) {
  return init_entity(st_mods.alien_models[index].model);
}

ENTITY *init_alien_ship_ent(size_t index) {
  return init_entity(sp_mods.alien_ship_models[index].model);
}

ENTITY *init_proj_ent(size_t index) {
  if (index) {
    return init_entity(st_mods.proj_model.model);
  } else {
    return init_entity(sp_mods.proj_model.model);
  }
}

ENTITY *init_obstacle_ent(size_t index) {
  return init_entity(sp_mods.asteroid_models[index].model);
}

ENTITY *init_station_obstacle_ent(size_t index) {
  return init_entity(st_mods.station_obstacles[index].model);
}

ENTITY *init_corridor_ent(size_t index) {
  return init_entity(st_mods.corridor_models[index].model);
}

ENTITY *init_dead_zone_ent() {
  return init_entity(c_mods.dead_zone_model.model);
}

ENTITY *init_station_ent() {
  return init_entity(sp_mods.station_model.model);
}

ENTITY *init_terminal_ent() {
  return init_entity(st_mods.terminal_model.model);
}

ENTITY *init_item_ent(PART_T type) {
  if (type == PART_WEAPON_PLASMA ||
      type == PART_WEAPON_BALLISTIC ||
      type == PART_WEAPON_LASER) {
    return init_entity(st_mods.station_ship_parts[TYPE_WEAPON].model);
  }
  return init_entity(st_mods.station_ship_parts[type].model);
}

MODEL *get_sphere_model() {
  return c_mods.sphere_model.model;
}

MODEL *get_tri_prism_model() {
  return c_mods.tri_prism_model.model;
}

MODEL *get_player_ship_model() {
  return sp_mods.player_ship_model.model;
}

unsigned int get_fire_particles() {
  return fire_particles;
}

unsigned int get_basic_shader() {
  return basic_shader;
}

unsigned int get_model_shader() {
  return model_shader;
}

unsigned int get_cubemap_shader() {
  return cubemap_shader;
}

unsigned int get_fire_shader() {
  return fire_shader;
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

  update_radar_fb();
  update_main_menu_fb();
}

void to_screen_space(vec4 pos, vec4 dest) {
  mat4 view = GLM_MAT4_IDENTITY_INIT;
  get_cam_matrix(&camera, view);
  glm_mat4_mulv(view, pos, dest);
  glm_mat4_mulv(persp_proj, dest, dest);
}

int get_finished_loading() {
  pthread_mutex_lock(&load_state_lock);
  int ret = finished_loading;
  pthread_mutex_unlock(&load_state_lock);
  return ret;
}

float get_total_load_state() {
  pthread_mutex_lock(&load_state_lock);
  float progress = num_loaded;
  pthread_mutex_unlock(&load_state_lock);
  float num_cmn = (float) sizeof(c_mods) / (float) sizeof(LOADED_MODEL);
  float num_sp = (float) sizeof(sp_mods) / (float) sizeof(LOADED_MODEL);
  float num_st = (float) sizeof(st_mods) / (float) sizeof(LOADED_MODEL);
  return progress / (num_cmn + num_sp + num_st);
}

void reset_load_state() {
  pthread_mutex_lock(&load_state_lock);
  finished_loading = 0;
  load_error = 0;
  num_loaded = 0;
  pthread_mutex_unlock(&load_state_lock);
}

int get_enemy_type(size_t index) {
  if (mode == STATION) {
    if (st_enemies[index].ent->model == st_mods.alien_models[BRUTE].model) {
      return BRUTE;
    } else {
      return NORMAL;
    }
  }
  return -1;
}
