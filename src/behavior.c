#include <behavior.h>

/*                              BEHAVIOR.C

  Implements the specific pathfinding functions for NPCs in both space and
  station mode.

*/

// =============================== SPACE MODE ================================

void sp_enemy_pathfind(size_t index) {
  SHIP *enemy = sp_enemies + index;
  vec3 e_pos = GLM_VEC3_ZERO_INIT;
  glm_vec3_copy(enemy->ent->translation, e_pos);
  vec3 player_forward = GLM_VEC3_ZERO_INIT;
  glm_quat_rotatev(enemy->ent->rotation, (vec3) { -1.0, 0.0, 0.0 },
                   player_forward);

  vec3 forward = { -1.0, 0.0, 0.0 };
  glm_quat_rotatev(enemy->ent->rotation, forward, forward);
  vec3 up = { 0.0, 1.0, 0.0 };
  glm_quat_rotatev(enemy->ent->rotation, up, up);
  vec3 side = GLM_VEC3_ZERO_INIT;
  glm_vec3_cross(forward, up, side);
  glm_vec3_normalize(side);

  //float stop_time = -enemy->thruster.max_vel / -enemy->thruster.max_accel;
  //float stop_dist = (enemy->thruster.max_vel * stop_time) +
  //                  (0.5 * enemy->thruster.max_accel *
  //                   enemy->thruster.max_accel * stop_time);
  float stop_time = -enemy->cur_speed / -enemy->thruster.max_accel;
  float stop_dist = (enemy->cur_speed * stop_time) +
                    (0.5 * enemy->thruster.max_accel *
                     enemy->thruster.max_accel * stop_time);
  float turning_rad = 50.0 + stop_dist;

  vec3 target_dir = GLM_VEC3_ZERO_INIT;
  float target_speed = enemy->thruster.max_vel;

  // Steer ship away from arena edges
  vec3 ab_dir = GLM_VEC3_ZERO_INIT;
  float ab_speed = enemy->thruster.max_vel;
  avoid_bounds(e_pos, forward, turning_rad, ab_dir, &ab_speed);
  // Take into account priority of avoiding bounds
  glm_vec3_scale(ab_dir, SP_AVOID_BOUNDS_PRIORITY, ab_dir);
  glm_vec3_add(ab_dir, target_dir, target_dir);

  // Steer ship away from nearby obstacles
  vec3 ao_dir = GLM_VEC3_ZERO_INIT;
  float ao_speed = enemy->thruster.max_vel;
  COLLISION *nearby = NULL;
  size_t num_nearby = sim_get_nearby(render_sim, &nearby,
                                     enemy->ent->translation, stop_dist);
  avoid_obstacles(nearby, num_nearby, enemy, e_pos, forward, stop_dist, ao_dir,
                  &ao_speed);
  free(nearby);
  // Take into account priority of avoiding obstacles
  glm_vec3_scale(ao_dir, SP_AVOID_OBSTACLE_PRIORITY, ao_dir);
  glm_vec3_add(ao_dir, target_dir, target_dir);

  // Chase the player
  vec3 p_dir = GLM_VEC3_ZERO_INIT;
  float p_speed = enemy->thruster.max_vel;
  chase_player(e_pos, forward, player_forward, stop_dist,
               enemy->weapon.proj_speed + enemy->cur_speed, p_dir, &p_speed);
  // Take into account priority of chasing player
  glm_vec3_scale(p_dir, SP_CHASE_PRIORITY, p_dir);
  glm_vec3_add(p_dir, target_dir, target_dir);

  // Calculate overall target direction and speed
  glm_vec3_normalize(target_dir);
  if (target_dir[X] || target_dir[Y] || target_dir[Z]) {
    target_speed = enemy->thruster.max_vel;
    if (ab_dir[X] || ab_dir[Y] || ab_dir[Z]) {
      target_speed = fmin(target_speed, ab_speed);
    }
    if (ao_dir[X] || ao_dir[Y] || ao_dir[Z]) {
      target_speed = fmin(target_speed, ao_speed);
    }
    if (p_dir[X] || p_dir[Y] || p_dir[Z]) {
      target_speed = fmin(target_speed, p_speed);
    }
  }

  float player_alignment = glm_vec3_dot(forward, p_dir);
  vec3 temp = GLM_VEC3_ZERO_INIT;

  if (target_dir[X] || target_dir[Y] || target_dir[Z]) {
    // Goal: Steer ship using linear combination of pitch roll and yaw to
    // ensure that the ship's forward vector matches its target vector, and
    // the forward, target and up vectors are coplanar. This will create a
    // "realistic" looking turning style

    // Pitch
    float pitch_alignment = glm_vec3_dot(target_dir, up);
    float cur_pitch = glm_vec3_dot(side, enemy->ent->ang_velocity);
    float target_pitch = 0.0;
    if (pitch_alignment < 0.0) {
      target_pitch = -enemy->wing.max_ang_vel * fabs(pitch_alignment);
    } else if (pitch_alignment > 0.0) {
      target_pitch = enemy->wing.max_ang_vel * fabs(pitch_alignment);
    }
    if (cur_pitch > target_pitch) {
      glm_vec3_scale_as(side, -enemy->wing.max_ang_accel * DELTA_TIME, temp);
    } else if (cur_pitch < target_pitch) {
      glm_vec3_scale_as(side, enemy->wing.max_ang_accel * DELTA_TIME, temp);
    }
    glm_vec3_add(temp, enemy->ent->ang_velocity, enemy->ent->ang_velocity);

    // Roll
    // Three vectors a, b and c are coplanar if (a * (b x c)) == 0
    glm_vec3_cross(forward, up, temp);
    float roll_alignment = glm_vec3_dot(target_dir, temp);
    float cur_roll = glm_vec3_dot(forward, enemy->ent->ang_velocity);
    float target_roll = 0.0;
    if (roll_alignment < 0.0) {
      target_roll = enemy->wing.max_ang_vel * fabs(roll_alignment);
    } else if (roll_alignment > 0.0) {
      target_roll = -enemy->wing.max_ang_vel * fabs(roll_alignment);
    }
    if (cur_roll > target_roll) {
      glm_vec3_scale_as(forward, -enemy->wing.max_ang_accel * DELTA_TIME,
                        temp);
    } else if (cur_roll < target_roll) {
      glm_vec3_scale_as(forward, enemy->wing.max_ang_accel * DELTA_TIME, temp);
    }
    glm_vec3_add(temp, enemy->ent->ang_velocity, enemy->ent->ang_velocity);

    // Yaw
    float yaw_alignment = glm_vec3_dot(target_dir, side);
    float cur_yaw = glm_vec3_dot(up, enemy->ent->ang_velocity);
    float target_yaw = 0.0;
    if (yaw_alignment < 0.0) {
      target_yaw =  enemy->wing.max_ang_vel * fabs(yaw_alignment);
    } else if (yaw_alignment > 0.0) {
      target_yaw =  -enemy->wing.max_ang_vel * fabs(yaw_alignment);
    }
    if (cur_yaw > target_yaw) {
      glm_vec3_scale_as(up, -enemy->wing.max_ang_accel * DELTA_TIME, temp);
    } else if (cur_yaw < target_yaw) {
      glm_vec3_scale_as(up, enemy->wing.max_ang_accel * DELTA_TIME, temp);
    }
    glm_vec3_add(temp, enemy->ent->ang_velocity, enemy->ent->ang_velocity);

    if (glm_vec3_norm(enemy->ent->ang_velocity) > enemy->wing.max_ang_vel) {
      glm_vec3_scale_as(enemy->ent->ang_velocity, enemy->wing.max_ang_vel,
                        enemy->ent->ang_velocity);
    }
  }

  if (enemy->cur_speed < target_speed) {
    enemy->cur_speed += enemy->thruster.max_accel * DELTA_TIME;
    if (enemy->cur_speed > enemy->thruster.max_vel) {
      enemy->cur_speed = enemy->thruster.max_vel;
    }
  } else if (enemy->cur_speed > target_speed) {
    enemy->cur_speed -= enemy->thruster.max_accel * DELTA_TIME;
    if (enemy->cur_speed < 0.0) {
      enemy->cur_speed = 0.0;
    }
  }
  glm_vec3_scale_as(forward, enemy->cur_speed, enemy->ent->velocity);

  if (ESHOOT_ON && enemy->e_can_shoot && player_alignment > 0.9 &&
      !enemy->ship_stalled) {
    enemy->e_can_shoot = 0;
    add_timer(1, (void *) &enemy->e_can_shoot, 1, NULL);
    use_power(enemy->weapon.max_power_draw, TYPE_WEAPON, enemy);

    vec3 gun_pos = GLM_VEC3_ZERO_INIT;
    glm_vec3_scale_as(forward, 12.0, gun_pos);
    glm_vec3_add(enemy->ent->translation, gun_pos, gun_pos);
    // spawn projectile
    size_t proj_index = init_projectile(gun_pos,
                                        forward,
                                        enemy->weapon.proj_speed +
                                        enemy->cur_speed,
                                        SRC_ENEMY,
                                        enemy->weapon.type,
                                        enemy->weapon.damage,
                                        enemy->weapon.range,
                                        0);
    projectile_insert_sim(proj_index);

  }
}

