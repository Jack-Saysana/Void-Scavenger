#include <ship_parts.h>

// ==================== BUFFER INITIALIZATION AND CLEANUP ====================

int init_station_ship_parts_buffer() {
  st_sp = malloc(sizeof(ST_SP) * BUFF_STARTING_LEN);
  if (st_sp == NULL) {
    fprintf(stderr, "Error: Unable to allocate station ship parts buffer\n");
    return -1;
  }
  num_ship_parts = 0;
  sp_buff_len = BUFF_STARTING_LEN;

  return 0;
}

void free_station_ship_parts_buffer() {
  free(st_sp);
  st_sp = NULL;
}

// ================== INDIVIDUAL INITIALIZATION AND CLEANUP ==================

size_t init_station_ship_part(int type, int rarity, vec3 pos, vec3 scale, 
                              versor rotation, float mass) {
  if (st_sp == NULL) {
    fprintf(stderr, "Error: Inserting into a deallocated space part buffer\n");
    return INVALID_INDEX;
  }

  ST_SP *part = st_sp + num_ship_parts;
  part->ent = init_station_ship_part_ent(type);
  if (part->ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate ship part entity\n");
    return INVALID_INDEX;
  }

  part->wrapper_offset = init_wrapper(STATION_SP_OBJ, part->ent,
                                           (void *) num_ship_parts);
  if (part->wrapper_offset == INVALID_INDEX) {
    return -1;
  }

  set_enhancements(part, type, rarity);

  glm_vec3_copy((vec3) { 0.0, 0.0, 0.0 }, part->ent->ang_velocity);
  glm_vec3_copy((vec3) { 0.0, 0.01, 0.0 }, part->ent->velocity);
  part->ent->rotation[0] = rotation[0];
  part->ent->rotation[1] = rotation[1];
  part->ent->rotation[2] = rotation[2];
  part->ent->rotation[3] = rotation[3];
  glm_vec3_copy(pos, part->ent->translation);
  glm_vec3_copy(scale, part->ent->scale);
  part->ent->inv_mass = 1.0 / mass;

  num_ship_parts++;
  if (num_ship_parts == sp_buff_len) {
    int status = double_buffer((void **) &st_sp, &sp_buff_len,
                               sizeof(ST_SP));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate space parts buffer\n");
      return INVALID_INDEX;
    }
  }

  return num_ship_parts - 1;
}

