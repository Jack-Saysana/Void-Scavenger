#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define IN            (0)
#define OUT           (1)
#define FRONTIER      (2)
#define WALL          (3)
#define INVALID       (-1)
#define NO_ELEMENTS   (-2)
#define MAX_MAZE_SIZE (41)
#define MIN_FRONTIER  (8)

/*
    Helper macros to convert from linear to 2D array
*/
#define CONVERT_X(z)           (z % MAX_MAZE_SIZE)
#define CONVERT_Y(z)           (z / MAX_MAZE_SIZE)
#define CONVERT_COMBINED(x, y) ((x) + ((y) * MAX_MAZE_SIZE))

/*
    Takes an "WALL" and set to "IN"
*/
#define UNSET_WALL(maze, x, y) (maze[x][y] = IN)

/* ======================== EXTERNALLY DEFINED FUNCTIONS ================== */
int double_buffer(void **, unsigned int *, unsigned int);
