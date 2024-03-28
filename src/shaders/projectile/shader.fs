#version 430 core

out vec4 frag_col;
uniform vec3 col;

void main() {
  frag_col = vec4(col, 1.0);
}
