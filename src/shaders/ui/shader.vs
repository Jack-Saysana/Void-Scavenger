#version 430 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_tex_coords;
layout (location = 3) in ivec4 in_bone_ids;
layout (location = 4) in vec4 in_weights;

uniform mat4 model;
uniform mat4 proj;

out vec2 tex_coords;

void main() {
  gl_Position = proj * model * vec4(in_pos, 1.0);
  tex_coords = in_tex_coords;
}
