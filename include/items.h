#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <glad/glad.h>
#include <pthread.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>
#include <structs/item_str.h>
#include <cglm/cglm.h>

#define BLUE_DIFF   (1.05)
#define GREEN_DIFF  (1.15)
#define PURPLE_DIFF (1.25)
#define GOLD_DIFF   (1.5)

#define MAX_NUM_PT_LIGHTS (64)

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define GOLD_COL   ((vec3) {1.0, 0.964705882, 0.262745098})
#define PURPLE_COL ((vec3) {0.780392157, 0.094117647, 0.768627451})
#define GREEN_COL  ((vec3) {0.223529412, 1.0, 0.078431373})
#define BLUE_COL   ((vec3) {0.298039216, 0.890196078, 1.0})
#define WHITE_COL  ((vec3) {1.0, 1.0, 1.0})

#define ATTENUATION_STD (1.0)
#define ATTENUATION_LINEAR (0.525)
#define ATTENUATION_QUADRATIC (0.9)

extern size_t i_size;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void set_enhancements(ST_ITEM *, int, int);
void distribute_picks(int, float, float *);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
int double_buffer(void **, size_t *, size_t);
size_t init_wrapper(SOBJ_T, ENTITY *, void *);
void delete_wrapper(size_t);

ENTITY *init_item_ent(PART_T);

float gen_rand_float(float);
