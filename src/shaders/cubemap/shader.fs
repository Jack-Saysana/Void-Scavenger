#version 430 core

in vec3 tex_coords;
out vec4 FragColor;

uniform samplerCube cube_map;

void main() {
  FragColor = texture(cube_map, tex_coords);
}
