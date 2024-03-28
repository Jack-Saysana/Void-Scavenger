#version 430 core

#define NUM_PT_LIGHTS (64)

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
  float a_consts[3];
};

uniform PT_LIGHT light[NUM_PT_LIGHTS];
uniform uint num_pt_lights;

vec3 calc_dir_light(DIR_LIGHT light);
vec3 calc_point_light(PT_LIGHT light);

void main() {
  dir_light.col = vec3(1.0, 1.0, 1.0);
  dir_light.dir = vec3(1.0, 1.0, 1.0);

  vec3 result = calc_dir_light(dir_light);

  for (uint i = 0; i < num_pt_lights; i++) {
    result += calc_point_light(light[i]);
  }

  frag_col = vec4(result, 1.0);
}

vec3 calc_dir_light(DIR_LIGHT light) {
  vec3 col = vec3(texture(material.diff_map, tex_coords));
  if (col.x == 0.0 && col.y == 0.0 && col.z == 0.0) {
    col = vec3(1.0, 1.0, 1.0);
  }

  float ambient = 0.25;
  float diffuse = max(dot(normalize(normal), normalize(light.dir)), 0);
  vec3 view_dir = normalize(view_pos - vec3(frag_pos));
  vec3 halfway = normalize(normalize(light.dir) + view_dir);
  float spec = pow(max(dot(normalize(normal), halfway), 0), 32);

  float str = ambient + diffuse + spec;
  if (str < 0.5) {
    str = 0.5;
  } else {
    str = 1.0;
  }

  vec3 model_col = str * light.col;

  return model_col * col;
}

vec3 calc_point_light(PT_LIGHT light) {
  vec3 col = vec3(texture(material.diff_map, tex_coords));
  if (col.x == 0.0 && col.y == 0.0 && col.z == 0.0) {
    col = vec3(1.0, 1.0, 1.0);
  }

  float ambient = 0.05;

  vec3 light_dir = normalize(vec3(frag_pos) - light.pos);
  float diffuse = max(dot(normalize(normal), light_dir), 0);

  vec3 view_dir = normalize(view_pos - vec3(frag_pos));
  vec3 halfway = normalize(normalize(light_dir) + view_dir);
  float spec = pow(max(dot(normalize(normal), halfway), 0), 2);
  float distance = length(light.pos - vec3(frag_pos));
  float attenuation = 1.0 / (light.a_consts[0] + light.a_consts[1] * distance + 
              light.a_consts[2] * (distance * distance));

  float str = (ambient + diffuse + spec) * attenuation;
  if (str < 0.25) {
    str = 0.0;
  } else if (str < 0.5) {
    str = 0.25;
  } else if (str < 0.75) {
    str = 0.5;
  } else {
    str = 1.0;
  }

  vec3 model_col = str * light.col;

  return model_col * col;

}
