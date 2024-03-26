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
  // Offset of corridor the enemy is moving towards 
  size_t target_corridor;
  // Offset of corridor the enemy currently resides in
  size_t cur_corridor;

  // Pathfinding data
  // Vector directing the enemy away from other enemies
  vec3 nearby_enemies;

  float max_health;
  float cur_health;
  float cur_speed;
  float fire_rate;
  E_WEAP_T weapon_type;
  int invuln;

  // Animation data
  unsigned int cur_frame;
} ST_ENEMY;

#endif
