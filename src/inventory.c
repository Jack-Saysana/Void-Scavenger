#include <inventory.h>

void pickup_item() {
  I_SLOT *slot = inv_first_avail();
  if (!slot) {
    // TODO: add popup prompt
    printf("INVENTORY IS FULL\n");
    return;
  }

  /* Finds the part which is closet to the player */
  COLLISION *col = NULL;
  size_t buff_size = sim_get_nearby(physics_sim, &col,
                     st_player.ent->translation, 5.0);
  if (!buff_size) {
    return;
  }

  SOBJ *temp = NULL;
  ST_ITEM *part = NULL;
  for (size_t i = 0; i < buff_size; i++) {
    temp = object_wrappers + (size_t) col[i].b_ent->data;
    if (temp->type != ITEM_OBJ) {
      continue;
    }
    part = items + (size_t) temp->data;
    break;
  }
  if (!part) {
    return;
  }

  /* Copy over union data for part data */
  memcpy(&(slot->data), &(part->enhancements), sizeof(part->enhancements));
  slot->rarity = part->rarity;

  /* Copy over part information (translate between part and inventory types) */
  slot->weapon_type = NOT_WEAPON;
  switch (part->type) {
    case PART_REACTOR:
      slot->type = I_SLOT_REACTOR;
      break;
    case PART_HULL:
      slot->type = I_SLOT_HULL;
      break;
    case PART_SHIELD:
      slot->type = I_SLOT_SHIELD;
      break;
    case PART_WEAPON_BALLISTIC:
      slot->weapon_type = W_BALLISTIC;
    case PART_WEAPON_LASER:
      slot->weapon_type = LASER;
    case PART_WEAPON_PLASMA:
      slot->weapon_type = PLASMA;
      slot->type = I_SLOT_WEAPON;
      break;
    case PART_WING:
      slot->type = I_SLOT_WING;
      break;
    case PART_THRUSTER:
      slot->type = I_SLOT_THRUSTER;
      break;
  }

  /* Trigger removal from simulation */
  temp->to_delete = 1;
}

void drop_item(size_t inv_slot) {
  size_t index = restore_item(inv_slot);
  if (index == INVALID_INDEX) {
    fprintf(stderr, "Failed to restore item!\n");
    return;
  }
  if (item_insert_sim(index) == -1) {
    fprintf(stderr, "Failed to insert item into simulation!\n");
    exit(0);
  } 

  /* Reset inventory slot */
  I_SLOT *slot = st_player.inventory + inv_slot;
  slot->type = I_SLOT_EMPTY;
  memset(&slot->data, 0, sizeof(slot->data));
  slot->weapon_type = NOT_WEAPON;
  slot->rarity = WHITE_RARITY;
}

I_SLOT *inv_first_avail() {
  for (size_t i = 0; i < i_size; i++) {
    if (st_player.inventory[i].type == I_SLOT_EMPTY) {
      return st_player.inventory + i;
    }
  }
  return NULL;
}

size_t find_first_filled() {
  for (size_t i = 0; i < i_size; i++) {
    if (st_player.inventory[i].type != I_SLOT_EMPTY) {
      return i;
    }
  }
  return INVALID_INDEX;
}
