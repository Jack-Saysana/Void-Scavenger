#version 430 core
#define TEARDROP_CONST (0.5555)
#define M_PI (3.14159265359f)
#define PHI (1.61803398874989484820459 * 00000.1) // Golden Ratio
#define PI  (3.14159265358979323846264 * 00000.1) // PI
#define SQ2 (1.41421356237309504880169 * 10000.0) // Square Root of Two

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_offset;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform float time;
uniform float particle_scale;

vec3 random_sphere_point(vec2);
vec3 random_teardrop_point(vec2);

out vec3 col;

void main() {
  vec3 fire_pt = random_teardrop_point(in_offset + vec2(time + 0.01));
  mat3 cam_to_world = transpose(mat3(view));
  gl_Position = projection * view *
                (vec4(cam_to_world * particle_scale * in_pos, 0.0) +
                 model * vec4(particle_scale * fire_pt, 1.0));
}

float gold_noise(vec2 coordinate, in float seed){
    return fract(tan(distance(coordinate*(seed+PHI), vec2(PHI, PI)))*SQ2);
}

vec3 random_sphere_point(vec2 uv) {
    // generating uniform points on the sphere: http://corysimon.github.io/articles/uniformdistn-on-sphere/
    // Note: Use uniform random generator instead of noise in your applications
    float theta = 2.0f * M_PI * gold_noise(vec2(uv.x * 0.3482f, uv.y * 2.18622f), M_PI);
    float phi = acos(1.0f - 2.0f * gold_noise(vec2(uv.x * 1.9013, uv.y * 0.94312), M_PI));
    float epsilon = asin(1.0f - 2.0f * gold_noise(vec2(uv.x * 1.4841, uv.y * 0.84273), M_PI));
    float x = sin(phi) * cos(theta);
    float y = sin(phi) * sin(theta);
    float z = cos(phi);
    float w = sin(epsilon);

    return w * vec3(x,y,z);
}

vec3 random_teardrop_point(vec2 uv) {
    float theta = 2.0f * M_PI * gold_noise(vec2(uv.x * 0.3482f, uv.y * 2.18622f), M_PI);
    float phi = acos(1.0f - 2.0f * gold_noise(vec2(uv.x * 1.9013, uv.y * 0.94312), M_PI));
    float epsilon = asin(1.0f - 2.0f * gold_noise(vec2(uv.x * 1.4841, uv.y * 0.84273), M_PI));

    float y = abs(sin(phi));
    y = (y-1)*(y-1);
    float x_bound_squared = (1-y)*(1-y)*(1-y)*y*TEARDROP_CONST;
    float x = sqrt(x_bound_squared) * sin(theta);
    float z = sqrt(x_bound_squared - (x*x)) * sin(epsilon);
    vec3 coord = vec3(x,y,z);
    float weight = length(coord);

    float q = (1.0-weight);
    q = q*q*q*q;
    col = vec3(q, q, 1.0);

    return coord;
}

