#version 430 core

in vec3 col;
out vec4 FragColor;

void main() {
  FragColor = vec4(col, 0.5);
}
