#include <render.h>

/*                                 RENDER.C

  Handles the loading of all assets and shaders, as well as all rendering calls
  for the game. Also handles the major matrix calculations related to rendering
  elements to the screen.

*/


// ======================= INITIALIZATION AND CLEAN UP =======================

int init_scene() {
  // Init shaders below...
  entity_shader = init_shader_prog("./src/shaders/entity/shader.vs", NULL,
                                   "./src/shaders/entity/shader.fs");
  model_shader = init_shader_prog("./src/shaders/model/shader.vs", NULL,
                                  "./src/shaders/model/shader.fs");
  ui_shader = init_shader_prog("./src/shaders/ui/shader.vs", NULL,
                               "./src/shaders/ui/shader.fs");
  basic_shader = init_shader_prog("./src/shaders/basic/shader.vs", NULL,
                                  "./src/shaders/basic/shader.fs");
  bone_shader = init_shader_prog("./src/shaders/bone/shader.vs", NULL,
                                 "./src/shaders/bone/shader.fs");
  proj_shader = init_shader_prog("./src/shaders/projectile/shader.vs", NULL,
                                 "./src/shaders/projectile/shader.fs");

  // Init models below...
  player_model = load_model("./assets/actors/player/player.obj");
  alien_models[0] = load_model("./assets/actors/alien_1/alien_1.obj");
  alien_models[1] = load_model("./assets/actors/alien_2/alien_2.obj");
  player_ship_model = load_model("./assets/actors/player_ship/player_ship.obj");
  alien_ship_models[0] = load_model("./assets/actors/alien_ship_1/alien_ship_1.obj");
  projectile_models[0] = load_model("./assets/misc/sp_projectile/sp_projectile.obj");
  projectile_models[1] = load_model("./assets/misc/st_projectile/st_projectile.obj");
  sphere_model = load_model("./assets/misc/sphere/sphere.obj");
  render_sphere_model = load_model("./assets/misc/render_sphere/render_sphere.obj");
  cube_model = load_model("./assets/misc/cube/cube.obj");
  asteroid_models[0] = load_model("./assets/set_pieces/asteroid_1/asteroid_1.obj");
  asteroid_models[1] = load_model("./assets/set_pieces/asteroid_2/asteroid_2.obj");
  asteroid_models[2] = load_model("./assets/set_pieces/asteroid_3/asteroid_3.obj");
  asteroid_models[3] = load_model("./assets/set_pieces/asteroid_4/asteroid_4.obj");
  asteroid_models[4] = load_model("./assets/set_pieces/asteroid_5/asteroid_5.obj");
  corridor_models[0] = load_model("./assets/set_pieces/1_way/1_way.obj");
  corridor_models[1] = load_model("./assets/set_pieces/4_way/4_way_0.obj");
  corridor_models[2] = load_model("./assets/set_pieces/corner/corner_0.obj");
  corridor_models[3] = load_model("./assets/set_pieces/t_junct/t_junct.obj");
  corridor_models[4] = load_model("./assets/set_pieces/corridor/corridor_0.obj");

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
  glm_vec3_copy((vec3) { RENDER_DIST, RENDER_DIST, RENDER_DIST },
                render_sphere->scale);
  render_sphere->velocity[X] = 0.01;

  // Initialize common matrices
  glm_ortho(-1.0, 1.0, -1.0, 1.0, 0.0, 100.0, ortho_proj);
  glm_perspective(glm_rad(45.0), RES_X / RES_Y, 0.1f, 100.0f, persp_proj);

  // Initialize OpenGL options
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Initialize engine UI features
  int status = init_ui("assets/misc/quad/quad.obj", "src/shaders/ui/shader.vs",
                       "src/shaders/ui/shader.fs",
                       "src/shaders/font/shader.vs",
                       "src/shaders/font/shader.fs");
  if (status) {
    return -1;
  }
  
  glm_vec3_copy((vec3) {0.0, 0.0, 5.0}, camera.pos);
  camera.pitch = 0.0;
  camera.yaw = 0.0;

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

  glUseProgram(entity_shader);
  set_mat4("projection", persp_proj, entity_shader);
  set_mat4("view", view, entity_shader);
  set_vec3("camera_pos", camera.pos, entity_shader);

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

  if (mode == STATION) {
    render_game_entity(st_player.ent);
    render_game_entity(render_sphere);
    /*
    render_enemies();
    render_projectiles();
    render_items();
    render_st_obstacles();
    */
    query_render_sim();
  } else if (mode == SPACE) {
    //render_game_entity(player_ship.ent);
    render_enemy_ships();
    render_projectiles();
    render_sp_obstacles();
  }

  render_ui();

  glfwSwapBuffers(window);
  glfwPollEvents();
}

// ============================== RENDER HELPERS =============================

void query_render_sim() {
  COLLISION *render_query = NULL;
  size_t query_len = get_sim_collisions(render_sim, &render_query);
  for (size_t i = 0; i < query_len; i++) {
    if (render_query[i].a_ent == render_sphere ||
        render_query[i].b_ent == render_sphere) {
      if (render_query[i].a_ent != render_sphere) {
        render_game_entity(render_query[i].a_ent);
      } else if (render_query[i].b_ent != render_sphere) {
        render_game_entity(render_query[i].b_ent);
      }
    }
  }
  free(render_query);
}

void render_enemies() {
  for (size_t i = 0; i < num_enemies; i++) {
    render_game_entity(st_enemies[i].ent);
  }
}

void render_enemy_ships() {
  for (size_t i = 0; i < num_enemies; i++) {
    render_game_entity(sp_enemies[i].ent);
  }
}

void render_projectiles() {
  for (size_t i = 0; i < num_projectiles; i++) {
    render_game_entity(projectiles[i].ent);
  }
}

void render_items() {
  for (size_t i = 0; i < num_items; i++) {
    render_game_entity(items[i].ent);
  }
}

void render_st_obstacles() {
  for(size_t i = 0; i < num_obstacles; i++) {
    render_game_entity(st_obs[i].ent);
  }
}

void render_sp_obstacles() {
  for(size_t i = 0; i < num_obstacles; i++) {
    render_game_entity(sp_obs[i].ent);
  }
}

void render_game_entity(ENTITY *ent) {
  SOBJ *wrapper = object_wrappers + (size_t) ent->data;
  if (wrapper->type == PROJ_OBJ) {
    draw_entity(proj_shader, ent);
  } else {
    draw_entity(entity_shader, ent);
  }
  if (hit_boxes) {
    glUseProgram(basic_shader);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    set_vec3("test_col", (vec3) { 1.0, 0.0, 1.0 }, basic_shader);
    draw_colliders(basic_shader, ent, sphere_model);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

// ================================= HELPERS =================================

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

ENTITY *init_corridor_ent(size_t index) {
  return init_entity(corridor_models[index]);
}

void toggle_hit_boxes() {
  hit_boxes = !hit_boxes;
}

void toggle_wire_frame() {
  wire_frame = !wire_frame;
}

void update_perspective() {  
  glm_perspective(glm_rad(45.0), RES_X / RES_Y, 0.1f, 100.0f, persp_proj);
}