// ============================== SPACE HELPERS ==============================

void chase_player(vec3 e_pos, vec3 forward, vec3 player_forward,
                  float stop_dist, float proj_speed, vec3 target_dir,
                  float *target_speed) {
  float dist = glm_vec3_distance(player_ship.ent->translation, e_pos);
  get_shot_target(e_pos, player_ship.ent->translation,
                  player_ship.ent->velocity, proj_speed, target_dir);
  vec3 from_player = GLM_VEC3_ZERO_INIT;
  glm_vec3_sub(e_pos, player_ship.ent->translation, from_player);
  glm_vec3_normalize(from_player);

  if (dist <= MIN_SP_FOLLOW_RANGE + stop_dist &&
      glm_vec3_dot(from_player, player_forward) < 0.0) {
    (*target_speed) = 0.0;
  }
}

void avoid_bounds(vec3 e_pos, vec3 forward, float turning_rad,
                  vec3 target_dir, float *target_speed) {
  if (e_pos[X] >= space_size - turning_rad) {
    target_dir[X] = -1.0;
  } else if (e_pos[X] <= turning_rad - space_size) {
    target_dir[X] = 1.0;
  }
  if (e_pos[Y] >= space_size - turning_rad) {
    target_dir[Y] = -1.0;
  } else if (e_pos[Y] <= turning_rad - space_size) {
    target_dir[Y] = 1.0;
  }
  if (e_pos[Z] >= space_size - turning_rad) {
    target_dir[Z] = -1.0;
  } else if (e_pos[Z] <= turning_rad - space_size) {
    target_dir[Z] = 1.0;
  }
  glm_vec3_normalize(target_dir);
  glm_vec3_normalize(forward);
  float alignment = glm_vec3_dot(target_dir, forward);

  // Slow down ship as it approaches a collision
  float speed_modifier = glm_vec3_norm(target_dir);
  if (speed_modifier && alignment < 0.99) {
    speed_modifier = 5.0 / fabs(speed_modifier);
    if (speed_modifier < 1.0) {
      (*target_speed) *= speed_modifier;
    }
  }
  glm_vec3_normalize(target_dir);
}

