#version 430 core

uniform vec3 test_col;

out vec4 FragColor;

void main() {
  FragColor = vec4(test_col, 1.0);
}
