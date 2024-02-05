#include <station.h>

/*                                  STATION.C

  Handles the functionality behind procdurally generating space stations for
  station mode. Also handles distribution of items and enemies.

*/

/* ==================== CORRIDOR BUFFER INITIALIZATION ===================== */

int init_corridor_buffer() {
  cd_obs = malloc(sizeof(CORRIDOR) * BUFF_STARTING_LEN);
  if (cd_obs == NULL) {
    fprintf(stderr, "Error: Unable to allocate projectile buffer\n");
    return -1;
  }
  num_corridors = 0;
  corridor_buff_len = BUFF_STARTING_LEN;

  return 0;
}

void free_corridor_buffer() {
  free(cd_obs);
}

/* ==================== CORRIDOR OBJECT INIT AND DELETE ==================== */

size_t init_corridor(vec3 pos, versor rotation, size_t type) {
  if (cd_obs == NULL) {
    fprintf(stderr, "Error: Inserting into a deallocated corridor buffer\n");
    return INVALID_INDEX;
  }

  CORRIDOR *corr = cd_obs + num_corridors;
  corr->ent = init_corridor_ent(type);
  if (corr->ent == NULL) {
    fprintf(stderr, "Error: Unable to allocate corridor entity\n");
    return INVALID_INDEX;
  }

  corr->wrapper_offset = init_wrapper(CORRIDOR_OBJ, corr->ent,
                                      (void *) num_corridors);
  if (corr->wrapper_offset == INVALID_INDEX) {
    return -1;
  }

  /* Initialize corridor entity data */
  glm_vec3_copy(pos, corr->ent->translation);
  glm_vec3_copy((vec3) GLM_VEC3_ZERO_INIT, corr->ent->ang_velocity);
  glm_vec3_copy((vec3) GLM_VEC3_ZERO_INIT, corr->ent->velocity);
  corr->ent->rotation[0] = rotation[0];
  corr->ent->rotation[1] = rotation[1];
  corr->ent->rotation[2] = rotation[2];
  corr->ent->rotation[3] = rotation[3];
  glm_vec3_copy((vec3) { 1.0, 1.0, 1.0 }, corr->ent->scale);
  

  if (++num_corridors == corridor_buff_len) {
    int status = double_buffer((void **) &cd_obs, &corridor_buff_len,
                               sizeof(CORRIDOR));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate corridor buffer\n");
      return INVALID_INDEX;
    }
  }
  return num_corridors - 1;
}

void delete_corridor(size_t index) {
  if (index >= num_corridors) {
    return;
  }

  free_entity(cd_obs[index].ent);
  delete_wrapper(cd_obs[index].wrapper_offset);

  num_corridors--;
}

void corridor_remove_sim(size_t index) {
  sim_remove_entity(render_sim, cd_obs[index].ent);
  sim_remove_entity(combat_sim, cd_obs[index].ent);
  sim_remove_entity(physics_sim, cd_obs[index].ent);
}

int corridor_insert_sim(size_t index) {
  if (sim_add_entity(physics_sim, cd_obs[index].ent,
                              ALLOW_HURT_BOXES)) {
    return -1;
  }

  if (sim_add_entity(combat_sim, cd_obs[index].ent,
                              ALLOW_HURT_BOXES)) {
    return -1;
  }

  if (sim_add_entity(render_sim, cd_obs[index].ent,
                              ALLOW_DEFAULT)) {
    return -1;
  }
  return 0;
}

/* =================== CORRIDOR LAYOUT GENERATION ========================== */

void set_invalid(int *list, int size) {
  for (int i = 0; i < size; i++) {
    list[i] = INVALID;
  }
}

/*
  Gets random item from the list, then removes and returns it
*/
int get_random(int *list, size_t size, int *num_elements) {
  /* Keep picking random items until a non-error block is found */
  if (*num_elements == 0) {
    return NO_ELEMENTS;
  }
  int ret = rand() % size;
  while (list[ret] == INVALID) {
    ret = rand() % size;
  }
  /* Denote the removal of the element from the list */
  (*num_elements)--;
  int temp = list[ret];
  list[ret] = INVALID;
  return temp;
}

/*
  Searches through the list to find an element and remove it
*/
void remove_element(int *list, size_t size, int *num_elements, int remove) {
  if (*num_elements == 0) {
    return;
  }
  for (int i = 0; i < size; i++) {
    if (list[i] == remove) {
      list[i] = INVALID;
      (*num_elements)--;
      return;
    }
  }
}