void avoid_obstacles(COLLISION *nearby, size_t num_nearby, SHIP *enemy,
                     vec3 e_pos, vec3 forward, float stop_dist,
                     vec3 target_dir, float *target_speed) {
  size_t obj_index = 0;
  SOBJ *cur_obj = NULL;
  vec3 to_obj = GLM_VEC3_ZERO_INIT;
  float obj_dist = 0.0;
  float obj_alignment = 0.0;
  vec3 avoidance_dir = GLM_VEC3_ZERO_INIT;
  float speed_modifier = 1.0;
  for (size_t i = 0; i < num_nearby; i++) {
    obj_index = (size_t) nearby[i].b_ent->data;
    if (obj_index == enemy->wrapper_offset) {
      continue;
    }

    cur_obj = object_wrappers + obj_index;
    glm_vec3_sub(cur_obj->entity->translation, e_pos, to_obj);
    obj_dist = glm_vec3_norm(to_obj);
    glm_vec3_normalize(to_obj);
    obj_alignment = glm_vec3_dot(to_obj, forward);

    // Don't consider object if it is sufficiently "out of the way"
    if (obj_alignment < SP_OBJ_AVOIDANCE_THRESHOLD) {
      continue;
    }

    if (cur_obj->type == PLAYER_SHIP_OBJ ||
        cur_obj->type == ENEMY_SHIP_OBJ ||
        cur_obj->type == OBSTACLE_OBJ ||
        cur_obj->type == STATION_OBJ) {
      glm_vec3_cross(to_obj, forward, avoidance_dir);
      glm_vec3_cross(avoidance_dir, forward, avoidance_dir);
      glm_vec3_scale_as(avoidance_dir,
                        (obj_alignment - SP_OBJ_AVOIDANCE_THRESHOLD) /
                        (1.0 - SP_OBJ_AVOIDANCE_THRESHOLD), avoidance_dir);
      glm_vec3_add(avoidance_dir, forward, avoidance_dir);
      glm_vec3_normalize(avoidance_dir);
      glm_vec3_add(avoidance_dir, target_dir, target_dir);

      speed_modifier = fmin(speed_modifier, obj_dist / stop_dist);
    }
  }
  glm_vec3_normalize(target_dir);
  (*target_speed) = speed_modifier * enemy->thruster.max_vel;
}

void get_shot_target(vec3 e_pos, vec3 t_pos, vec3 t_vel, float proj_speed,
                     vec3 dest) {
  // Calculate the interception vector for the enemy ship to shoot such that
  // it's projectile intercepts the player's current trajectory

  vec3 q = GLM_VEC3_ZERO_INIT;
  glm_vec3_sub(t_pos, e_pos, q);

  float a = glm_vec3_dot(t_vel, t_vel) - (proj_speed * proj_speed);
  if (a == 0.0) {
    glm_vec3_sub(t_pos, e_pos, dest);
    glm_vec3_normalize(dest);
    return;
  }
  float b = 2.0 * glm_vec3_dot(t_vel, q);
  float c = glm_vec3_dot(q, q);

  float b2_4ac = (b * b) - (4.0 * a * c);
  if (b2_4ac < 0.0) {
    glm_vec3_sub(t_pos, e_pos, dest);
    glm_vec3_normalize(dest);
    return;
  }
  float sqrt_b2_4ac = sqrtf(b2_4ac);
  float a2 = 2.0 * a;

  float t1 = (-b + sqrt_b2_4ac) / a2;
  float t2 = (-b - sqrt_b2_4ac) / a2;

  float t = 0.0;
  if (t1 > 0.0 && t2 > 0.0) {
    if (t1 < t2) {
      t = t1;
    } else {
      t = t2;
    }
  } else if (t1 > 0.0) {
    // Add constant to time to make enemies lead their shots a little bit more.
    // This improves their aim.
    t = t1 + SP_SHOT_DELAY;
  } else if (t2 > 0.0) {
    // Add constant to time to make enemies lead their shots a little bit more.
    // This improves their aim.
    t = t2 + SP_SHOT_DELAY;
  } else {
    glm_vec3_sub(t_pos, e_pos, dest);
    glm_vec3_normalize(dest);
    return;
  }

  vec3 d = GLM_VEC3_ZERO_INIT;
  glm_vec3_scale(t_vel, t, d);
  glm_vec3_add(d, q, d);
  glm_vec3_scale(d, 1.0 / t, d);
  glm_vec3_normalize(d);
  glm_vec3_copy(d, dest);
}

// =============================== STATION MODE ==============================

