#include <obj_wrapper.h>

/*                                  OBJ_WRAPPER.C

  Responsible for managing the global buffer of game object wrappers by
  defining helper functions used to initialize, add and remove from the buffer.

*/

// ==================== BUFFER INITIALIZATION AND CLEANUP ====================

int init_wrapper_buffer() {
  object_wrappers = malloc(sizeof(SOBJ) * BUFF_STARTING_LEN);
  if (object_wrappers == NULL) {
    fprintf(stderr, "Error: Unable to allocate object wrapper buffer\n");
    return -1;
  }
  num_wrappers = 0;
  wrapper_buff_size = BUFF_STARTING_LEN;

  return 0;
}

void free_wrapper_buffer() {
  free(object_wrappers);
  num_wrappers = 0;
  wrapper_buff_size = 0;
}

// =========================== WRAPPER MANIPLATION ===========================

size_t init_wrapper(SOBJ_T type, ENTITY *entity, void *data) {
  if (object_wrappers == NULL) {
    fprintf(stderr, "Error: Inserting into deallocated wrapper buffer\n");
    return INVALID_INDEX;
  }

  object_wrappers[num_wrappers].type = type;
  object_wrappers[num_wrappers].entity = entity;
  object_wrappers[num_wrappers].data = data;
  object_wrappers[num_wrappers].to_delete = 0;
  entity->data = (void *) num_wrappers;
  num_wrappers++;
  if (num_wrappers == wrapper_buff_size) {
    int status = double_buffer((void **) &object_wrappers, &wrapper_buff_size,
                               sizeof(SOBJ));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate object wrapper buffer\n");
      return INVALID_INDEX;
    }
  }
  return num_wrappers - 1;
}

void delete_wrapper(size_t index) {
  num_wrappers--;
  if (num_wrappers == index) {
    return;
  }

  object_wrappers[index] = object_wrappers[num_wrappers];
  SOBJ *old_wrapper = object_wrappers + num_wrappers;
  old_wrapper->entity->data = (void *) index;
  if (old_wrapper->type == PLAYER_OBJ) {
    st_player.wrapper_offset = index;
  } else if (old_wrapper->type == PLAYER_SHIP_OBJ) {
    player_ship.wrapper_offset = index;
  } else if (old_wrapper->type == ENEMY_OBJ) {
    st_enemies[(size_t) old_wrapper->data].wrapper_offset = index;
  } else if (old_wrapper->type == ENEMY_SHIP_OBJ) {
    sp_enemies[(size_t) old_wrapper->data].wrapper_offset = index;
  } else if (old_wrapper->type == PROJ_OBJ) {
    projectiles[(size_t) old_wrapper->data].wrapper_offset = index;
  } else if (old_wrapper->type == ITEM_OBJ) {
    items[(size_t) old_wrapper->data].wrapper_offset = index;
  } else if (old_wrapper->type == OBSTACLE_OBJ) {
    if (mode == SPACE) {
      sp_obs[(size_t) old_wrapper->data].wrapper_offset = index;
    } else {
      st_obs[(size_t) old_wrapper->data].wrapper_offset = index;
    }
  } else if (old_wrapper->type == CORRIDOR_OBJ) {
    cd_obs[(size_t) old_wrapper->data].wrapper_offset = index;
  }
}
