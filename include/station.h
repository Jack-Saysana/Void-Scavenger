#include <global_vars.h>
#include <const.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cglm/quat.h>

#define IN            (0)
#define OUT           (1)
#define FRONTIER      (2)
#define WALL          (3)
#define INVALID       (-1)
#define NO_ELEMENTS   (-2)
#define MIN_FRONTIER  (8)

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
#define RIGHT(maze, x, z) (maze[x][z + 1] == 0)    
#define LEFT(maze, x, z) (maze[x][z - 1] == 0)
#define UP(maze, x, z) (maze[x + 1][z] == 0)
#define DOWN(maze, x, z) (maze[x - 1][z] == 0)

#define CHECK_UP(maze, x, z, in) { \
  if (x > 0) {                     \
    in = UP(maze, x, z);           \
  }                                \
}

#define CHECK_DOWN(maze, x, z, in) { \
  if (x < maze_size - 1) {           \
    in = DOWN(maze, x, z);           \
  }                                  \
}

#define CHECK_LEFT(maze, x, z, in) { \
  if (z > 0) {                       \
    in = LEFT(maze, x, z);           \
  }                                  \
}

#define CHECK_RIGHT(maze, x, z, in) { \
  if (z < maze_size - 1) {            \
    in = RIGHT(maze, x, z);           \
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