void st_enemy_pathfind(size_t index) {
  ST_ENEMY *enemy = st_enemies + index;
  enemy_speak(index);
  if (enemy->invuln) {
    return;
  }
  //fprintf(stderr, "CUR_FRAME:\n");
  vec3 forward = GLM_VEC3_ZERO_INIT;
  glm_quat_rotatev(enemy->ent->rotation, (vec3) { -1.0, 0.0, 0.0 }, forward);
  vec3 enemy_pos_2d = { enemy->ent->translation[X], 0.0,
                        enemy->ent->translation[Z] };

  // Get vector to steer away from other enemies
  vec3 nearby_enemies = GLM_VEC3_ZERO_INIT;
  float nearby_enemies_speed = 0.0;
  glm_vec3_normalize_to(enemy->nearby_enemies, nearby_enemies);
  if (nearby_enemies[X] || nearby_enemies[Y] || nearby_enemies[Z]) {
    nearby_enemies_speed = 1.0;
  }
  glm_vec3_zero(enemy->nearby_enemies);

  if (enemy->cur_corridor == INVALID_INDEX) {
    enemy->cur_frame = INVALID_FRAME;
    update_timer_args(st_enemy_walk_cycle, (void *) index,
                      (void *) INVALID_INDEX);

    enemy->ent->velocity[X] = 0.0;
    enemy->ent->velocity[Z] = 0.0;
    glm_vec3_zero(enemy->ent->ang_velocity);
    return;
  }

  // Overall target direction to be calculated
  vec3 target_dir = GLM_VEC3_ZERO_INIT;
  float target_speed = 0.0;

  // Direction toward targeted corridor
  vec3 target_cd_dir = GLM_VEC3_ZERO_INIT;
  float target_cd_speed = 0.0;

  // Search for player's corridor (if within range)
  size_t player_cd = INVALID_INDEX;
  size_t to_player_cd = INVALID_INDEX;
  search_st_player(enemy, enemy->cur_corridor, &player_cd, &to_player_cd);
  //fprintf(stderr, "  enemy_cd: %ld\n", enemy->cur_corridor);
  //fprintf(stderr, "  to_player_cd: %ld\n", to_player_cd);
  //fprintf(stderr, "  player_cd: %ld\n", player_cd);

  vec3 to_player = GLM_VEC3_ZERO_INIT;
  glm_vec3_sub(st_player.ent->translation, enemy->ent->translation, to_player);
  float player_dist = glm_vec3_norm(to_player);
  glm_vec3_normalize(to_player);

  // Determine course of action based on proximity and line of sight to player
  int clear_shot = 0;
  if (enemy->ent->translation[Y] >= 5.0) {
    // Behavior for nested enemies
    enemy->target_corridor = enemy->cur_corridor;
    clear_shot = 1;
  } else if (enemy->weapon_type == RANGED) {
    if (player_cd != INVALID_INDEX) {
      //fprintf(stderr, "  Found Player\n");
      // Get clear shot to player in a corridor with a valid range
      clear_shot = check_clear_shot(enemy->cur_corridor, player_cd);
      //fprintf(stderr, "  clear_shot: %d\n", clear_shot);
      //fprintf(stderr, "  player_dist: %f\n", player_dist);
      if (!clear_shot || player_dist > ST_ENEMY_RANGE_MAX) {
        float test_dist = glm_vec3_distance(cd_obs[to_player_cd].ent->translation,
                                            cd_obs[player_cd].ent->translation);
        if (test_dist < ST_ENEMY_RANGE_MIN + 4.0 &&
            check_clear_shot(to_player_cd, player_cd)) {
          //fprintf(stderr, "  Holding peek spot\n");
          enemy->target_corridor = enemy->cur_corridor;
        } else {
          //fprintf(stderr, "  Moving toward player\n");
          enemy->target_corridor = to_player_cd;
        }
      } else if (player_dist < ST_ENEMY_RANGE_MIN) {
        // Find corridor out of range or out of line of sight
        if (player_cd == enemy->cur_corridor) {
          //fprintf(stderr, "Player in current corridor, patroling\n");
          vec3 backward = GLM_VEC3_ZERO_INIT;
          glm_vec3_negate_to(forward, backward);
          enemy->target_corridor = search_patrol_cd(enemy->cur_corridor,
                                                    backward);
        } else {
          //fprintf(stderr, "Player nearby, escaping\n");
          enemy->target_corridor = search_evasion_cd(enemy->cur_corridor,
                                                     player_cd);
        }
        if (enemy->target_corridor == INVALID_INDEX) {
          enemy->target_corridor = enemy->cur_corridor;
        }
      } else {
        //fprintf(stderr, "  Holding\n");
        enemy->target_corridor = enemy->cur_corridor;
      }
    } else {
      // Patrol
      enemy->target_corridor = search_patrol_cd(enemy->cur_corridor, forward);
    }
  } else {
    if (player_cd != INVALID_INDEX) {
      clear_shot = check_clear_shot(enemy->cur_corridor, player_cd);
      enemy->target_corridor = to_player_cd;
    } else {
      // Patrol
      enemy->target_corridor = search_patrol_cd(enemy->cur_corridor, forward);
    }
  }

  // Calculate target speed and direction based on course of action
  CORRIDOR *cd = cd_obs + enemy->target_corridor;
  vec3 cd_pos_2d = { cd->ent->translation[X], 0.0, cd->ent->translation[Z] };
  float to_cd_center = glm_vec3_distance(enemy_pos_2d, cd_pos_2d);
  if (enemy->weapon_type == RANGED) {
    if (to_cd_center > 1.0) {
      glm_vec3_sub(cd_pos_2d, enemy_pos_2d, target_cd_dir);
      glm_vec3_normalize(target_cd_dir);
      // Check if enemy should move backward to target corridor to maintain
      // line of sight of player
      //fprintf(stderr, "  target_cd_dir: [ %f, %f, %f ]\n",
      //        target_cd_dir[X], target_cd_dir[Y], target_cd_dir[Z]);
      //fprintf(stderr, "  to_player: [ %f, %f, %f ]\n",
      //        to_player[X], to_player[Y], to_player[Z]);
      float backward_check = glm_vec3_dot(target_cd_dir, to_player);
      //fprintf(stderr, "  backward_check: %f\n", backward_check);
      if (backward_check < -0.7) {
        glm_vec3_negate(target_cd_dir);
        target_cd_speed = -2.0;
      } else {
        target_cd_speed = 2.0;
      }
    } else {
      glm_vec3_copy(to_player, target_cd_dir);
      target_cd_speed = 0.0;
    }
  } else {
    if (clear_shot) {
      glm_vec3_copy(to_player, target_cd_dir);
      if (player_dist < 2.0) {
        target_cd_speed = 0.0;
      } else {
        target_cd_speed = 2.0;
      }
    } else {
      glm_vec3_sub(cd_pos_2d, enemy_pos_2d, target_cd_dir);
      target_cd_speed = 2.0;
    }
  }

  // Check if enemy should move backward to target corridor to maintain
  // line of sight of player
  float backward_check = glm_vec3_dot(nearby_enemies, to_player);
  if (backward_check < -0.7) {
    glm_vec3_negate(nearby_enemies);
    nearby_enemies_speed = -1.0;
  } else {
    nearby_enemies_speed = 1.0;
  }

  glm_vec3_add(nearby_enemies, target_cd_dir, target_dir);
  glm_vec3_normalize(target_dir);
  target_speed = (nearby_enemies_speed + target_cd_speed) / 2.0;
  target_speed = target_cd_speed;

  // Move enemy given target direction
  float alignment = glm_vec3_dot(target_dir, forward);
  if (alignment >= 0.75) {
    vec3 vel = GLM_VEC3_ZERO_INIT;
    glm_vec3_scale_as(forward, enemy->cur_speed * target_speed, vel);
    enemy->ent->velocity[X] = vel[X];
    enemy->ent->velocity[Z] = vel[Z];
  }
  if (alignment < 1.0) {
    vec3 test_dir = GLM_VEC3_ZERO_INIT;
    glm_vec3_cross(forward, target_dir, test_dir);
    glm_vec3_normalize(test_dir);
    if (glm_vec3_dot(test_dir, (vec3) { 0.0, 1.0, 0.0 }) > 0.0) {
      glm_vec3_copy((vec3) { 0.0, 5.0, 0.0 }, enemy->ent->ang_velocity);
    } else {
      glm_vec3_copy((vec3) { 0.0, -5.0, 0.0 }, enemy->ent->ang_velocity);
    }
  } else {
    glm_vec3_zero(enemy->ent->ang_velocity);
  }

  // Attack Player
  float player_alignment = glm_vec3_dot(forward, to_player);
  if (enemy->weapon_type == RANGED && clear_shot && player_alignment > 0.9 &&
      ESHOOT_ON && enemy->can_shoot) {
    enemy->can_shoot = 0;
    add_timer(enemy->fire_rate, (void *) &enemy->can_shoot, 1, NULL);

    vec3 proj_pos = GLM_VEC3_ZERO_INIT;
    glm_vec3_scale(forward, 1.0, proj_pos);
    glm_vec3_add(enemy->ent->translation, proj_pos, proj_pos);

    size_t proj_index = init_projectile(proj_pos,
                                        to_player,
                                        ST_E_BASE_PROJ_SPEED +
                                        enemy->cur_speed,
                                        SRC_ENEMY,
                                        LASER,
                                        ST_E_BASE_PROJ_DAMAGE,
                                        ST_E_BASE_PROJ_RANGE,
                                        1);
    projectile_insert_sim(proj_index);

    enemy->cur_frame = 0;
    add_timer(0.016, st_enemy_shoot_anim, -1000, (void *) index);
  } else if (enemy->weapon_type == MELEE && clear_shot &&
             player_alignment > 0.9 && ESHOOT_ON && enemy->can_shoot &&
             player_dist < 3.0) {
    enemy->can_shoot = 0;
    add_timer(enemy->fire_rate, (void *) &enemy->can_shoot, 1, NULL);

    vec3 proj_pos = GLM_VEC3_ZERO_INIT;
    glm_vec3_scale_as(forward, 1.25, proj_pos);
    glm_vec3_add(enemy->ent->translation, proj_pos, proj_pos);

    size_t proj_index = init_projectile(proj_pos,
                                        forward,
                                        enemy->cur_speed + 0.01,
                                        SRC_ENEMY,
                                        T_MELEE,
                                        ST_E_BASE_PROJ_DAMAGE,
                                        0.2,
                                        1);
    projectile_insert_sim(proj_index);

    enemy->cur_frame = 0;
    add_timer(0.016, st_enemy_swing_anim, -1000, (void *) index);
  } else if (enemy->cur_frame == INVALID_FRAME && target_speed) {
    // Animate walk cycle
    enemy->cur_frame = 0;
    add_timer(0.016, st_enemy_walk_cycle, -1000, (void *) index);
  }
}

