#version 330 core
out vec4 FragColor;

in vec3 TexCoords;
in vec3 TexCoords_orig;


uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float texmix;

void main() {
  
  vec4 frag0 = texture(texture0, TexCoords.xy/TexCoords.z);
  vec4 frag1 = texture(texture1, TexCoords_orig.xy);
  FragColor = mix(frag0,frag1,texmix);
}