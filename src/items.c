#include <items.h>

// ==================== BUFFER INITIALIZATION AND CLEANUP ====================

int init_items_buffer() {
  items = malloc(sizeof(ST_ITEM) * BUFF_STARTING_LEN);
  if (items == NULL) {
    fprintf(stderr, "Error: Unable to allocate items buffer\n");
    return -1;
  }
  num_items = 0;
  item_buff_len = BUFF_STARTING_LEN;

  return 0;
}

void free_items_buffer() {
  free(items);
  items = NULL;
}

// ================== INDIVIDUAL INITIALIZATION AND CLEANUP ==================

size_t init_item(int type, int rarity, vec3 pos, vec3 scale,
                              versor rotation, float mass) {
  if (items == NULL) {
    fprintf(stderr, "Error: Inserting into a deallocated item buffer\n");
    return INVALID_INDEX;
  }

  ST_ITEM *part = items + num_items;
  part->type = type;
  
  part->ent = init_item_ent(part->type);
  if (part->ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate item entity\n");
    return INVALID_INDEX;
  }

  part->wrapper_offset = init_wrapper(ITEM_OBJ, part->ent,
                                           (void *) num_items);
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

  num_items++;
  if (num_items == item_buff_len) {
    int status = double_buffer((void **) &items, &item_buff_len,
                               sizeof(ST_ITEM));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate items buffer\n");
      return INVALID_INDEX;
    }
  }

  return num_items - 1;
}

size_t restore_item(size_t inv_slot_num) {
  if (inv_slot_num > i_size) {
    fprintf(stderr, "Trying to restore item from inventory that doens't exist");
    return INVALID_INDEX;
  }

  if (!items) {
    fprintf(stderr, "Trying to restore item into an unallocated item buffer");
    return INVALID_INDEX;
  }

  I_SLOT *slot = st_player.inventory + inv_slot_num;
  if (slot->type == I_SLOT_EMPTY) {
    return INVALID_INDEX;
  }

  ST_ITEM *part = items + num_items;

  /* Translate from slot type to part type */
  if (slot->type == I_SLOT_REACTOR) {
    part->type = PART_REACTOR;
  } else if (slot->type == I_SLOT_HULL) {
    part->type = PART_HULL;
  } else if (slot->type == I_SLOT_SHIELD) {
    part->type = PART_SHIELD;
  } else if (slot->type == I_SLOT_WEAPON) {
    if (slot->weapon_type == W_LASER) {
      part->type = PART_WEAPON_LASER;
    } else if (slot->weapon_type == W_BALLISTIC) {
      part->type = PART_WEAPON_BALLISTIC;
    } else if (slot->weapon_type == W_PLASMA) {
      part->type = PART_WEAPON_PLASMA;
    }
  } else if (slot->type == I_SLOT_THRUSTER) {
    part->type = PART_THRUSTER;
  } else if (slot->type == I_SLOT_WING) {
    part->type = PART_WING;
  }

  part->ent = init_item_ent(part->type);
  if (part->ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate item entity\n");
    return INVALID_INDEX;
  }

  part->wrapper_offset = init_wrapper(ITEM_OBJ, part->ent,
                                           (void *) num_items);
  if (part->wrapper_offset == INVALID_INDEX) {
    return -1;
  }
  /* Copy over part data */
  memcpy(&part->enhancements, &slot->data, sizeof(slot->data));
  part->rarity = slot->rarity;

  glm_vec3_copy((vec3) { 0.0, 0.0, 0.0 }, part->ent->ang_velocity);
  glm_vec3_copy((vec3) { 0.0, 0.01, 0.0 }, part->ent->velocity);
  part->ent->rotation[0] = 0.0;
  part->ent->rotation[1] = 0.0;
  part->ent->rotation[2] = 0.0;
  part->ent->rotation[3] = 0.0;
  glm_vec3_copy(st_player.ent->translation, part->ent->translation);
  glm_vec3_copy(GLM_VEC3_ONE, part->ent->scale);
  part->ent->inv_mass = 1.0 / (2.0 * (gen_rand_float(3.0) + 1.0));

  num_items++;
  if (num_items == item_buff_len) {
    int status = double_buffer((void **) &items, &item_buff_len,
                               sizeof(ST_ITEM));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate items buffer\n");
      return INVALID_INDEX;
    }
  }

  return num_items - 1;
}