// ============================= STATION HELPERS =============================

void search_st_player(ST_ENEMY *enemy, size_t first_cd, size_t *player_cd,
                      size_t *to_player_cd) {
  vec3 st_player_pos = GLM_VEC3_ZERO_INIT;
  glm_vec3_copy(st_player.ent->translation, st_player_pos);

  CELL_DATA *cell_data = malloc(sizeof(CELL_DATA) * num_corridors);
  if (!cell_data) {
    return;
  }
  for (size_t i = 0; i < num_corridors; i++) {
    cell_data[i].prev = INVALID_INDEX;
    cell_data[i].visited = 0;
  }

  SEARCH_FRAME *search_queue = malloc(sizeof(SEARCH_FRAME) *
                                      BUFF_STARTING_LEN);
  if (!search_queue) {
    free(cell_data);
    return;
  }
  size_t front = 0;
  size_t rear = 1;
  size_t queue_size = BUFF_STARTING_LEN;
  search_queue[0].cd = first_cd;
  search_queue[0].depth = 0;
  search_queue[0].searchable = SEARCHABLE_ALL;
  cell_data[first_cd].visited = 1;

  size_t *nb = NULL;
  size_t cur_cd = 0;
  size_t cur_neighbor = 0;
  int cur_depth = 0;
  float cur_dist = 0;
  size_t target = INVALID_INDEX;
  while (front != rear) {
    cur_cd = search_queue[front].cd;
    cur_depth = search_queue[front].depth;
    front = (front + 1) % queue_size;

    // Check if player in corridor
    // (i.e player is <= 4.0 meters from center of corridor)
    cur_dist = glm_vec3_distance2(st_player_pos,
                                  cd_obs[cur_cd].ent->translation);
    if (cur_dist <= 4.0 * 4.0) {
      // Set to 3 for debugging
      cell_data[cur_cd].visited = 3;
      target = cur_cd;
      break;
    }

    // Add children corridors to search if depth not exausted
    if (cur_depth == ST_ENEMY_SEARCH_DEPTH) {
      continue;
    }
    nb = cd_obs[cur_cd].neighbors;
    for (int i = 0; i < 8; i++) {
      cur_neighbor = nb[i];
      // Dont consider unaccessable/visited neighbors
      if (!can_access(nb, i) || cell_data[cur_neighbor].visited) {
        continue;
      }

      search_queue[rear].cd = nb[i];
      search_queue[rear].depth = cur_depth + 1;
      search_queue[rear].searchable = SEARCHABLE_ALL;
      cell_data[nb[i]].visited = 1;
      cell_data[cur_neighbor].prev = cur_cd;
      rear = (rear + 1) % queue_size;
      if (rear == front) {
        int status = double_search_queue(&search_queue, &front, &rear,
                                         &queue_size);
        if (status) {
          break;
        }
      }
    }
  }

  if (target != INVALID_INDEX) {
    *player_cd = target;
    //fprintf(stderr, "path: %ld ", target);
    while (cell_data[target].prev != first_cd &&
           cell_data[target].prev != INVALID_INDEX) {
      target = cell_data[target].prev;
      //fprintf(stderr, "%ld ", target);
    }
    ///fprintf(stderr, "\n");
    *to_player_cd = target;
  }

  // Set to 2 for debugging
  cell_data[first_cd].visited = 2;
  //print_cell_data(cell_data);

  free(search_queue);
  free(cell_data);
  return;
}

