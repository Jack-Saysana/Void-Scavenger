#include <player.h>

/*                                  PLAYER.C

  Handles common logic behind manipulating and managing player data. This
  includes movement, inventory management and skill management

*/

// =============================== STATION MODE ==============================

// Initialize player struct at beginning of game
int init_player() {
  memset(&st_player, 0, sizeof(PLAYER));

  // TODO allocate player skills
  // TODO allocate player inventory

  st_player.ent = init_player_ent();
  if (st_player.ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate player entity\n");
    return -1;
  }
  st_player.ent->type |= T_DRIVING;
  st_player.ent->inv_mass = 1.0;

  st_player.max_health = P_BASE_HEALTH;
  st_player.cur_health = P_BASE_HEALTH;
  st_player.speed = P_BASE_SPEED;
  st_player.fire_rate = P_BASE_FIRERATE;
  st_player.max_experience = P_BASE_MAX_EXP;
  st_player.invuln = 0;

  return 0;
}

// De-allocate player resources at end of game
void free_player() {
  free_entity(st_player.ent);
  delete_wrapper(st_player.wrapper_offset);
}

// Insert station mode player into global simulations
int player_insert_sim() {
  int status = sim_add_entity(physics_sim, st_player.ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(combat_sim, st_player.ent, ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, st_player.ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(event_sim, st_player.ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  return 0;
}

void player_remove_sim() {
  sim_remove_entity(physics_sim, st_player.ent);
  sim_remove_entity(combat_sim, st_player.ent);
  sim_remove_entity(event_sim, st_player.ent);
}

void sim_refresh_player() {
  COLLIDER *cur_col = NULL;
  for (size_t i = 0; i < st_player.ent->model->num_colliders; i++) {
    cur_col = st_player.ent->model->colliders + i;
    if (cur_col->category == DEFAULT) {
      refresh_collider(physics_sim, st_player.ent, i);
      refresh_collider(event_sim, st_player.ent, i);
    } else if (cur_col->category == HURT_BOX) {
      refresh_collider(combat_sim, st_player.ent, i);
    }
  }
}

// =============================== SPACE MODE ================================

// Initalize player ship struct at beginning of game
int init_player_ship() {
  memset(&player_ship, 0, sizeof(SHIP));

  player_ship.reactor.max_output = S_BASE_PWR_OUTPUT;
  player_ship.hull.max_health = S_BASE_HEALTH;
  player_ship.shield.max_shield = S_BASE_SHIELD;
  player_ship.shield.recharge_rate = S_BASE_SHIELD_RECHARGE;
  player_ship.shield.recharge_delay = S_BASE_SHIELD_DELAY;
  player_ship.shield.power_draw = S_BASE_PWR_DRAW;
  player_ship.weapon.type = BALLISTIC;
  player_ship.weapon.damage = S_BASE_DAMAGE;
  player_ship.weapon.fire_rate = S_BASE_FIRERATE;
  player_ship.weapon.max_power_draw = S_BASE_PWR_DRAW;
  player_ship.weapon.proj_speed = S_BASE_PROJ_SPEED;
  player_ship.weapon.range = S_BASE_RANGE;
  player_ship.wing.max_ang_vel = S_BASE_ANG_VEL;
  player_ship.wing.max_ang_accel = S_BASE_ANG_ACCEL;
  player_ship.thruster.max_vel = S_BASE_VEL;
  player_ship.thruster.max_accel = S_BASE_ACCEL;
  player_ship.thruster.max_power_draw = S_BASE_PWR_DRAW;

  player_ship.ent = init_player_ship_ent();
  if (player_ship.ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate player ship entity\n");
    return -1;
  }
  player_ship.ent->type |= T_DRIVING;
  player_ship.ent->inv_mass = 1.0;

  player_ship.cur_health = player_ship.hull.max_health;
  player_ship.cur_shield = player_ship.shield.max_shield;
  player_ship.invuln = 0;

  return 0;
}

// De-allocate player ship resources at end of game
void free_player_ship() {
  free_entity(player_ship.ent);
  delete_wrapper(player_ship.wrapper_offset);
}

// Insert space mode player into global simulations
int player_ship_insert_sim() {
  int status = sim_add_entity(physics_sim, player_ship.ent, ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(combat_sim, player_ship.ent, ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, player_ship.ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(event_sim, player_ship.ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  return 0;
}

void player_ship_remove_sim() {
  sim_remove_entity(physics_sim, player_ship.ent);
  sim_remove_entity(combat_sim, player_ship.ent);
  sim_remove_entity(event_sim, player_ship.ent);
}

void sim_refresh_player_ship() {
  COLLIDER *cur_col = NULL;
  for (size_t i = 0; i < player_ship.ent->model->num_colliders; i++) {
    cur_col = player_ship.ent->model->colliders + i;
    if (cur_col->category == DEFAULT) {
      refresh_collider(event_sim, player_ship.ent, i);
    } else if (cur_col->category == HURT_BOX) {
      refresh_collider(physics_sim, player_ship.ent, i);
      refresh_collider(combat_sim, player_ship.ent, i);
    }
  }
}

void player_ship_thrust_move() {
  if (mode == SPACE) {
    vec3 ship_forward;
    glm_quat_rotatev(player_ship.ent->rotation, (vec3){-1.0, 0.0, 0.0},
                     ship_forward);
    glm_normalize(ship_forward);
    glm_vec3_scale(ship_forward, player_ship.cur_speed, ship_forward);
    glm_vec3_copy(ship_forward, player_ship.ent->velocity);
  }
}

// =============================== HELPERS ================================

void get_player_coordinates(vec3 coords) {
  if (mode == SPACE) {
    glm_vec3_copy(player_ship.ent->translation, coords);
  } else {
    glm_vec3_copy(st_player.ent->translation, coords);
  }
}

void get_player_gun_mat(mat4 dest) {
  mat4 to_player_space = GLM_MAT4_IDENTITY_INIT;
  glm_rotate(to_player_space, glm_rad(camera.pitch),
             (vec3) { 0.0, 0.0, 1.0 });
  glm_translate(to_player_space, (vec3) { -0.3, -0.25, 0.0 });
  mat4 temp = GLM_MAT4_IDENTITY_INIT;
  glm_mat4_ins3((mat3) {
    { 0.0, 0.0, 1.0 },
    { -1.0, 0.0, 0.0 },
    { 0.0, -1.0, 0.0 }
  }, temp);
  glm_mat4_transpose(temp);
  glm_mat4_mul(to_player_space, temp, to_player_space);

  glm_mat4_identity(dest);
  glm_translate(dest, camera.pos);
  glm_quat_rotate(dest, st_player.ent->rotation, dest);
  glm_scale(dest, st_player.ent->scale);
  glm_mat4_mul(dest, to_player_space, dest);
}
