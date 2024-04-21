#include <ui/main_menu_ui.h>

void init_main_menu_ui() {
  main_menu_ui_fb = framebuffer_init(RES_X, RES_Y);

  main_menu_root = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.0, 0.0 }, 1.0, 1.0,
                               ABSOLUTE_POS | POS_UNIT_RATIO |
                               SIZE_UNIT_RATIO);
  btn_root = add_ui_comp(main_menu_root, (vec2) { 0.75, -0.5 }, 0.15, 0.25,
                         ABSOLUTE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO);
  set_ui_pivot(btn_root, PIVOT_CENTER);
  set_ui_display(btn_root, 0);

  title = add_ui_comp(main_menu_root, (vec2) { 0.5, -0.25 }, 0.5, 0.20,
                      ABSOLUTE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO);
  set_ui_pivot(title, PIVOT_CENTER);
  set_ui_text(title, "VOID SCAVENGER", 0.5, T_CENTER, fixed_sys,
              (vec3) { 1.0, 1.0, 0.0 });
  set_ui_texture(title, "./assets/transparent.png");

  start_btn = init_blue_button(btn_root, (vec2) { 0.0, 0.0 }, 1.0, 0.4,
                               ABSOLUTE_POS | POS_UNIT_RATIO |
                               SIZE_UNIT_RATIO);
  set_ui_text(start_btn, "START GAME", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);

  close_btn = init_blue_button(btn_root, (vec2) { 0.0, -1.0 }, 1.0, 0.4,
                               ABSOLUTE_POS | POS_UNIT_RATIO |
                               SIZE_UNIT_RATIO);
  set_ui_pivot(close_btn, PIVOT_BOTTOM_LEFT);
  set_ui_text(close_btn, "CLOSE GAME", 0.25, T_CENTER, fixed_sys, GLM_VEC3_ONE);

  set_ui_on_click(start_btn, start_game, NULL);
  set_ui_on_click(close_btn, close_game, NULL);
}

void update_main_menu_ui() {
  if (mode == MAIN_MENU) {
    set_ui_enabled(main_menu_root, 1);
    set_ui_texture_unit(main_menu_root, render_main_menu_anim());
  } else {
    set_ui_enabled(main_menu_root, 0);
  }
}

void update_main_menu_fb() {
  framebuffer_delete(main_menu_ui_fb);
  main_menu_ui_fb = framebuffer_init(RES_X, RES_Y);
}

unsigned int render_main_menu_anim() {
  unsigned int model_shader = get_model_shader();
  unsigned int cubemap_shader = get_cubemap_shader();
  unsigned int fire_shader = get_fire_shader();
  unsigned int fire_particles = get_fire_particles();
  MODEL *ship_model = get_player_ship_model();

  mat4 proj = GLM_MAT4_IDENTITY_INIT;
  glm_perspective(glm_rad(45.0), RES_X / RES_Y, 0.1f, 100.0, proj);
  mat4 view = GLM_MAT4_IDENTITY_INIT;
  mat4 model = GLM_MAT4_IDENTITY_INIT;

  glBindFramebuffer(GL_FRAMEBUFFER, main_menu_ui_fb.FBO);
  glClearColor(1.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glUseProgram(cubemap_shader);
  set_mat4("projection", proj, cubemap_shader);
  set_mat4("view", view, cubemap_shader);
  set_mat4("model", model, cubemap_shader);
  render_skybox();

  float t = glfwGetTime();
  float cos_time = cos(t);
  float sin_time = sin(t);

  glm_translate(model, (vec3) { -5.0 + cos_time,
                0.5 * sin(2.0 * t), -20.0 });
  glm_rotate_z(model, -glm_rad(15.0), model);
  glm_rotate_y(model, glm_rad(120.0 + 3.0 * sin_time), model);
  glm_rotate_x(model, glm_rad(5.0 * cos_time), model);

  glUseProgram(model_shader);
  set_mat4("projection", proj, model_shader);
  set_mat4("view", view, model_shader);
  set_mat4("model", model, model_shader);
  draw_model(model_shader, ship_model);

  glUseProgram(fire_shader);
  float particle_scale = 2.5;
  set_float("particle_scale", particle_scale, fire_shader);
  set_float("time", glfwGetTime(), fire_shader);

  mat4 f_model = GLM_MAT4_IDENTITY_INIT;
  mat4 to_thruster = GLM_MAT4_IDENTITY_INIT;

  vec3 positions[] = {
    { 2.78, 0.0, 1.2 },
    { 2.78, 0.0, -1.2 },
    { 2.78, -1.0, 0.93 },
    { 2.78, -1.0, -0.93},
    { -0.15, -0.87, 6.34},
    { -0.15, -0.87, -6.34}
  };

  set_mat4("projection", proj, fire_shader);
  set_mat4("view", view, fire_shader);
  for (int i = 0; i < 6; i++) {
    glm_mat4_identity(to_thruster);
    glBindVertexArray(fire_particles);
    glm_translate(to_thruster, positions[i]);
    glm_rotate_z(to_thruster, glm_rad(-90.0), to_thruster);
    glm_mat4_mul(model, to_thruster, f_model);
    set_mat4("model", f_model, fire_shader);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, NUM_PARTICLES);
  }
  glBindVertexArray(0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  return main_menu_ui_fb.color_texture;
}

void start_game(UI_COMP *comp, void *args) {
  CURSOR_ENABLED = 0;
  enable_fps();
  enable_coordinates();
  pause_audio(MAIN_THEME);
  play_audio(SPACE_THEME);
  generate_sp_enemy_types();
  init_space_mode();
}

void close_game(UI_COMP *comp, void *args) {
  pause_audio(MAIN_THEME);
  quit();
}
