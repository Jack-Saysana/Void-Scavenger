#ifndef __ENGINE_SPATIAL_ALGEBRA_H__
#define __ENGINE_SPATIAL_ALGEBRA_H__

#include <cglm/vec3.h>
#include <cglm/mat3.h>

#define VEC6_ZERO_INIT { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }
#define MAT6_ZERO_INIT {VEC6_ZERO_INIT, VEC6_ZERO_INIT, VEC6_ZERO_INIT, VEC6_ZERO_INIT, VEC6_ZERO_INIT, VEC6_ZERO_INIT}

typedef float vec6[6];
typedef vec6 mat6[6];

// Z = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
// m = [[Z, Z], [Z, Z]]
void mat6_zero(mat6 m);
// dest = m
void mat6_copy(mat6 m, mat6 dest);
// dest = [[m1, m2], [m3, m4]]
void mat6_compose(mat3 m1, mat3 m2, mat3 m3, mat3 m4, mat6 dest);
// dest = m1 + m2
void mat6_add(mat6 m1, mat6 m2, mat6 dest);
// dest = m1 - m2
void mat6_sub(mat6 m1, mat6 m2, mat6 dest);
// dest = m1m2
void mat6_mul(mat6 m1, mat6 m2, mat6 dest);
// dest = mv
void mat6_mulv(mat6 m, vec6 v, vec6 dest);
// dest = s*m
void mat6_scale(mat6 m, float s, mat6 dest);
// R = rotate_fg
// T = translate_fg
// dest = [[R, 0],[TR, R]]
void mat6_spatial_transform(mat3 rotate_fg, mat3 translate_fg, mat6 dest);

// v = [0, 0, 0, 0, 0, 0];
void vec6_zero(vec6 v);
// dest = v
void vec6_copy(vec6 v, vec6 dest);
// dest = [a, b]
void vec6_compose(vec3 a, vec3 b, vec6 dest);
// dest = a + b
void vec6_add(vec6 a, vec6 b, vec6 dest);
// dest = a - b
void vec6_sub(vec6 a, vec6 b, vec6 dest);
// dest = s*a
void vec6_scale(vec6 a, float s, vec6 dest);
// v = [a, b]
// v' = transpose(transpose(b), transpose(a))
// dest = v'm
void vec6_spatial_transpose_mulm(vec6 v, mat6 m, vec6 dest);
// a = [a1, a2]
// b = [b1, b2]
// b' = transpose(transpose(b2), transpose(b1))
// dest = ab'
void vec6_spatial_transpose_mulv(vec6 a, vec6 b, mat6 dest);
// a = [a1, a2, a3, a4, a5, a6]
// b = [b1, b2, b3, b4, b5, b6]
// dest = a1 * b1 + a2 * b2 + a3 * b3 + a4 * b4 + a5 * b5 + a6 * b6
float vec6_dot(vec6 a, vec6 b);
// a = [a1, a2]
// b = [b1, b2]
// = a'b = a2*b1 + a1*b2
float vec6_inner_product(vec6 a, vec6 b);

void vec6_remove_noise(vec6 vec, float threshold);

// MISC CUSTOM OPERATIONS
void vec3_singular_cross(vec3 a, mat3 dest);

#endif