int item_insert_sim(size_t index) {
  int status = sim_add_entity(physics_sim, items[index].ent,
                              ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(combat_sim, items[index].ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(render_sim, items[index].ent, ALLOW_DEFAULT);
  if (status) {
    return -1;
  }

  status = sim_add_entity(event_sim, items[index].ent, ALLOW_HURT_BOXES);
  if (status) {
    return -1;
  }

  return 0;
}

void delete_item(size_t index) {
  if (index >= num_items) {
    return;
  }

  free_entity(items[index].ent);
  delete_wrapper(items[index].wrapper_offset);

  num_items--;

  items[index] = items[num_items];
  SOBJ *wrapper = object_wrappers + items[index].wrapper_offset;
  wrapper->data = (void *) index;
}

void item_remove_sim(size_t index) {
  sim_remove_entity(physics_sim, items[index].ent);
  sim_remove_entity(combat_sim, items[index].ent);
  sim_remove_entity(render_sim, items[index].ent);
  sim_remove_entity(event_sim, items[index].ent);
}

void sim_refresh_item(size_t index) {
  ST_ITEM *obs = items + index;
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

void set_enhancements(ST_ITEM *part, int type, int rarity) {
  if (part) {
    memset(&part->enhancements, 0, sizeof(part->enhancements));
    part->type = type;
    part->rarity = rarity;

    /* Creates a range of plus or minus 2.5% which the modifier can add */
    // float randomness = gen_rand_float(0.5) + 0.975;
    // float b_offset = randomness * BLUE_DIFF;
    // float g_offset = randomness * GREEN_DIFF;
    // float p_offset = randomness * PURPLE_DIFF;
    // float gd_offset = randomness * GOLD_DIFF;

    float modifier_pool = 0;
    if (rarity == WHITE_RARITY) {
      modifier_pool = WHITE_POOL;
    } else if (rarity == BLUE_RARITY) {
      modifier_pool = BLUE_POOL;
    } else if (rarity == GREEN_RARITY) {
      modifier_pool = GREEN_POOL;
    } else if (rarity == PURPLE_RARITY) {
      modifier_pool = PURPLE_POOL;
    } else if (rarity == GOLD_RARITY) {
      modifier_pool = GOLD_POOL;
    }
    float pick[MAX_NUM_STATS];
    if (type == TYPE_THRUSTER) {
      modifier_pool = modifier_pool * THRUSTER_NUM_STATS; //3
      distribute_picks(THRUSTER_NUM_STATS, modifier_pool, pick);
      part->enhancements.thruster.max_vel = THRUSTER_MAX_VEL_MIN 
        + (pick[0] * THRUSTER_MAX_VEL_MODIFIER);
      part->enhancements.thruster.max_accel = THRUSTER_MAX_ACCEL_MIN
        + (pick[1] * THRUSTER_MAX_ACCEL_MODIFIER);
      part->enhancements.thruster.max_power_draw = THRUSTER_MAX_POWER_DRAW_MIN 
        + (pick[2] * THRUSTER_MAX_POWER_DRAW_MODIFIER);
      if (part->enhancements.thruster.max_power_draw < THRUSTER_PWR_DRAW_CAP) {
        float rebate = THRUSTER_PWR_DRAW_CAP -  
          part->enhancements.thruster.max_power_draw;
        part->enhancements.thruster.max_power_draw = THRUSTER_PWR_DRAW_CAP;
        rebate = rebate / THRUSTER_MAX_POWER_DRAW_MODIFIER;
        rebate = fabs(rebate);
        distribute_picks(THRUSTER_NUM_STATS - 1, rebate, pick);
        part->enhancements.thruster.max_vel += 
          (pick[0] * THRUSTER_MAX_VEL_MODIFIER);
        part->enhancements.thruster.max_accel += 
          (pick[1] * THRUSTER_MAX_ACCEL_MODIFIER);
      }
    } else if (type == TYPE_HULL) {
      modifier_pool = modifier_pool * HULL_NUM_STATS; //1
      float pick1 = modifier_pool;
      part->enhancements.hull.max_health = HULL_HEALTH_MIN 
        + (pick1 * HULL_HEALTH_MODIFIER);
    } else if (type == TYPE_REACTOR) {
      modifier_pool = modifier_pool * REACTOR_NUM_STATS; //2
      distribute_picks(REACTOR_NUM_STATS, modifier_pool, pick);
      part->enhancements.reactor.max_output = REACTOR_MAX_POWER_OUTPUT_MIN 
        + (pick[0] * REACTOR_MAX_POWER_OUTPUT_MODIFIER);
      part->enhancements.reactor.recharge_rate = REACTOR_RECHARGE_RATE_MIN
        + (pick[1] * REACTOR_RECHARGE_RATE_MODIFIER);
    } else if (type == TYPE_SHIELD) {
      modifier_pool = modifier_pool * SHIELD_NUM_STATS; //4
      distribute_picks(SHIELD_NUM_STATS, modifier_pool, pick);
      part->enhancements.shield.max_shield = SHIELD_MAX_SHIELD_MIN
        + (pick[0] * SHIELD_MAX_SHIELD_MODIFIER);
      part->enhancements.shield.recharge_rate = SHIELD_RECHARGE_RATE_MIN
        + (pick[1] * SHIELD_RECHARGE_RATE_MODIFIER);
      part->enhancements.shield.recharge_delay = SHIELD_RECHARGE_DELAY_MIN 
        + (pick[2] * SHIELD_RECHARGE_DELAY_MODIFIER);
      part->enhancements.shield.power_draw = SHIELD_POWER_DRAW_MIN 
        + (pick[3] * SHIELD_POWER_DRAW_MODIFIER);
      if(part->enhancements.shield.recharge_delay < SHIELD_RECHARGE_DELAY_CAP) {
        float rebate =  SHIELD_RECHARGE_DELAY_CAP - 
            part->enhancements.shield.recharge_delay;
        part->enhancements.shield.recharge_delay = SHIELD_RECHARGE_DELAY_CAP;
        rebate = rebate / SHIELD_RECHARGE_DELAY_MODIFIER;
        rebate = fabs(rebate);
        distribute_picks(SHIELD_NUM_STATS - 1, rebate, pick);
        part->enhancements.shield.max_shield += 
            (pick[0] * SHIELD_MAX_SHIELD_MODIFIER);
        part->enhancements.shield.recharge_rate += 
            (pick[1] * SHIELD_RECHARGE_RATE_MODIFIER);
        part->enhancements.shield.power_draw += 
            (pick[2] * SHIELD_POWER_DRAW_MODIFIER); 
      }
      if (part->enhancements.shield.power_draw < SHIELD_PWR_DRAW_CAP) {
        float rebate = SHIELD_PWR_DRAW_CAP - 
            part->enhancements.shield.power_draw;
        part->enhancements.shield.power_draw = SHIELD_PWR_DRAW_CAP;
        rebate = rebate / SHIELD_POWER_DRAW_MODIFIER;
        rebate = fabs(rebate);
        distribute_picks(SHIELD_NUM_STATS - 2, rebate, pick);
        part->enhancements.shield.max_shield += 
            (pick[0] * SHIELD_MAX_SHIELD_MODIFIER);
        part->enhancements.shield.recharge_rate += 
            (pick[1] * SHIELD_RECHARGE_RATE_MODIFIER);
      }
    } else if (type == TYPE_WEAPON_BALLISTIC || type == TYPE_WEAPON_LASER 
               || type == TYPE_WEAPON_PLASMA) {
      modifier_pool = modifier_pool * WEAPON_NUM_STATS; //7
      distribute_picks(WEAPON_NUM_STATS, modifier_pool, pick);
      part->enhancements.weapon.damage = WEAPON_DAMAGE_MIN
        + (pick[0] * WEAPON_DAMAGE_MODIFIER);
      if (type == TYPE_WEAPON_LASER) {
        part->enhancements.weapon.fire_rate = WEAPON_FIRE_RATE_MIN_LASER
        + (pick[1] * WEAPON_FIRE_RATE_MODIFIER);
        part->enhancements.weapon.type = LASER;
      } else {
        part->enhancements.weapon.fire_rate = WEAPON_FIRE_RATE_MIN
        + (pick[1] * WEAPON_FIRE_RATE_MODIFIER);
        if (type == TYPE_WEAPON_BALLISTIC) {
          part->enhancements.weapon.type = BALLISTIC;
        } else {
          part->enhancements.weapon.type = PLASMA;
        }
      }
      part->enhancements.weapon.max_power_draw = WEAPON_POWER_DRAW_MIN 
        + (pick[2] * WEAPON_POWER_DRAW_MODIFIER);
      part->enhancements.weapon.proj_speed = WEAPON_PROJ_SPEED_MIN
        + (pick[3] * WEAPON_PROJ_SPEED_MODIFIER);
      part->enhancements.weapon.range = WEAPON_RANGE_MIN
        + (pick[4] * WEAPON_RANGE_MODIFIER);
      part->enhancements.weapon.bullet_size = WEAPON_BULLET_SIZE_MIN
        + (pick[5] * WEAPON_BULLET_SIZE_MODIFIER);
      part->enhancements.weapon.num_barrels = WEAPON_NUM_BARRELS_MIN
        + (pick[6] * WEAPON_NUM_BARRELS_MODIFIER);
      if (part->enhancements.weapon.num_barrels > WEAPON_NUM_BARRELS_CAP) {
        float rebate = (float)part->enhancements.weapon.num_barrels - 
            WEAPON_NUM_BARRELS_CAP;
        part->enhancements.weapon.num_barrels = (int)WEAPON_NUM_BARRELS_CAP;
        rebate = rebate / WEAPON_NUM_BARRELS_MODIFIER;
        distribute_picks(WEAPON_NUM_STATS - 1, rebate, pick);
        part->enhancements.weapon.damage += (pick[0] * WEAPON_DAMAGE_MODIFIER);
        part->enhancements.weapon.max_power_draw += 
            (pick[1] * WEAPON_POWER_DRAW_MODIFIER);
        part->enhancements.weapon.proj_speed += 
            (pick[2] * WEAPON_PROJ_SPEED_MODIFIER);
        part->enhancements.weapon.range += 
            (pick[3] * WEAPON_RANGE_MODIFIER);
        part->enhancements.weapon.bullet_size += 
            (pick[4] * WEAPON_BULLET_SIZE_MODIFIER);
        part->enhancements.weapon.fire_rate += 
            (pick[5] * WEAPON_FIRE_RATE_MODIFIER);
      }
      if (part->enhancements.weapon.fire_rate < WEAPON_FIRERATE_CAP) {
        float rebate =  WEAPON_FIRERATE_CAP - 
            part->enhancements.weapon.fire_rate;
        part->enhancements.weapon.fire_rate = WEAPON_FIRERATE_CAP;
        rebate = rebate / WEAPON_FIRE_RATE_MODIFIER;
        rebate = fabs(rebate);
        distribute_picks(WEAPON_NUM_STATS - 2, rebate, pick);
        part->enhancements.weapon.damage += (pick[0] * WEAPON_DAMAGE_MODIFIER);
        part->enhancements.weapon.max_power_draw += 
            (pick[1] * WEAPON_POWER_DRAW_MODIFIER);
        part->enhancements.weapon.proj_speed += 
            (pick[2] * WEAPON_PROJ_SPEED_MODIFIER);
        part->enhancements.weapon.range += 
            (pick[3] * WEAPON_RANGE_MODIFIER);
        part->enhancements.weapon.bullet_size += 
            (pick[4] * WEAPON_BULLET_SIZE_MODIFIER);
      }
      if (part->enhancements.weapon.max_power_draw < WEAPON_PWR_DRAW_CAP) {
        float rebate =  WEAPON_PWR_DRAW_CAP - 
            part->enhancements.weapon.max_power_draw;
        part->enhancements.weapon.max_power_draw = WEAPON_PWR_DRAW_CAP;
        rebate = rebate / WEAPON_POWER_DRAW_MODIFIER;
        rebate = fabs(rebate);
        distribute_picks(WEAPON_NUM_STATS - 3, rebate, pick);
        part->enhancements.weapon.damage += 
            (pick[0] * WEAPON_DAMAGE_MODIFIER);
        part->enhancements.weapon.proj_speed += 
            (pick[1] * WEAPON_PROJ_SPEED_MODIFIER);
        part->enhancements.weapon.range += 
            (pick[2] * WEAPON_RANGE_MODIFIER);
        part->enhancements.weapon.bullet_size += 
            (pick[3] * WEAPON_BULLET_SIZE_MODIFIER);
      }
    } else if (type == TYPE_WING) {
      modifier_pool = modifier_pool * WING_NUM_STATS; //2
      distribute_picks(WING_NUM_STATS, modifier_pool, pick);
      part->enhancements.wing.max_ang_vel = WING_ANG_VEL_MIN
        + (pick[0] * WING_ANG_VEL_MODIFIER);
      part->enhancements.reactor.recharge_rate = WING_ANG_ACCEL_MIN
        + (pick[1] * WING_ANG_ACCEL_MODIFIER);
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

void distribute_picks(int num_stats, float pool_size, float * pick) {
  float spot_picks[num_stats];
  for (int i = 0; i < num_stats - 1; i++) {
    spot_picks[i] = gen_rand_float(1000.0);
  }
  spot_picks[num_stats - 1] = 1000.0;
  int swapped = 0;
  for (int i = 0; i < num_stats - 1; i++) {
    swapped = 0;
    for (int j = 0; j < num_stats - i - 1; j++) {
      if (spot_picks[j] > spot_picks[j+1]) {
        float temp = spot_picks[j];
        spot_picks[j] = spot_picks[j+1];
        spot_picks[j+1] = temp;
        swapped = 1;
      }
    }
    if (swapped == 0) {
      break;
    }
  }
  float last_spot_pick = 0;
  for (int k = 0; k < num_stats; k++) {
    pick[k] = ((spot_picks[k] - last_spot_pick) / 1000.0) * pool_size;
    last_spot_pick = spot_picks[k];
  }
}

void populate_point_lights(unsigned int shader) {
  unsigned int num_pt_lights = min(num_items, MAX_NUM_PT_LIGHTS);
  glUseProgram(shader);
  set_uint("num_pt_lights", num_pt_lights, shader); 
  for (size_t i = 0; i < num_pt_lights; i++) {
    ST_ITEM *part = items + i;

    char struct_buff[32];
    char col_buff[64];
    char pos_buff[64];
    //char a_consts_buff[3][64];
    #ifdef __linux__
    sprintf(struct_buff, "light[%ld].", i);
    #else
    sprintf(struct_buff, "light[%lld].", i);
    #endif

    strncpy(col_buff, struct_buff, sizeof(col_buff));
    strncpy(pos_buff, struct_buff, sizeof(pos_buff));
    //strncpy(a_consts_buff[0], struct_buff, sizeof(a_consts_buff[0]));
    //strncpy(a_consts_buff[1], struct_buff, sizeof(a_consts_buff[1]));
    //strncpy(a_consts_buff[2], struct_buff, sizeof(a_consts_buff[2]));

    strncat(col_buff, "col", sizeof(col_buff) - 1);
    strncat(pos_buff, "pos", sizeof(pos_buff) - 1);
    //strncat(a_consts_buff[0], "a_consts[0]", sizeof(a_consts_buff[0]) - 1);
    //strncat(a_consts_buff[1], "a_consts[1]", sizeof(a_consts_buff[1]) - 1);
    //strncat(a_consts_buff[2], "a_consts[2]", sizeof(a_consts_buff[2]) - 1);

    if (part->rarity == WHITE_RARITY) {
      set_vec3(col_buff, WHITE_COL, shader);
    } else if (part->rarity == BLUE_RARITY) {
      set_vec3(col_buff, BLUE_COL, shader);
    } else if (part->rarity == GREEN_RARITY) {
      set_vec3(col_buff, GREEN_COL, shader);
    } else if (part->rarity == PURPLE_RARITY) {
      set_vec3(col_buff, PURPLE_COL, shader);
    } else if (part->rarity == GOLD_RARITY) {
      set_vec3(col_buff, GOLD_COL, shader);
    }
    
    set_vec3(pos_buff, part->ent->translation, shader);
    //set_float(a_consts_buff[0], ATTENUATION_STD, shader); 
    //set_float(a_consts_buff[1], ATTENUATION_LINEAR, shader); 
    //set_float(a_consts_buff[2], ATTENUATION_QUADRATIC, shader); 
  }
}
