#version 430 core

#define LOCATION (0)
#define ROTATION (1)
#define SCALE (2)

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_tex_coords;
layout (location = 3) in ivec4 in_bone_ids;
layout (location = 4) in vec4 in_weights;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 camera_pos;

out vec4 frag_pos;
out vec3 tex_coords;
out vec3 normal;
out vec3 view_pos;

void main() {
  gl_Position = projection * view * model * vec4(in_pos, 1.0);

  frag_pos = model * vec4(in_pos, 1.0);
  tex_coords = in_pos;
  normal = mat3(transpose(inverse(model))) * in_normal;
  view_pos = camera_pos;
}
