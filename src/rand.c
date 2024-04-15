#include <engine/engine.h>
#include <math.h>
#include <time.h>

#define PHI (1.61803398874989484820459 * 00000.1) // Golden Ratio
#define PI  (3.14159265358979323846264 * 00000.1) // PI
#define SQ2 (1.41421356237309504880169 * 10000.0) // Square Root of Two

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

void gen_rand_vec3_plus_minus(vec3 *to_copy, float bounds) {
  vec3 temp = GLM_VEC3_ZERO_INIT;
  gen_rand_vec3(&temp, bounds);
  temp[0] -= bounds / 2.0;
  temp[1] -= bounds / 2.0;
  temp[2] -= bounds / 2.0;
  glm_vec3_copy(temp, *to_copy);
}

void gen_rand_vec4(vec4 *to_copy, float bounds) {
  glm_vec4_copy((vec4) {
    fmod(rand(), bounds),
    fmod(rand(), bounds),
    fmod(rand(), bounds),
    fmod(rand(), bounds)
  }, *to_copy);
}

void gen_rand_vec4_plus_minus(vec4 *to_copy, float bounds) {
  vec4 temp = GLM_VEC4_ZERO_INIT;
  gen_rand_vec4(&temp, bounds);
  temp[0] -= bounds / 2.0;
  temp[1] -= bounds / 2.0;
  temp[2] -= bounds / 2.0;
  temp[3] -= bounds / 2.0;
  glm_vec4_copy(temp, *to_copy);
}

void gen_rand_vec2(vec2 *to_copy, float bounds) {
  glm_vec2_copy((vec2) {
    fmod(rand(), bounds),
    fmod(rand(), bounds)
  }, *to_copy);
}

void gen_rand_vec2_plus_minus(vec2 *to_copy, float bounds) {
  vec2 temp = GLM_VEC2_ZERO_INIT;
  gen_rand_vec2(&temp, bounds);
  temp[0] -= bounds / 2.0;
  temp[1] -= bounds / 2.0;
  glm_vec2_copy(temp, *to_copy);
}

float gen_rand_float(float bounds) {
  return ((float) rand() / RAND_MAX) * bounds;
}

int gen_rand_int(int bounds) {
  return rand() % bounds;
}

float gen_rand_float_plus_minus(float bounds) {
  float temp = gen_rand_float(bounds);
  temp -= bounds / 2.0;
  return temp;
}

float gold_noise() {
  vec2 dummy = GLM_VEC2_ZERO_INIT;
  gen_rand_vec2(&dummy, 10.0);
  glm_vec2_scale(dummy, glfwGetTime() + PHI, dummy);
  double nothing;
  float output =
          modf(tan(glm_vec2_distance(dummy, (vec2) {PHI, PI})) * SQ2, &nothing);
  return output < 0.0 ? output *= -1 : output;
}
