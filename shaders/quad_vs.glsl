#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aTexCoords;
layout(location = 2) in vec3 aTexCoords_orig;

out vec3 TexCoords;
out vec3 TexCoords_orig;


void main() {
  TexCoords = aTexCoords;
  TexCoords_orig = aTexCoords_orig;
  gl_Position = vec4(aPos, 1.0);
}