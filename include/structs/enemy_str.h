#ifndef __ENEMY_STR_H__
#define __ENEMY_STR_H__

/*                                 ENEMY_STR.H

  Represents an enemy in station mode. Manages the enemy's health, speed and
  attack info, as well as the spatial/physical information about the enemy.

*/

typedef enum enemy_weap_type {
  MELEE,
  RANGED
} E_WEAP_T;

typedef struct station_enemy {
  // Entity data in station mode station
  ENTITY *ent;
  // Offset of respective wrapper in the object_wrapper buffer
  size_t wrapper_offset;

  float max_health;
  float cur_health;
  float speed;
  float fire_rate;
  E_WEAP_T weapon_type;
  int invuln;
} ST_ENEMY;

#endif
