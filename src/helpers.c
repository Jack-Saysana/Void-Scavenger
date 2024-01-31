#include <helpers.h>

/*                                HELPERS.C

  Defines miscellaneous helper functions that may generally be used anywhere in
  the codebase.

*/

void reset_physics(ENTITY *ent) {
  glm_quat_identity(ent->rotation);
  glm_vec3_one(ent->scale);
  glm_vec3_zero(ent->translation);
  glm_vec3_zero(ent->velocity);
  glm_vec3_zero(ent->ang_velocity);
}
