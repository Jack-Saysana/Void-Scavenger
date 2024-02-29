#include <ui/target_ui.h>

void init_target_ui() {
  target_ui = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.999, -25.0 }, 0.2, 0.1,
                            ABSOLUTE_POS | POS_X_UNIT_RATIO_X |
                            POS_Y_UNIT_PIXEL | SIZE_UNIT_RATIO_Y);
  set_ui_pivot(target_ui, PIVOT_TOP_RIGHT);
  set_ui_texture(target_ui, "assets/ui/hud_color_20.png");
  set_ui_enabled(target_ui, 1);

  target_header = add_ui_comp(target_ui, (vec2) { 0.05, -0.05 }, 0.9, 0.30,
                              ABSOLUTE_POS | POS_UNIT_RATIO | SIZE_UNIT_RATIO);
  set_ui_text(target_header, "TARGET:", 1.0, T_CENTER, fixed_sys,
              GLM_VEC3_ONE);
  set_ui_texture(target_header, "assets/ui/hud_color_20.png");

  // Target shield stats
  target_shield_root = add_ui_comp(target_ui, (vec2) { 0.05, -0.4 }, 0.9,
                                   0.25, RELATIVE_POS | POS_UNIT_RATIO |
                                   SIZE_UNIT_RATIO);
  set_ui_texture(target_shield_root, "assets/transparent.png");
  target_shield_text = add_ui_comp(target_shield_root, (vec2) { 0.0, 0.0 },
                                   0.24, 1.0, RELATIVE_POS | POS_UNIT_RATIO |
                                   SIZE_UNIT_RATIO);
  set_ui_texture(target_shield_text, "assets/transparent.png");
  set_ui_text(target_shield_text, "SHIELD:", 0.5, T_LEFT, fixed_sys,
              GLM_VEC3_ONE);
  target_shield_bar_bg = add_ui_comp(target_shield_root,
                                     (vec2) { 0.05, -0.1 }, 0.7, 0.8,
                                     RELATIVE_POS | POS_UNIT_RATIO |
                                     SIZE_UNIT_RATIO);
  set_ui_texture(target_shield_bar_bg, "assets/ui/hud_color_20.png");
  target_shield_bar = add_ui_comp(target_shield_bar_bg, (vec2) { 0.0, 0.0 },
                                  0.6, 1.0, RELATIVE_POS | POS_UNIT_RATIO |
                                  SIZE_UNIT_RATIO);
  set_ui_texture(target_shield_bar, "assets/ui/hud_color_50.png");

  // Target health stats
  target_health_root = add_ui_comp(target_ui, (vec2) { 0.05, -0.05 }, 0.9,
                                   0.25, RELATIVE_POS | POS_UNIT_RATIO |
                                   SIZE_UNIT_RATIO);
  set_ui_texture(target_health_root, "assets/transparent.png");
  target_health_text = add_ui_comp(target_health_root, (vec2) { 0.0, 0.0 },
                                   0.24, 1.0, RELATIVE_POS | POS_UNIT_RATIO |
                                   SIZE_UNIT_RATIO);
  set_ui_texture(target_health_text, "assets/transparent.png");
  set_ui_text(target_health_text, "HEALTH:", 0.5, T_LEFT, fixed_sys,
              GLM_VEC3_ONE);
  target_health_bar_bg = add_ui_comp(target_health_root,
                                     (vec2) { 0.05, -0.1 }, 0.7, 0.8,
                                     RELATIVE_POS | POS_UNIT_RATIO |
                                     SIZE_UNIT_RATIO);
  set_ui_texture(target_health_bar_bg, "assets/ui/hud_color_20.png");
  target_health_bar = add_ui_comp(target_health_bar_bg, (vec2) { 0.0, 0.0 },
                                  0.6, 1.0, RELATIVE_POS | POS_UNIT_RATIO |
                                  SIZE_UNIT_RATIO);
  set_ui_texture(target_health_bar, "assets/ui/hud_color_50.png");


  target_waypoint = add_ui_comp(UI_ROOT_COMP, (vec2) { 0.0, 0.0 }, 0.1, 0.1,
                                ABSOLUTE_POS | POS_UNIT_RATIO |
                                SIZE_UNIT_RATIO_Y);
  set_ui_texture(target_waypoint, "assets/ui/target_icon.png");
  set_ui_enabled(target_waypoint, 1);
  set_ui_pivot(target_waypoint, PIVOT_CENTER);
}