size_t search_patrol_cd(size_t enemy_cd, vec3 enemy_dir) {
  float max_alignment = -1.0;
  size_t best_cd = INVALID_INDEX;
  float cur_alignment = 0.0;
  size_t cur_neighbor = 0;
  vec3 to_neighbor = GLM_VEC3_ZERO_INIT;
  for (int i = 0; i < 4; i++) {
    if (i == 0) {
      cur_neighbor = cd_obs[enemy_cd].neighbors[NEIGHBOR_TOP];
    } else if (i == 1) {
      cur_neighbor = cd_obs[enemy_cd].neighbors[NEIGHBOR_LEFT];
    } else if (i == 2) {
      cur_neighbor = cd_obs[enemy_cd].neighbors[NEIGHBOR_RIGHT];
    } else {
      cur_neighbor = cd_obs[enemy_cd].neighbors[NEIGHBOR_BOTTOM];
    }
    if (cur_neighbor == INVALID_INDEX) {
      continue;
    }

    glm_vec3_sub(cd_obs[cur_neighbor].ent->translation,
                 cd_obs[enemy_cd].ent->translation, to_neighbor);
    glm_vec3_normalize(to_neighbor);
    cur_alignment = glm_vec3_dot(to_neighbor, enemy_dir);

    if (cur_alignment > max_alignment || best_cd == INVALID_INDEX) {
      max_alignment = cur_alignment;
      best_cd = cur_neighbor;
    }
  }

  return best_cd;
}

