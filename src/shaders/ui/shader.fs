#version 430 core

in vec2 tex_coords;

out vec4 frag_col;

uniform int textured;
uniform struct Material {
  sampler2D amb_map;
} material;

void main() {
  frag_col = vec4(1.0);
  if (textured != 0) {
    frag_col = texture(material.amb_map, tex_coords);
  }
}
