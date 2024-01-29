#version 430 core

#define LOCATION (0)
#define ROTATION (1)
#define SCALE (2)

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_tex_coords;
layout (location = 3) in ivec4 in_bone_ids;
layout (location = 4) in vec4 in_weights;

uniform mat4 bone_mats[50];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 camera_pos;

out vec4 frag_pos;
out vec2 tex_coords;
out vec3 normal;
out vec3 view_pos;

//vec4 get_bone_transformation();
mat4 get_bone_transformation();

void main() {
  /*
  vec4 bone_transformation = get_bone_transformation();
  if (bone_transformation.w == 0.0) {
    bone_transformation = vec4(in_pos, 1.0);
  }
  */
  mat4 bone_transformation = get_bone_transformation();
  if (bone_transformation[3][3] == 0.0) {
    bone_transformation = mat4(1.0);
  }

  gl_Position = projection * view * model * bone_transformation *
                vec4(in_pos, 1.0);

  frag_pos = model * bone_transformation * vec4(in_pos, 1.0);
  tex_coords = in_tex_coords;
  normal = mat3(transpose(inverse(model * bone_transformation))) * in_normal;
  view_pos = camera_pos;
}

/*
vec4 get_bone_transformation() {
  vec4 total = vec4(0.0);

  int i = 0;
  int cur = in_bone_ids[i];
  while (i < 4 && cur != -1) {
    total += (in_weights[i] * bone_mats[cur] * vec4(in_pos, 1.0));
    i++;
    cur = in_bone_ids[i];
  }

  return total;
}
*/

mat4 get_bone_transformation() {
  mat4 total = mat4(0.0);
  int i = 0;
  int cur = in_bone_ids[i];
  while (i < 4 && cur != -1) {
    total += (in_weights[i] * bone_mats[cur]);
    i++;
    cur = in_bone_ids[i];
  }

  return total;
}