void target_nearest_enemy() {
  if (mode != SPACE) {
    return;
  }

  COLLISION *query = NULL;
  size_t query_len = sim_get_nearby(combat_sim, &query,
                                    player_ship.ent->translation,
                                    MAX_TARGET_DIST);
  target_enemy = INVALID_INDEX;
  float min_dist = MAX_TARGET_DIST * MAX_TARGET_DIST;
  float cur_dist = 0.0;

  SOBJ *wrapper = NULL;
  SHIP *enemy = NULL;
  for (size_t i = 0; i < query_len; i++) {
    wrapper = object_wrappers + (size_t) query[i].b_ent->data;
    if (wrapper->type != ENEMY_SHIP_OBJ) {
      continue;
    }

    enemy = sp_enemies + (size_t) wrapper->data;
    cur_dist = glm_vec3_distance2(enemy->ent->translation,
                                  player_ship.ent->translation);
    if (cur_dist < min_dist) {
      min_dist = cur_dist;
      target_enemy = (size_t) wrapper->data;
    }
  }

  if (target_enemy != INVALID_INDEX) {
    set_ui_enabled(target_ui, 1);
    set_ui_enabled(target_waypoint, 1);
  } else {
    set_ui_enabled(target_ui, 0);
    set_ui_enabled(target_waypoint, 0);
  }
}

size_t get_target_ship_index() {
  return target_enemy;
}

void set_target_ship_index(size_t index) {
  target_enemy = index;
  if (index == INVALID_INDEX) {
    set_ui_enabled(target_ui, 0);
    set_ui_enabled(target_waypoint, 0);
  }
}

void update_target_ui() {
  if (mode != SPACE) {
    target_enemy = INVALID_INDEX;
  }
  if (target_enemy == INVALID_INDEX) {
    set_ui_enabled(target_ui, 0);
    set_ui_enabled(target_waypoint, 0);
    return;
  }

  set_ui_width(target_shield_bar, sp_enemies[target_enemy].cur_shield /
               sp_enemies[target_enemy].shield.max_shield);
  set_ui_width(target_health_bar, sp_enemies[target_enemy].cur_health /
               sp_enemies[target_enemy].hull.max_health);

  vec4 screen_space = GLM_VEC4_ZERO_INIT;
  vec4 world_space = GLM_VEC4_ONE_INIT;
  glm_vec3_copy(sp_enemies[target_enemy].ent->translation, world_space);
  to_screen_space(world_space, screen_space);
  screen_space[X] /= screen_space[W];
  screen_space[Y] /= screen_space[W];
  screen_space[X] = (screen_space[X] + 1.0) / 2.0;
  screen_space[Y] = (screen_space[Y] - 1.0) / 2.0;

  // Clamp target so it does not go off screen
  screen_space[X] = fmax(0.0, fmin(screen_space[X], 1.0));
  screen_space[Y] = fmax(-1.0, fmin(screen_space[Y], 0.0));

  // Clamp target to edge of screen if target is behind player
  if (screen_space[Z] < 0.0) {
    if (fmin(screen_space[X], 1.0 - screen_space[X]) <
        fmin(abs(screen_space[Y]), 1.0 - abs(screen_space[Y]))) {
      if (screen_space[X] < 0.5) {
        screen_space[X] = 0.0;
      } else {
        screen_space[X] = 1.0;
      }
    } else {
      if (screen_space[Y] > -0.5) {
        screen_space[Y] = 0.0;
      } else {
        screen_space[Y] = -1.0;
      }
    }
  }

  set_ui_pos(target_waypoint, screen_space);
}
