#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>
#include <structs/station_ship_part_str.h>

#define BLUE_DIFF   (1.05)
#define GREEN_DIFF  (1.15)
#define PURPLE_DIFF (1.25)
#define GOLD_DIFF   (1.5)

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void set_enhancements(ST_SP *, int, int);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
int double_buffer(void **, size_t *, size_t);
size_t init_wrapper(SOBJ_T, ENTITY *, void *);
void delete_wrapper(size_t);

ENTITY *init_station_ship_part_ent(size_t);