/*
  Adds an element to the list and doubles the buffer if it is
  needed to fit the next coming element.
*/
void add_element(int **list, size_t *size, int *num_elements, int to_add) {
  if (*size == *num_elements) {
    int prev_size = *size;
    if (double_buffer((void **) list, size, sizeof(int)) == -1) {
      printf("maze.c: failed to double buffer\n");
      exit(1);
    }
    set_invalid((*list) + prev_size, prev_size);
  }
  for (int i = 0; i < *size; i++) {
    if ((*list)[i] == INVALID) {
      (*list)[i] = to_add;
      (*num_elements)++;
      return;
    }
  }
}

/*
  Connect is called on a FRONTIER cell to have one of the walls
  around the frontier cell which is adjacent to a IN cell removed
  so that the frontier cell is connected to the rest of the maze.
  After, the previously frontier cell is added to the rest of the
  maze by being converted into an IN cell. After, all the adjacent
  OUT cells around the newly created IN cell are changed to frontier
  cells.
*/
void connect_cell(int **maze,
                  int x, int y, int **list,
                  size_t *size, int *num_elements) {
  /* Find a wall around the frontier square that is adjacent */
  /* to an IN cell, then remove the wall by setting to IN    */
  if ((x + 2) < maze_size && maze[x + 2][y] == IN) {
    UNSET_WALL(maze, x + 1, y);
  } else if ((x - 2) > 0 && maze[x - 2][y] == IN) {
    UNSET_WALL(maze, x - 1, y);
  } else if ((y + 2) < maze_size && maze[x][y + 2] == IN) {
    UNSET_WALL(maze, x, y + 1);
  } else if ((y - 2) > 0 && maze[x][y - 2] == IN) {
    UNSET_WALL(maze, x, y - 1);
  }

  /* Remove the frontier square from the list */
  remove_element(*list, *size, num_elements, CONVERT_COMBINED(x, y));

  /* Set to IN */
  maze[x][y] = IN;

  /* Set frontier squares and add to frontier list */
  if ((x + 2) < maze_size && maze[x + 2][y] == OUT) {
    maze[x + 2][y] = FRONTIER;
    add_element(list, size, num_elements, CONVERT_COMBINED(x + 2, y));
  }
  if ((x - 2) > 0 && maze[x - 2][y] == OUT) {
    maze[x - 2][y] = FRONTIER;
    add_element(list, size, num_elements, CONVERT_COMBINED(x - 2, y));
  }
  if ((y + 2) < maze_size && maze[x][y + 2] == OUT) {
    maze[x][y + 2] = FRONTIER;
    add_element(list, size, num_elements, CONVERT_COMBINED(x, y + 2));
  }
  if ((y - 2) > 0 && maze[x][y - 2] == OUT) {
    maze[x][y - 2] = FRONTIER;
    add_element(list, size, num_elements, CONVERT_COMBINED(x, y - 2));
  }
}


int **gen_maze() {
  int **maze = (int **) malloc(sizeof(int *) * maze_size);
  for (int i = 0; i < maze_size; i++) {
    maze[i] = (int *) malloc(sizeof(int) * maze_size);
  }
  size_t size = MIN_FRONTIER;
  int *frontier_list = (int *)(malloc(sizeof(int) * size));
  int num_elements = 0;

  /* Set all elements to invalid */
  set_invalid(frontier_list, size);

  /* Seed rand() for this generation time */
  srand(time(NULL));

  /* Set up maze in a grid */
  for (int x = 0; x < maze_size; x++) {
    for (int y = 0; y < maze_size; y++) {
      if (x % 2 == 0 || y % 2 == 0) {
        maze[x][y] = WALL;
      } else {
        maze[x][y] = OUT;
      }
      /* Set the outside wall for back side of maze */
      if ((x == (maze_size - 1) || y == (maze_size - 1))) {
        maze[x][y] = WALL;
      }
    }
  }

  /* Set entrance */
  maze[1][1] = IN;

  /* Manually set frontiers around starting point */
  maze[3][1] = FRONTIER;
  maze[1][3] = FRONTIER;

  /* Add the manually set frontiers to list */
  add_element(&frontier_list, &size, &num_elements, CONVERT_COMBINED(1, 3));
  add_element(&frontier_list, &size, &num_elements, CONVERT_COMBINED(3, 1));

  /* Set the exit location */
  //maze[maze_size - 2][maze_size - 1] = IN;

  /* While there are frontier cells left */
  /* choose one at random                */
  int random = get_random(frontier_list, size, &num_elements);
  while (random != NO_ELEMENTS || num_elements > 0) {
    connect_cell(maze, CONVERT_X(random), CONVERT_Y(random),
            &frontier_list, &size, &num_elements);
    random = get_random(frontier_list, size, &num_elements);
  }
  free(frontier_list);
  return maze;
}

void free_maze(int **maze) {
  for (int i = 0; i < maze_size; i++) {
    free(maze[i]);
  }
  free(maze);
}
