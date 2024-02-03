#include <engine/engine.h>
#include <math.h>
#include <time.h>

void seed_random() {
  srand(time(NULL));
}

void gen_rand_vec3(vec3 *to_copy, float bounds) {
  glm_vec3_copy((vec3) {
    fmod(rand(), bounds),
    fmod(rand(), bounds),
    fmod(rand(), bounds)
  }, *to_copy);
}

void gen_rand_vec2(vec2 *to_copy, float bounds) {
  glm_vec2_copy((vec2) {
    fmod(rand(), bounds),
    fmod(rand(), bounds)
  }, *to_copy);
}

float gen_rand_float(float bounds) {
  return fmod(rand(), bounds);
}

int gen_rand_int(int bounds) {
  return rand() % bounds;
}
