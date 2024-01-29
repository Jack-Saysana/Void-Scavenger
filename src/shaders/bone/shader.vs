#version 430 core

#define LOCATION (0)
#define ROTATION (1)
#define SCALE (2)

layout (location = 0) in vec3 in_pos;
layout (location = 1) in int bone_id;

struct BONE {
  vec3 coords;
  int parent;
};

uniform mat4 bone_mats[50];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * bone_mats[bone_id] * vec4(in_pos, 1.0);
}

