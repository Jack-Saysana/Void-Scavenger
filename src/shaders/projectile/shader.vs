#version 430 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_tex_coords;
layout (location = 3) in ivec4 in_bone_ids;
layout (location = 4) in vec4 in_weights;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 frag_pos;

void main() {
  gl_Position = projection * view * model * vec4(in_pos, 1.0);

  frag_pos = model * vec4(in_pos, 1.0);
}
