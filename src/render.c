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
  if (!player_model || !alien_models[0] || !alien_models[1] ||
      !player_ship_model || !alien_ship_models[0]) {
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
  int status = init_ui("assets/quad/quad.obj", "src/shaders/ui/shader.vs",
                       "src/shaders/ui/shader.fs",
                       "src/shaders/font/shader.vs",
                       "src/shaders/font/shader.fs");
  if (status) {
    return -1;
  }

  glm_vec3_copy((vec3) {0.0, 0.0, -1.0}, camera.forward);
  glm_vec3_copy((vec3) {0.0, 1.0, 0.0}, camera.up);
  glm_vec3_copy((vec3) {0.5, 0.0, 0.0}, camera.pos);

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
  glClearColor(1.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Insert rendering logic below...
  render_ui();

  glfwSwapBuffers(window);
  glfwPollEvents();
}

// ================================= HELPERS =================================

void update_perspective() {
  glm_perspective(glm_rad(45.0), RES_X / RES_Y, 0.1f, 100.0f, persp_proj);
}