int station_ship_part_insert_sim(size_t index) {
  int status = sim_add_entity(physics_sim, st_sp[index].ent,
                              ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(combat_sim, st_sp[index].ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, st_sp[index].ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(event_sim, st_sp[index].ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  return 0;
}

void delete_station_ship_part(size_t index) {
  if (index >= num_ship_parts) {
    return;
  }

  free_entity(st_sp[index].ent);
  delete_wrapper(st_sp[index].wrapper_offset);

  num_ship_parts--;

  st_sp[index] = st_sp[num_ship_parts];
  SOBJ *wrapper = object_wrappers + st_sp[index].wrapper_offset;
  wrapper->data = (void *) index;
}

void station_ship_part_remove_sim(size_t index) {
  sim_remove_entity(physics_sim, st_sp[index].ent);
  sim_remove_entity(combat_sim, st_sp[index].ent);
  sim_remove_entity(render_sim, st_sp[index].ent);
  sim_remove_entity(event_sim, st_sp[index].ent);
}

void sim_refresh_station_ship_part(size_t index) {
  ST_SP *obs = st_sp + index;
  COLLIDER *cur_col = NULL;
  for (size_t i = 0; i < obs->ent->model->num_colliders; i++) {
    cur_col = obs->ent->model->colliders + i;
    if (cur_col->category == DEFAULT) {
      refresh_collider(physics_sim, obs->ent, i);
      refresh_collider(combat_sim, obs->ent, i);
      refresh_collider(render_sim, obs->ent, i);
      refresh_collider(event_sim, obs->ent, i);
    }
  }
}

// ================================= HELPERS =================================

/*
  Sets the changes to which the part will have on the ship. The numbers
  which are assigned are designed to be OFFSETS, not actual replacements.
*/
void set_enhancements(ST_SP *part, int type, int rarity) {
  if (part) {
    memset(&part->enhancements, 0, sizeof(part->enhancements));
    part->type = type;
    part->rarity = rarity;
    if (type == TYPE_ENGINE) {
      part->enhancements.thruster.max_vel = S_BASE_VEL;
      part->enhancements.thruster.max_accel = S_BASE_ACCEL;
      part->enhancements.thruster.max_power_draw = S_BASE_PWR_DRAW;
      if (rarity == BLUE_RARITY) {
        part->enhancements.thruster.max_vel *= BLUE_DIFF;
        part->enhancements.thruster.max_accel *= BLUE_DIFF;
        part->enhancements.thruster.max_power_draw *= BLUE_DIFF;
      } else if (rarity == GREEN_RARITY) {
        part->enhancements.thruster.max_vel *= GREEN_DIFF;
        part->enhancements.thruster.max_accel *= GREEN_DIFF;
        part->enhancements.thruster.max_power_draw *= GREEN_DIFF;
      } else if (rarity == PURPLE_RARITY) {
        part->enhancements.thruster.max_vel *= PURPLE_DIFF;
        part->enhancements.thruster.max_accel *= PURPLE_DIFF;
        part->enhancements.thruster.max_power_draw *= PURPLE_DIFF;
      } else if (rarity == GOLD_RARITY) {
        part->enhancements.thruster.max_vel *= GOLD_DIFF;
        part->enhancements.thruster.max_accel *= GOLD_DIFF;
        part->enhancements.thruster.max_power_draw *= GOLD_DIFF;
      }
    } else if (type == TYPE_HULL) {
      part->enhancements.hull.max_health = S_BASE_HEALTH;
      if (rarity == BLUE_RARITY) {
        part->enhancements.hull.max_health *= BLUE_DIFF;
      } else if (rarity == GREEN_RARITY) {
        part->enhancements.hull.max_health *= GREEN_DIFF;
      } else if (rarity == PURPLE_RARITY) {
        part->enhancements.hull.max_health *= PURPLE_DIFF;
      } else if (rarity == GOLD_RARITY) {
        part->enhancements.hull.max_health *= GOLD_DIFF;
      }
    } else if (type == TYPE_REACTOR) {
      part->enhancements.reactor.max_output = S_BASE_PWR_OUTPUT;
      if (rarity == BLUE_RARITY) {
        part->enhancements.reactor.max_output *= BLUE_DIFF;
      } else if (rarity == GREEN_RARITY) {
        part->enhancements.reactor.max_output *= GREEN_DIFF;
      } else if (rarity == PURPLE_RARITY) {
        part->enhancements.reactor.max_output *= PURPLE_DIFF;
      } else if (rarity == GOLD_RARITY) {
        part->enhancements.reactor.max_output *= GOLD_DIFF;
      }
    } else if (type == TYPE_SHIELD) {
      part->enhancements.shield.max_shield = S_BASE_SHIELD;
      part->enhancements.shield.recharge_rate = S_BASE_SHIELD_RECHARGE;
      part->enhancements.shield.recharge_delay = S_BASE_SHIELD_DELAY;
      part->enhancements.shield.power_draw = S_BASE_PWR_DRAW;
      if (rarity == BLUE_RARITY) {
        part->enhancements.shield.max_shield *= BLUE_DIFF;
        part->enhancements.shield.recharge_rate *= BLUE_DIFF;
        part->enhancements.shield.recharge_delay *= BLUE_DIFF;
        part->enhancements.shield.power_draw *= BLUE_DIFF;
      } else if (rarity == GREEN_RARITY) {
        part->enhancements.shield.max_shield *= GREEN_DIFF;
        part->enhancements.shield.recharge_rate *= GREEN_DIFF;
        part->enhancements.shield.recharge_delay *= GREEN_DIFF;
        part->enhancements.shield.power_draw *= GREEN_DIFF;
      } else if (rarity == PURPLE_RARITY) {
        part->enhancements.shield.max_shield *= PURPLE_DIFF;
        part->enhancements.shield.recharge_rate *= PURPLE_DIFF;
        part->enhancements.shield.recharge_delay *= PURPLE_DIFF;
        part->enhancements.shield.power_draw *= PURPLE_DIFF;
      } else if (rarity == GOLD_RARITY) {
        part->enhancements.shield.max_shield *= GOLD_DIFF;
        part->enhancements.shield.recharge_rate *= GOLD_DIFF;
        part->enhancements.shield.recharge_delay *= GOLD_DIFF;
        part->enhancements.shield.power_draw *= GOLD_DIFF;
      }
    } else if (type == TYPE_WEAPON_BALLISTIC) {
      /* TODO: Fill in with ballistic specific changes */
      part->enhancements.weapon.type = BALLISTIC;
      part->enhancements.weapon.damage = S_BASE_DAMAGE;
      part->enhancements.weapon.fire_rate = S_BASE_FIRERATE;
      part->enhancements.weapon.max_power_draw = S_BASE_PWR_DRAW;
      part->enhancements.weapon.proj_speed = S_BASE_PROJ_SPEED;
      part->enhancements.weapon.range = S_BASE_RANGE;
      if (rarity == BLUE_RARITY) {
        part->enhancements.weapon.damage *= BLUE_DIFF;
        part->enhancements.weapon.fire_rate *= BLUE_DIFF;
        part->enhancements.weapon.max_power_draw *= BLUE_DIFF;
        part->enhancements.weapon.proj_speed *= BLUE_DIFF;
        part->enhancements.weapon.range *= BLUE_DIFF;
      } else if (rarity == GREEN_RARITY) {
        part->enhancements.weapon.damage *= GREEN_DIFF;
        part->enhancements.weapon.fire_rate *= GREEN_DIFF;
        part->enhancements.weapon.max_power_draw *= GREEN_DIFF;
        part->enhancements.weapon.proj_speed *= GREEN_DIFF;
        part->enhancements.weapon.range *= GREEN_DIFF;
      } else if (rarity == PURPLE_RARITY) {
        part->enhancements.weapon.damage *= PURPLE_DIFF;
        part->enhancements.weapon.fire_rate *= PURPLE_DIFF;
        part->enhancements.weapon.max_power_draw *= PURPLE_DIFF;
        part->enhancements.weapon.proj_speed *= PURPLE_DIFF;
        part->enhancements.weapon.range *= PURPLE_DIFF;
      } else if (rarity == GOLD_RARITY) {
        part->enhancements.weapon.damage *= GOLD_DIFF;
        part->enhancements.weapon.fire_rate *= GOLD_DIFF;
        part->enhancements.weapon.max_power_draw *= GOLD_DIFF;
        part->enhancements.weapon.proj_speed *= GOLD_DIFF;
        part->enhancements.weapon.range *= GOLD_DIFF;
      }
    } else if (type == TYPE_WEAPON_LASER) {
      /* TODO: Fill in with laser specific changes */
      part->enhancements.weapon.type = LASER;
      part->enhancements.weapon.damage = S_BASE_DAMAGE;
      part->enhancements.weapon.fire_rate = S_BASE_FIRERATE;
      part->enhancements.weapon.max_power_draw = S_BASE_PWR_DRAW;
      part->enhancements.weapon.proj_speed = S_BASE_PROJ_SPEED;
      part->enhancements.weapon.range = S_BASE_RANGE;
      if (rarity == BLUE_RARITY) {
        part->enhancements.weapon.damage *= BLUE_DIFF;
        part->enhancements.weapon.fire_rate *= BLUE_DIFF;
        part->enhancements.weapon.max_power_draw *= BLUE_DIFF;
        part->enhancements.weapon.proj_speed *= BLUE_DIFF;
        part->enhancements.weapon.range *= BLUE_DIFF;
      } else if (rarity == GREEN_RARITY) {
        part->enhancements.weapon.damage *= GREEN_DIFF;
        part->enhancements.weapon.fire_rate *= GREEN_DIFF;
        part->enhancements.weapon.max_power_draw *= GREEN_DIFF;
        part->enhancements.weapon.proj_speed *= GREEN_DIFF;
        part->enhancements.weapon.range *= GREEN_DIFF;
      } else if (rarity == PURPLE_RARITY) {
        part->enhancements.weapon.damage *= PURPLE_DIFF;
        part->enhancements.weapon.fire_rate *= PURPLE_DIFF;
        part->enhancements.weapon.max_power_draw *= PURPLE_DIFF;
        part->enhancements.weapon.proj_speed *= PURPLE_DIFF;
        part->enhancements.weapon.range *= PURPLE_DIFF;
      } else if (rarity == GOLD_RARITY) {
        part->enhancements.weapon.damage *= GOLD_DIFF;
        part->enhancements.weapon.fire_rate *= GOLD_DIFF;
        part->enhancements.weapon.max_power_draw *= GOLD_DIFF;
        part->enhancements.weapon.proj_speed *= GOLD_DIFF;
        part->enhancements.weapon.range *= GOLD_DIFF;
      }

    } else if (type == TYPE_WEAPON_PLASMA) {
      /* TODO: Fill in with plasma specific changes */
      part->enhancements.weapon.type = PLASMA;
      part->enhancements.weapon.damage = S_BASE_DAMAGE;
      part->enhancements.weapon.fire_rate = S_BASE_FIRERATE;
      part->enhancements.weapon.max_power_draw = S_BASE_PWR_DRAW;
      part->enhancements.weapon.proj_speed = S_BASE_PROJ_SPEED;
      part->enhancements.weapon.range = S_BASE_RANGE;
      if (rarity == BLUE_RARITY) {
        part->enhancements.weapon.damage *= BLUE_DIFF;
        part->enhancements.weapon.fire_rate *= BLUE_DIFF;
        part->enhancements.weapon.max_power_draw *= BLUE_DIFF;
        part->enhancements.weapon.proj_speed *= BLUE_DIFF;
        part->enhancements.weapon.range *= BLUE_DIFF;
      } else if (rarity == GREEN_RARITY) {
        part->enhancements.weapon.damage *= GREEN_DIFF;
        part->enhancements.weapon.fire_rate *= GREEN_DIFF;
        part->enhancements.weapon.max_power_draw *= GREEN_DIFF;
        part->enhancements.weapon.proj_speed *= GREEN_DIFF;
        part->enhancements.weapon.range *= GREEN_DIFF;
      } else if (rarity == PURPLE_RARITY) {
        part->enhancements.weapon.damage *= PURPLE_DIFF;
        part->enhancements.weapon.fire_rate *= PURPLE_DIFF;
        part->enhancements.weapon.max_power_draw *= PURPLE_DIFF;
        part->enhancements.weapon.proj_speed *= PURPLE_DIFF;
        part->enhancements.weapon.range *= PURPLE_DIFF;
      } else if (rarity == GOLD_RARITY) {
        part->enhancements.weapon.damage *= GOLD_DIFF;
        part->enhancements.weapon.fire_rate *= GOLD_DIFF;
        part->enhancements.weapon.max_power_draw *= GOLD_DIFF;
        part->enhancements.weapon.proj_speed *= GOLD_DIFF;
        part->enhancements.weapon.range *= GOLD_DIFF;
      }
    } else if (type == TYPE_WING) {
      part->enhancements.wing.max_ang_vel = S_BASE_ANG_VEL;
      part->enhancements.wing.max_ang_accel = S_BASE_ANG_ACCEL;
      if (rarity == BLUE_RARITY) {
        part->enhancements.wing.max_ang_vel *= BLUE_DIFF;
        part->enhancements.wing.max_ang_accel *= BLUE_DIFF;
      } else if (rarity == GREEN_RARITY) {
        part->enhancements.wing.max_ang_vel *= GREEN_DIFF;
        part->enhancements.wing.max_ang_accel *= GREEN_DIFF; 
      } else if (rarity == PURPLE_RARITY) {
        part->enhancements.wing.max_ang_vel *= PURPLE_DIFF;
        part->enhancements.wing.max_ang_accel *= PURPLE_DIFF;
      } else if (rarity == GOLD_RARITY) {
        part->enhancements.wing.max_ang_vel *= GOLD_DIFF;
        part->enhancements.wing.max_ang_accel *= GOLD_DIFF;
      }
    } else {
      fprintf(stderr, "Trying to add enhancement to unknown part type (%d)!\n",
              type);
      return;
    }
  } else {
    fprintf(stderr, "Trying to add enhancements to NULL ship_part (%d)!\n",
            type);
    return;
  }
}
