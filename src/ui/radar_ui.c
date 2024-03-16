#include <ui/radar_ui.h>

void init_radar_ui() {
  radar_ui_fb = framebuffer_init(RES_X, RES_Y);

  radar_ui = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.5, -0.875 }, 0.25, 0.25,
                         ABSOLUTE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO_Y);
  set_ui_pivot(radar_ui, PIVOT_CENTER);
}

void update_radar_ui() {
  set_ui_texture_unit(radar_ui, render_radar_ui());
}

void update_radar_fb() {
  framebuffer_delete(radar_ui_fb);
  radar_ui_fb = framebuffer_init(RES_X, RES_Y);
}

unsigned int render_radar_ui() {
  unsigned int basic_shader = get_basic_shader();
  MODEL *sphere_model = get_sphere_model();
  MODEL *tri_prism_model = get_tri_prism_model();

  glBindFramebuffer(GL_FRAMEBUFFER, radar_ui_fb.FBO);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(5.0);
  glUseProgram(basic_shader);
  set_vec3("col", (vec3) { 0.0, 0.0, 1.0 }, basic_shader);

  mat4 proj = GLM_MAT4_IDENTITY_INIT;
  glm_perspective(glm_rad(45.0), 1.0, 0.1f, 100.0, proj);

  mat4 view = GLM_MAT4_IDENTITY_INIT;
  glm_translate(view, (vec3) { 0.0, 0.0, -0.75 });

  // Draw radar sphere

  mat4 model = GLM_MAT4_IDENTITY_INIT;
  mat4 rot = GLM_MAT4_IDENTITY_INIT;
  glm_quat_rotatev(player_ship.ent->rotation, (vec3) { 0.0, 0.0, -1.0 },
                   rot[0]);
  glm_quat_rotatev(player_ship.ent->rotation, (vec3) { 0.0, 1.0, 0.0 },
                   rot[1]);
  glm_quat_rotatev(player_ship.ent->rotation, (vec3) { 1.0, 0.0, 0.0 },
                   rot[2]);
  glm_mat4_transpose(rot);
  glm_mat4_copy(rot, model);
  glm_scale(model, (vec3) { 0.25, 0.25, 0.25 });

  set_mat4("projection", proj, basic_shader);
  set_mat4("view", view, basic_shader);
  set_mat4("model", model, basic_shader);

  draw_model(basic_shader, sphere_model);

  glLineWidth(1.0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // Draw nearby entity "blips"

  glm_mat4_identity(model);
  glm_mat4_copy(rot, model);
  mat4 temp = GLM_MAT4_IDENTITY_INIT;
  vec3 e_pos = GLM_VEC3_ZERO_INIT;

  COLLISION *cols = NULL;
  size_t num_cols = sim_get_nearby(combat_sim, &cols,
                                   player_ship.ent->translation,
                                   SEARCH_RADIUS);

  SOBJ *wrapper = NULL;
  for (size_t i = 0; i < num_cols; i++) {
    wrapper = object_wrappers + (size_t) cols[i].b_ent->data;
    if (wrapper->type == ENEMY_SHIP_OBJ) {
      set_vec3("col", (vec3) { 1.0, 0.0, 0.0 }, basic_shader);
    } else if (wrapper->type == OBSTACLE_OBJ) {
      set_vec3("col", (vec3) { 0.0, 1.0, 0.0 }, basic_shader);
    } else {
      continue;
    }

    glm_vec3_sub(cols[i].b_ent->translation, player_ship.ent->translation,
                 e_pos);
    if (glm_vec3_norm(e_pos) > SEARCH_RADIUS) {
      continue;
    }

    glm_vec3_scale(e_pos, 1.0 / SEARCH_RADIUS, e_pos);
    glm_mat4_identity(temp);
    glm_scale(temp, (vec3) { 0.25, 0.25, 0.25 });
    glm_translate(temp, e_pos);
    glm_scale(temp, (vec3) { 0.05, 0.05, 0.05 });
    glm_mat4_mul(model, temp, temp);

    set_mat4("model", temp, basic_shader);

    draw_model(basic_shader, tri_prism_model);
  }
  free(cols);

  // Draw player "blip"

  set_vec3("col", (vec3) { 0.0, 1.0, 1.0 }, basic_shader);
  glm_mat4_identity(model);
  glm_scale(model, (vec3) { 0.01, 0.01, 0.01 });
  set_mat4("model", model, basic_shader);
  draw_model(basic_shader, tri_prism_model);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  return radar_ui_fb.color_texture;
}
