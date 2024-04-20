#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cglm/cglm.h>
#include <const.h>
#include <pthread.h>
#include <global_vars.h>

#define IN            (0)
#define OUT           (1)
#define FRONTIER      (2)
#define WALL          (3)
#define ARENA         (9)
#define INVALID       (-1)
#define NO_ELEMENTS   (-2)
#define MIN_FRONTIER  (8)

/* Arena creation helpers */
#define CORRIDOR_LOCATION (10)
#define ARENA_LOCATION    (11)
#define NONE              (12)
#define MIN_ARENA_SIZE    (2)

/*
    Helper macros to convert from linear to 2D array
*/
#define CONVERT_X(z)           (z % maze_size)
#define CONVERT_Y(z)           (z / maze_size)
#define CONVERT_COMBINED(x, y) ((x) + ((y) * maze_size))

/*
    Takes an "WALL" and set to "IN"
*/
#define UNSET_WALL(maze, x, y) (maze[x][y] = IN)

/* Maze to corridor macro helpers */
#define S_RIGHT(maze, x, z) (maze[x][z + 1] == IN)
#define S_LEFT(maze, x, z) (maze[x][z - 1] == IN)
#define S_UP(maze, x, z) (maze[x + 1][z] == IN)
#define S_DOWN(maze, x, z) (maze[x - 1][z] == IN)

/* Maze to arena macro helpers */
/* 9 == arena location */
#define A_RIGHT(maze, x, z) (maze[x][z + 1] == ARENA)
#define A_LEFT(maze, x, z) (maze[x][z - 1] == ARENA)
#define A_UP(maze, x, z) (maze[x + 1][z] == ARENA)
#define A_DOWN(maze, x, z) (maze[x - 1][z] == ARENA)

#define CHECK_UP(maze, x, z, in) { \
  if (x > 0) {                     \
    in = S_UP(maze, x, z);         \
    if (!in)                       \
      in = A_UP(maze, x, z);       \
  }                                \
}

#define CHECK_DOWN(maze, x, z, in) { \
  if (x < maze_size - 1) {           \
    in = S_DOWN(maze, x, z);         \
    if (!in)                         \
      in = A_DOWN(maze, x, z);       \
  }                                  \
}

#define CHECK_LEFT(maze, x, z, in) { \
  if (z > 0) {                       \
    in = S_LEFT(maze, x, z);         \
    if (!in)                         \
      in = A_LEFT(maze, x, z);       \
  }                                  \
}

#define CHECK_RIGHT(maze, x, z, in) { \
  if (z < maze_size - 1) {            \
    in = S_RIGHT(maze, x, z);         \
    if (!in)                          \
      in = A_RIGHT(maze, x, z);       \
  }                                   \
}

/* Quaternion creation macro (about OpenGL y-axis) */
#define CREATE_QUATERNION(rotation, quaternion) {            \
  glm_quat_identity(quaternion);                             \
  glm_quatv(quaternion, rotation, (vec3) { 0.0, 1.0, 0.0 }); \
}

/* ======================== INTERNALLY DEFINED FUNCTIONS ================== */
void free_maze(int **);
void spawn_small_station_obstacle(vec3);
void spawn_large_station_obstacle(vec3);
void gen_terminal_location(int, int, vec3, vec3, versor);
size_t gen_cd_obj(int **, ivec2, vec3, vec3, int *, int *, int *, int);
void object_random_offset(vec3);
void spawn_ship_part(vec3);
void print_maze(int **);
void add_arena(int, int **);

/* ======================== EXTERNALLY DEFINED FUNCTIONS ================== */
int double_buffer(void **, size_t *, size_t);
ENTITY *init_corridor_ent(size_t index);

size_t init_wrapper(SOBJ_T, ENTITY *, void *);
void delete_wrapper(size_t);

int gen_rand_int(int);
float gen_rand_float(float);
void gen_rand_vec3(vec3 *, float);
float gen_rand_float(float);
void seed_random();

void station_obstacle_insert_sim(size_t);
int space_obstacle_insert_sim(size_t);
size_t init_station_obstacle(int, vec3, vec3, versor, float);

void spawn_st_enemy(vec3, int, int);
void spawn_st_terminal(vec3, versor);

size_t init_item(int, int, vec3, vec3, versor, float);
int item_insert_sim(size_t);

int get_details_state();
