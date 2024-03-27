#ifndef __PLAYER_STR_H__
#define __PLAYER_STR_H__

#include <structs/ship_str.h>

/*                              PLAYER_STR.H

  Manages a player in station mode as well as the meta-game statistics that
  will be displayed to the player upon death. This includes managing the
  player's inventory, skill tree, health, speed and spatial data.

*/

typedef enum item_slot_id {
  I_SLOT_EMPTY,
  I_SLOT_REACTOR,
  I_SLOT_HULL,
  I_SLOT_SHIELD,
  I_SLOT_WEAPON,
  I_SLOT_WING,
  I_SLOT_THRUSTER
} I_SLOT_ID;

typedef struct inv_slot {
  union {
    S_REACTOR reactor;
    S_HULL hull;
    S_SHIELD shield;
    S_WEAPON weapon;
    S_WING wing;
    S_THRUSTER thruster;
  } data;
  I_SLOT_ID type;
  unsigned int weapon_type;
  int rarity;
} I_SLOT;

typedef struct player {
  // Meta-statistics
  size_t total_levels_completed;
  size_t total_enemies_defeated;
  size_t total_ships_defeated;
  double total_distance_flown;
  double total_distance_walked;
  double total_damage_dealt;
  double total_damage_taken;
  double total_experience;

  // inv
  I_SLOT *inventory;
  size_t i_size;

  // Entity in station simulation
  ENTITY *ent;
  // Offset of respective wrapper in the object_wrapper buffer
  size_t wrapper_offset;

  // Game stats
  size_t cur_experience;
  size_t max_experience;
  float cur_health;
  float max_health;
  float cur_shield;
  float max_shield;
  float speed;
  float fire_rate;
  float damage;
  int invuln;
} PLAYER;

#endif