size_t search_evasion_cd(size_t enemy_cd, size_t player_cd) {
  vec3 to_player = GLM_VEC3_ZERO_INIT;
  glm_vec3_sub(cd_obs[player_cd].ent->translation,
               cd_obs[enemy_cd].ent->translation, to_player);
  // Evasion cd is the neighbor index of the enemy_cd which the enemy is
  // attempting to move away from
  int evasion_cd = 0;
  if (to_player[X] < 0.0 && to_player[Z] > 0.0) {
    //fprintf(stderr, "  evasion_cd: TOP_LEFT\n");
    evasion_cd = NEIGHBOR_TOP_LEFT;
  } else if (to_player[X] == 0.0 && to_player[Z] > 0.0) {
    //fprintf(stderr, "  evasion_cd: TOP\n");
    evasion_cd = NEIGHBOR_TOP;
  } else if (to_player[X] > 0.0 && to_player[Z] > 0.0) {
    //fprintf(stderr, "  evasion_cd: TOP_RIGHT\n");
    evasion_cd = NEIGHBOR_TOP_RIGHT;
  } else if (to_player[X] < 0.0 && to_player[Z] == 0.0) {
    //fprintf(stderr, "  evasion_cd: LEFT\n");
    evasion_cd = NEIGHBOR_LEFT;
  } else if (to_player[X] > 0.0 && to_player[Z] == 0.0) {
    //fprintf(stderr, "  evasion_cd: RIGHT\n");
    evasion_cd = NEIGHBOR_RIGHT;
  } else if (to_player[X] < 0.0 && to_player[Z] < 0.0) {
    //fprintf(stderr, "  evasion_cd: BOTTOM_LEFT\n");
    evasion_cd = NEIGHBOR_BOTTOM_LEFT;
  } else if (to_player[X] == 0.0 && to_player[Z] < 0.0) {
    //fprintf(stderr, "  evasion_cd: BOTTOM\n");
    evasion_cd = NEIGHBOR_BOTTOM;
  } else if (to_player[X] > 0.0 && to_player[Z] < 0.0) {
    //fprintf(stderr, "  evasion_cd: BOTTOM_RIGHT\n");
    evasion_cd = NEIGHBOR_BOTTOM_RIGHT;
  } else {
    //fprintf(stderr, "BAD!\n");
  }

  float enemy_dist = glm_vec3_distance(cd_obs[enemy_cd].ent->translation,
                                       cd_obs[player_cd].ent->translation);

  size_t ret = INVALID_INDEX;
  float cur_dist = 0.0;
  size_t cur_neighbor = 0;
  size_t *nb = cd_obs[enemy_cd].neighbors;
  for (int i = 0; i < 8; i++) {
    cur_neighbor = nb[i];
    if (i == evasion_cd || !can_access(nb, i) ||
        (evasion_cd == NEIGHBOR_TOP_LEFT &&
         (i == NEIGHBOR_TOP || i == NEIGHBOR_LEFT)) ||
        (evasion_cd == NEIGHBOR_TOP_RIGHT &&
         (i == NEIGHBOR_TOP || i == NEIGHBOR_RIGHT)) ||
        (evasion_cd == NEIGHBOR_BOTTOM_LEFT &&
         (i == NEIGHBOR_BOTTOM || i == NEIGHBOR_LEFT)) ||
        (evasion_cd == NEIGHBOR_BOTTOM_RIGHT &&
         (i == NEIGHBOR_BOTTOM || i == NEIGHBOR_RIGHT))) {
      continue;
    }
    cur_dist = glm_vec3_distance(cd_obs[cur_neighbor].ent->translation,
                                 cd_obs[player_cd].ent->translation);
    if (cur_dist < enemy_dist) {
      continue;
    }

    if ((i == NEIGHBOR_TOP_LEFT && evasion_cd == NEIGHBOR_BOTTOM_RIGHT) ||
        (i == NEIGHBOR_TOP && evasion_cd == NEIGHBOR_BOTTOM) ||
        (i == NEIGHBOR_TOP_RIGHT && evasion_cd == NEIGHBOR_BOTTOM_LEFT) ||
        (i == NEIGHBOR_LEFT && evasion_cd == NEIGHBOR_RIGHT) ||
        (i == NEIGHBOR_RIGHT && evasion_cd == NEIGHBOR_LEFT) ||
        (i == NEIGHBOR_BOTTOM_LEFT && evasion_cd == NEIGHBOR_TOP_RIGHT) ||
        (i == NEIGHBOR_BOTTOM && evasion_cd == NEIGHBOR_TOP) ||
        (i == NEIGHBOR_BOTTOM_RIGHT && evasion_cd == NEIGHBOR_BOTTOM_LEFT)) {
      // Prioritize the neighbor across from evasion_cd
      ret = cd_obs[enemy_cd].neighbors[i];
      break;
    } else {
      // If a less-than-ideal neighbor is valid, consider it
      ret = cd_obs[enemy_cd].neighbors[i];
    }
  }

  return ret;
}

int check_clear_shot(size_t enemy_cd, size_t player_cd) {
  if (enemy_cd == player_cd) {
    return 1;
  }

  CELL_DATA *cell_data = malloc(sizeof(CELL_DATA) * num_corridors);
  if (!cell_data) {
    return 0;
  }
  for (size_t i = 0; i < num_corridors; i++) {
    cell_data[i].prev = INVALID_INDEX;
    cell_data[i].visited = 0;
  }

  SEARCH_FRAME *search_queue = malloc(sizeof(SEARCH_FRAME) *
                                      BUFF_STARTING_LEN);
  if (!search_queue) {
    free(cell_data);
    return 0;
  }
  size_t front = 0;
  size_t rear = 1;
  size_t queue_size = BUFF_STARTING_LEN;
  search_queue[0].cd = enemy_cd;
  search_queue[0].depth = 0;
  search_queue[0].searchable = 0;
  for (int i = 0; i < 8; i++) {
    if (can_access(cd_obs[enemy_cd].neighbors, i)) {
      search_queue[0].searchable |= SEARCH_FLAGS[i];
    }
  }
  cell_data[enemy_cd].visited = 1;

  size_t *nb = NULL;
  size_t cur_cd = 0;
  size_t cur_neighbor = 0;
  int cur_depth = 0;
  int cur_searchable = 0;
  int child_searchable = 0;
  int found = 0;
  while (front != rear) {
    cur_cd = search_queue[front].cd;
    cur_depth = search_queue[front].depth;
    cur_searchable = search_queue[front].searchable;
    front = (front + 1) % queue_size;

    if (cur_cd == player_cd) {
      // Set to 3 for debugging
      cell_data[cur_cd].visited = 3;
      found = 1;
      break;
    }

    // Add children corridors to search if depth not exausted
    if (cur_depth == ST_ENEMY_SEARCH_DEPTH) {
      continue;
    }
    nb = cd_obs[cur_cd].neighbors;
    for (int i = 0; i < 8; i++) {
      cur_neighbor = nb[i];
      // Dont consider unaccessable/visited neighbors
      if (!(cur_searchable & SEARCH_FLAGS[i]) || !can_access(nb, i) ||
          cell_data[cur_neighbor].visited) {
        continue;
      }

      search_queue[rear].cd = nb[i];
      search_queue[rear].depth = cur_depth + 1;
      child_searchable = cur_searchable &
                         gen_searchable_neighbors(cd_obs[nb[i]].neighbors, i);
      search_queue[rear].searchable = child_searchable;
      cell_data[nb[i]].visited = 1;
      cell_data[cur_neighbor].prev = cur_cd;
      rear = (rear + 1) % queue_size;
      if (rear == front) {
        int status = double_search_queue(&search_queue, &front, &rear,
                                         &queue_size);
        if (status) {
          break;
        }
      }
    }
  }

  // Set to 2 for debugging
  cell_data[enemy_cd].visited = 2;
  //print_cell_data(cell_data);

  free(search_queue);
  free(cell_data);

  return found;
}

