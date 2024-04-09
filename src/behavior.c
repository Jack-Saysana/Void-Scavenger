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

  vec3 forward = { -1.0, 0.0, 0.0 };
  glm_quat_rotatev(enemy->ent->rotation, forward, forward);
  vec3 up = { 0.0, 1.0, 0.0 };
  glm_quat_rotatev(enemy->ent->rotation, up, up);
  vec3 side = GLM_VEC3_ZERO_INIT;
  glm_vec3_cross(forward, up, side);
  glm_vec3_normalize(side);

  float turning_rad = 50.0 + (enemy->thruster.max_vel /
                              enemy->wing.max_ang_vel);

  //fprintf(stderr, "FRAME BEGIN:\n");
  //fprintf(stderr, "  nearby: [ %f, %f, %f ]\n", enemy->nearby_obstacles[X],
  //        enemy->nearby_obstacles[Y], enemy->nearby_obstacles[Z]);
  vec3 target_dir = GLM_VEC3_ZERO_INIT;
  float target_speed = enemy->thruster.max_vel;

  // Steer ship away from arena edges
  vec3 ab_dir = GLM_VEC3_ZERO_INIT;
  float ab_speed = enemy->thruster.max_vel;
  avoid_bounds(e_pos, forward, turning_rad, ab_dir, &ab_speed);
  // Take into account priority of avoiding bounds
  glm_vec3_scale(ab_dir, SP_AVOID_BOUNDS_PRIORITY, ab_dir);
  glm_vec3_add(ab_dir, target_dir, target_dir);

  /*
  // Steer ship away from nearby obstacles
  vec3 ao_dir = GLM_VEC3_ZERO_INIT;
  float ao_speed = enemy->thruster.max_vel;
  glm_vec3_copy(enemy->nearby_obstacles, ao_dir);
  if (ao_dir[X] || ao_dir[Y] || ao_dir[Z]) {
    ao_speed = 0.5 * enemy->thruster.max_vel;
  }
  // Take into account priority of avoiding obstacles
  glm_vec3_scale(ao_dir, SP_AVOID_OBSTACLE_PRIORITY, ao_dir);
  glm_vec3_zero(enemy->nearby_obstacles);
  glm_vec3_add(ao_dir, target_dir, target_dir);
  */

  // Chase the player
  vec3 p_dir = GLM_VEC3_ZERO_INIT;
  float p_speed = enemy->thruster.max_vel;
  chase_player(e_pos, forward, enemy->weapon.proj_speed + enemy->cur_speed,
               p_dir, &p_speed);
  // Take into account priority of chasing player
  glm_vec3_scale(p_dir, SP_CHASE_PRIORITY, p_dir);
  glm_vec3_add(p_dir, target_dir, target_dir);

  // Calculate overall target direction and speed
  glm_vec3_normalize(target_dir);
  float div = 0.0;
  if (target_dir[X] || target_dir[Y] || target_dir[Z]) {
    target_speed = 0.0;
    if (ab_dir[X] || ab_dir[Y] || ab_dir[Z]) {
      target_speed += ab_speed;
      div++;
    }
    /*
    if (ao_dir[X] || ao_dir[Y] || ao_dir[Z]) {
      target_speed += ao_speed;
      div++;
    }
    */
    if (p_dir[X] || p_dir[Y] || p_dir[Z]) {
      target_speed += p_speed;
      div++;
    }
    target_speed /= div;
  }

  float player_alignment = glm_vec3_dot(forward, p_dir);
  //float alignment = glm_vec3_dot(forward, target_dir);
  vec3 temp = GLM_VEC3_ZERO_INIT;

  /*
  fprintf(stderr, "  ab: [ %f, %f, %f ]\n", ab_dir[X], ab_dir[Y], ab_dir[Z]);
  fprintf(stderr, "  cp: [ %f, %f, %f ]\n", p_dir[X], p_dir[Y], p_dir[Z]);
  fprintf(stderr, "  target: [ %f, %f, %f ]\n",
          target_dir[X], target_dir[Y], target_dir[Z]);
  fprintf(stderr, "  forward: [ %f, %f, %f ]\n",
          forward[X], forward[Y], forward[Z]);
  fprintf(stderr, "  alignment: %f\n", alignment);
  */

  if (target_dir[X] || target_dir[Y] || target_dir[Z]) {
    // Goal: Steer ship using linear combination of pitch roll and yaw to
    // ensure that the ship's forward vector matches its target vector, and
    // the forward, target and up vectors are coplanar. This will create a
    // "realistic" looking turning style

    // Pitch
    float pitch_alignment = glm_vec3_dot(target_dir, up);
    float cur_pitch = glm_vec3_dot(side, enemy->ent->ang_velocity);
    float target_pitch = 0.0;
    //fprintf(stderr, "  pitch_alignment: %f\n", pitch_alignment);
    if (pitch_alignment < 0.0) {
      target_pitch = -enemy->wing.max_ang_vel * fabs(pitch_alignment);
    } else if (pitch_alignment > 0.0) {
      target_pitch = enemy->wing.max_ang_vel * fabs(pitch_alignment);
    }
    //fprintf(stderr, "  target_pitch: %f\n", target_pitch);
    //fprintf(stderr, "  cur_pitch: %f\n", cur_pitch);
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
    //fprintf(stderr, "  roll_alignment: %f\n", roll_alignment);
    if (roll_alignment < 0.0) {
      target_roll = enemy->wing.max_ang_vel * fabs(roll_alignment);
    } else if (roll_alignment > 0.0) {
      target_roll = -enemy->wing.max_ang_vel * fabs(roll_alignment);
    }
    //fprintf(stderr, "  target_roll: %f\n", target_roll);
    //fprintf(stderr, "  cur_roll: %f\n", cur_roll);
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
    //fprintf(stderr, "  yaw_alignment: %f\n", yaw_alignment);
    if (yaw_alignment < 0.0) {
      target_yaw =  enemy->wing.max_ang_vel * fabs(yaw_alignment);
    } else if (yaw_alignment > 0.0) {
      target_yaw =  -enemy->wing.max_ang_vel * fabs(yaw_alignment);
    }
    //fprintf(stderr, "  target_yaw: %f\n", target_yaw);
    //fprintf(stderr, "  cur_yaw: %f\n", cur_yaw);
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

  if (ESHOOT_ON && enemy->e_can_shoot && player_alignment > 0.9) {
    enemy->e_can_shoot = 0;
    add_timer(1, (void *) &enemy->e_can_shoot, 1, NULL);

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

void chase_player(vec3 e_pos, vec3 forward, float proj_speed, vec3 target_dir,
                  float *target_speed) {
  float dist = glm_vec3_distance(player_ship.ent->translation, e_pos);
  if (dist <= MAX_SP_AGRO_RANGE) {
    get_shot_target(e_pos, player_ship.ent->translation,
                    player_ship.ent->velocity, proj_speed, target_dir);
    vec3 test = GLM_VEC3_ZERO_INIT;
    glm_vec3_sub(player_ship.ent->translation, e_pos, test);
    glm_vec3_normalize(test);
    /*
    fprintf(stderr, "  to_player: [ %f, %f, %f ]\n",
            test[X], test[Y], test[Z]);
    fprintf(stderr, "  interception: [ %f, %f, %f ]\n",
            target_dir[X], target_dir[Y], target_dir[Z]);
    fprintf(stderr, "  p_vel: [ %f, %f, %f ]\n",
            player_ship.ent->velocity[X], player_ship.ent->velocity[Y],
            player_ship.ent->velocity[Z]);
    */

    if (dist <= MIN_SP_FOLLOW_RANGE) {
      (*target_speed) = 0.0;
    }
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

void get_shot_target(vec3 e_pos, vec3 t_pos, vec3 t_vel, float proj_speed,
                     vec3 dest) {
//  fprintf(stderr, "  e_pos: [ %f, %f, %f ]\n", e_pos[X], e_pos[Y], e_pos[Z]);
//  fprintf(stderr, "  t_pos: [ %f, %f, %f ]\n", t_pos[X], t_pos[Y], t_pos[Z]);
//  fprintf(stderr, "  t_vel: [ %f, %f, %f ]\n", t_vel[X], t_vel[Y], t_vel[Z]);
//  fprintf(stderr, "  proj_speed: %f\n", proj_speed);
  // Calculate the interception vector for the enemy ship to shoot such that
  // it's projectile intercepts the player's current trajectory

  vec3 q = GLM_VEC3_ZERO_INIT;
  glm_vec3_sub(t_pos, e_pos, q);

  float a = glm_vec3_dot(t_vel, t_vel) - (proj_speed * proj_speed);
//  fprintf(stderr, "  a: %f\n", a);
  if (a == 0.0) {
    glm_vec3_sub(t_pos, e_pos, dest);
    glm_vec3_normalize(dest);
    return;
  }
  float b = 2.0 * glm_vec3_dot(t_vel, q);
//  fprintf(stderr, "  b: %f\n", b);
  float c = glm_vec3_dot(q, q);
//  fprintf(stderr, "  c: %f\n", c);

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
//  fprintf(stderr, "  t1: %f\n", t1);
//  fprintf(stderr, "  t2: %f\n", t2);

  float t = 0.0;
  if (t1 > 0.0 && t2 > 0.0) {
    if (t1 < t2) {
      t = t1;
    } else {
      t = t2;
    }
  } else if (t1 > 0.0) {
    t = t1;
  } else if (t2 > 0.0) {
    t = t2;
  } else {
    glm_vec3_sub(t_pos, e_pos, dest);
    glm_vec3_normalize(dest);
    return;
  }
//  fprintf(stderr, "  t: %f\n", t);

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
  if (enemy->invuln) {
    return;
  }
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

  vec3 to_player = GLM_VEC3_ZERO_INIT;
  glm_vec3_sub(st_player.ent->translation, enemy->ent->translation, to_player);
  float player_dist = glm_vec3_norm(to_player);

  // Determine course of action based on proximity and line of sight to player
  int clear_shot = 0;
  if (enemy->weapon_type == RANGED) {
    if (player_cd != INVALID_INDEX) {
      // Get clear shot to player in a corridor with a valid range
      clear_shot = check_clear_shot(enemy->cur_corridor, player_cd);
      if (!clear_shot || player_dist > ST_ENEMY_RANGE_MAX) {
        float test_dist = glm_vec3_distance(cd_obs[to_player_cd].ent->translation,
                                            cd_obs[player_cd].ent->translation);
        if (test_dist < ST_ENEMY_RANGE_MIN + 4.0 &&
            check_clear_shot(to_player_cd, player_cd)) {
          enemy->target_corridor = enemy->cur_corridor;
        } else {
          enemy->target_corridor = to_player_cd;
        }
      } else if (player_dist < ST_ENEMY_RANGE_MIN) {
        // Find corridor out of range or out of line of sight
        if (player_cd == enemy->cur_corridor) {
          enemy->target_corridor = search_patrol_cd(enemy->cur_corridor,
                                                    forward);
        } else {
          enemy->target_corridor = search_evasion_cd(enemy->cur_corridor,
                                                     player_cd);
        }
        if (enemy->target_corridor == INVALID_INDEX) {
          enemy->target_corridor = enemy->cur_corridor;
        }
      } else {
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
      target_cd_speed = 2.0;
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

  glm_vec3_add(nearby_enemies, target_cd_dir, target_dir);
  glm_vec3_normalize(target_dir);
  target_speed = (nearby_enemies_speed + target_cd_speed) / 2.0;
  glm_vec3_normalize_to(target_cd_dir, target_dir);
  target_speed = target_cd_speed;

  // Move enemy given target direction
  float alignment = glm_vec3_dot(target_dir, forward);
  if (alignment >= 0.75) {
    vec3 vel = GLM_VEC3_ZERO_INIT;
    glm_vec3_scale_as(forward, enemy->cur_speed * target_speed, vel);
    enemy->ent->velocity[X] = vel[X];
    enemy->ent->velocity[Z] = vel[Z];
  }
  if (alignment < 0.99) {
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

  // Animate walk cycle
  if (enemy->cur_frame == INVALID_FRAME && target_speed) {
    enemy->cur_frame = 0;
    add_timer(0.016, st_enemy_walk_cycle, -1000, (void *) index);
  } else if (enemy->cur_frame != INVALID_FRAME && target_speed == 0.0) {
    enemy->cur_frame = INVALID_FRAME;
    update_timer_args(st_enemy_walk_cycle, (void *) index,
                      (void *) INVALID_INDEX);
  }
}

// ============================= STATION HELPERS =============================

void search_st_player(ST_ENEMY *enemy, size_t first_cd, size_t *player_cd,
                      size_t *to_player_cd) {
  vec3 st_player_pos = GLM_VEC3_ZERO_INIT;
  glm_vec3_copy(st_player.ent->translation, st_player_pos);

  typedef struct cell_data {
    size_t prev;
    char visited;
  } CELL_DATA;
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
  search_queue[0].prev = INVALID_INDEX;
  cell_data[first_cd].visited = 1;

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
      target = cur_cd;
      break;
    }
    cell_data[cur_cd].visited = 1;

    // Add children corridors to search if depth not exausted
    if (cur_depth == ST_ENEMY_SEARCH_DEPTH) {
      continue;
    }
    for (int i = 0; i < 4; i++) {
      cur_neighbor = cd_obs[cur_cd].neighbors[i];
      if (cur_neighbor == INVALID_INDEX || cell_data[cur_neighbor].visited) {
        continue;
      }

      search_queue[rear].cd = cd_obs[cur_cd].neighbors[i];
      search_queue[rear].depth = cur_depth + 1;
      cell_data[cd_obs[cur_cd].neighbors[i]].prev = cur_cd;
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
    while (cell_data[target].prev != first_cd &&
           cell_data[target].prev != INVALID_INDEX) {
      target = cell_data[target].prev;
    }
    *to_player_cd = target;
  }

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
    cur_neighbor = cd_obs[enemy_cd].neighbors[i];
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
  // Evasion cd is the neighbor index (0 - 3) of the enemy_cd which the enemy
  // is attempting to move away from
  int evasion_cd = 0;
  if (to_player[X] < 0.0) {
    evasion_cd = 1;
  } else if (to_player[Z] > 0.0) {
    evasion_cd = 2;
  } else if (to_player[Z] < 0.0) {
    evasion_cd = 3;
  }

  float enemy_dist = glm_vec3_distance(cd_obs[enemy_cd].ent->translation,
                                       cd_obs[player_cd].ent->translation);

  size_t ret = INVALID_INDEX;
  float cur_dist = 0.0;
  size_t cur_neighbor = 0;
  for (int i = 0; i < 4; i++) {
    cur_neighbor = cd_obs[enemy_cd].neighbors[i];
    if (i == evasion_cd || cur_neighbor == INVALID_INDEX) {
      continue;
    }
    cur_dist = glm_vec3_distance(cd_obs[cur_neighbor].ent->translation,
                                 cd_obs[player_cd].ent->translation);
    if (cur_dist < enemy_dist) {
      continue;
    }

    if ((i == 0 && evasion_cd == 1) || (i == 1 && evasion_cd == 0) ||
        (i == 2 && evasion_cd == 3) || (i == 3 && evasion_cd == 2)) {
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

  size_t cur = INVALID_INDEX;
  for (int i = 0; i < 4; i++) {
    cur = cd_obs[enemy_cd].neighbors[i];
    if (cur == INVALID_INDEX) {
      continue;
    }
    for (int j = 0; j < ST_ENEMY_SEARCH_DEPTH; j++) {
      if (cur == player_cd) {
        return 1;
      }
      cur = cd_obs[cur].neighbors[i];
      if (cur == INVALID_INDEX) {
        break;
      }
    }
  }

  return 0;
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
