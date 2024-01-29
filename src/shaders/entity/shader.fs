#version 430 core

in vec4 frag_pos;
in vec2 tex_coords;
in vec3 normal;
in vec3 view_pos;

out vec4 frag_col;

uniform struct Material {
  sampler2D diff_map;
  sampler2D spec_map;
  int shine;
} material;

// Dir is the direction of the light projected
// FROM the fragment TO the light (light_pos - frag_pos)
struct DIR_LIGHT {
  vec3 col;
  vec3 dir;
} dir_light;

struct PT_LIGHT {
  vec3 col;
  vec3 pos;
  int a_consts[3];
};

vec3 calc_dir_light(DIR_LIGHT light);

void main() {
  dir_light.col = vec3(1.0, 1.0, 1.0);
  dir_light.dir = vec3(1.0, 1.0, 1.0);

  //frag_col = vec4(calc_dir_light(dir_light), 1.0);
  frag_col = vec4(1.0, 1.0, 1.0, 1.0);
}

vec3 calc_dir_light(DIR_LIGHT light) {
  vec3 col = vec3(texture(material.diff_map, tex_coords));
  if (col.x == 0.0 && col.y == 0.0 && col.z == 0.0) {
    col = vec3(1.0, 1.0, 1.0);
  }

  vec3 ambient = light.col * 0.05;

  vec3 diffuse = max(dot(normalize(normal), normalize(light.dir)), 0) * light.col;

  vec3 view_dir = normalize(view_pos - vec3(frag_pos));
  vec3 halfway = normalize(normalize(light.dir) + view_dir);
  float spec = pow(max(dot(normalize(normal), halfway), 0), 32);
  vec3 specular = spec * light.col;

  return (ambient + diffuse + specular) * col;
}

/*vec3 calc_point_light(struct PT_LIGHT light) {
  vec3 col = vec3(texture(material.diff_map, tex_coords));
  if (col.x == 0.0 && col.y == 0.0 && col.z == 0.0) {
    col = vec3(1.0, 1.0, 1.0);
  }

  vec3 ambient = light.col * 0.05;

  vec3 light_dir = normalize(vec3(frag_pos) - light.pos);
  vec3 diffuse = max(dot(normalize(normal), light_dir), 0) * light.col;

  vec3 view_dir = normalize(view_pos - vec3(frag_pos));
  vec3 halfway = normalize(normalize(light_dir) + view_dir);
  float spec = pow(max(dot(normalize(normal), halfway), 0), 32);
  vec3 specular = spec * light.col;

  // TODO: ADD ATTENUATION

  return (ambient + diffuse + specular) * col;
}*/