int double_search_queue(SEARCH_FRAME **queue, size_t *front, size_t *rear,
                        size_t *size) {
  size_t old_size = *size;
  SEARCH_FRAME *new_queue = malloc(sizeof(SEARCH_FRAME) * 2 * old_size);
  if (new_queue == NULL) {
    return -1;
  }

  size_t f = *front;
  size_t r = *rear;
  size_t len = 0;
  do {
    new_queue[len] = (*queue)[f];
    f = (f + 1) % old_size;
    len++;
  } while(f != r);

  *queue = new_queue;
  *front = 0;
  *rear = len;
  *size = 2 * old_size;
  return 0;
}

// Find the searchable neighbors of a node given its neighbor list and position
// relative to its parent
int gen_searchable_neighbors(size_t *nb, size_t i) {
  int ret = 0;
  if (i == NEIGHBOR_TOP_LEFT && nb[i] != INVALID_INDEX) {
    ret = SEARCHABLE_TL | SEARCHABLE_T | SEARCHABLE_L;
  } else if (i == NEIGHBOR_TOP_RIGHT && nb[i] != INVALID_INDEX) {
    ret = SEARCHABLE_TR | SEARCHABLE_T | SEARCHABLE_R;
  } else if (i == NEIGHBOR_BOTTOM_LEFT && nb[i] != INVALID_INDEX) {
    ret = SEARCHABLE_BL | SEARCHABLE_B | SEARCHABLE_L;
  } else if (i == NEIGHBOR_BOTTOM_RIGHT && nb[i] != INVALID_INDEX) {
    ret = SEARCHABLE_BR | SEARCHABLE_B | SEARCHABLE_R;
  } else if (i == NEIGHBOR_TOP) {
    ret = SEARCHABLE_T;
  } else if (i == NEIGHBOR_LEFT) {
    ret = SEARCHABLE_L;
  } else if (i == NEIGHBOR_RIGHT) {
    ret = SEARCHABLE_R;
  } else if (i == NEIGHBOR_BOTTOM) {
    ret = SEARCHABLE_B;
  }
  return ret;
}

int can_access(size_t *nb, size_t i) {
  if (nb[i] == INVALID_INDEX ||
      (i == NEIGHBOR_TOP_LEFT &&
       (nb[NEIGHBOR_TOP] == INVALID_INDEX ||
        nb[NEIGHBOR_LEFT] == INVALID_INDEX)) ||
      (i == NEIGHBOR_TOP_RIGHT &&
       (nb[NEIGHBOR_TOP] == INVALID_INDEX ||
        nb[NEIGHBOR_RIGHT] == INVALID_INDEX)) ||
      (i == NEIGHBOR_BOTTOM_LEFT &&
       (nb[NEIGHBOR_BOTTOM] == INVALID_INDEX ||
        nb[NEIGHBOR_LEFT] == INVALID_INDEX)) ||
      (i == NEIGHBOR_BOTTOM_RIGHT &&
       (nb[NEIGHBOR_BOTTOM] == INVALID_INDEX ||
        nb[NEIGHBOR_RIGHT] == INVALID_INDEX))) {
    return 0;
  }
  return 1;
}

void print_cell_data(CELL_DATA *data) {
  for (int i = 0; i < maze_size; i++) {
    for (int j = 0; j < maze_size; j++) {
      int found = 0;
      vec2 pos = {
        (((float) i - 1) * 5.0) - (2.5 * maze_size),
        (((float) j - 1) * 5.0) - (2.5 * maze_size),
      };
      for (size_t k = 0; k < num_corridors; k++) {
        if (pos[X] == cd_obs[k].ent->translation[X] &&
            pos[Y] == cd_obs[k].ent->translation[Z]) {
          printf("%d ", data[k].visited);
          found = 1;
          break;
        }
      }
      if (!found) {
        printf("X ");
      }
    }
    printf("\n");
  }

  for (int i = 0; i < maze_size; i++) {
    for (int j = 0; j < maze_size; j++) {
      int found = 0;
      vec2 pos = {
        (((float) i - 1) * 5.0) - (2.5 * maze_size),
        (((float) j - 1) * 5.0) - (2.5 * maze_size),
      };
      for (size_t k = 0; k < num_corridors; k++) {
        if (pos[X] == cd_obs[k].ent->translation[X] &&
            pos[Y] == cd_obs[k].ent->translation[Z]) {
	  #ifdef __linux__
          printf("%02ld ", k);
          #endif
          found = 1;
          break;
        }
      }
      if (!found) {
        printf("XX ");
      }
    }
    printf("\n");
  }
}


