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

  // Init models below...
  player_model = load_model("./assets/actors/player/player.obj");
  alien_models[0] = load_model("./assets/actors/alien_1/alien_1.obj");
  alien_models[1] = load_model("./assets/actors/alien_2/alien_2.obj");
  player_ship_model = load_model("./assets/actors/player_ship/player_ship.obj");
  alien_ship_models[0] = load_model("./assets/actors/alien_ship_1/alien_ship_1.obj");
  sphere_model = load_model("./assets/misc/sphere/sphere.obj");
  if (!player_model || !alien_models[0] || !alien_models[1] ||
      !player_ship_model || !alien_ship_models[0] || !sphere_model) {
    fprintf(stderr, "Error: failed to initialize game models\n");
    return -1;
  }

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

  glm_vec3_copy((vec3) {0.0, 0.0, -1.0}, camera.forward);
  glm_vec3_copy((vec3) {0.0, 1.0, 0.0}, camera.up);
  glm_vec3_copy((vec3) {0.0, 0.0, 5.0}, camera.pos);

  return 0;
}

void cleanup_scene() {
  free_model(player_model);
  free_model(alien_models[0]);
  free_model(alien_models[1]);
  free_model(player_ship_model);
  free_model(alien_ship_models[0]);

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

  glUseProgram(basic_shader);
  set_mat4("projection", persp_proj, basic_shader);
  set_mat4("view", view, basic_shader);

  if (wire_frame) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  if (mode == STATION) {
    render_game_entity(st_player.ent);
    render_enemies();
    render_projectiles();
    render_items();
    render_st_obstacles();
  } else if (mode == SPACE) {
    render_game_entity(player_ship.ent);
    render_enemy_ships();
    render_projectiles();
    render_sp_obstacles();
  }

  render_ui();

  glfwSwapBuffers(window);
  glfwPollEvents();
}

// ============================== RENDER HELPERS =============================

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
  draw_entity(entity_shader, ent);
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

ENTITY *init_proj_ent() {
  // TODO create projectile model to instance
  return NULL;
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
