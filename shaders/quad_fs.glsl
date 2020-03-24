#version 330 core

in vec3 TexCoords;
in vec3 TexCoords_orig;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float texmix;

void main() {
  vec4 frag0 = texture(texture0, TexCoords.xy / TexCoords.z ); // this is the perspective 
  vec4 frag1 = texture(texture1, TexCoords_orig.xy * vec2(1.0, -1.0)); // original - the vec2(1.0,-1.0) is just for flipping the image
  gl_FragColor = mix(frag0, frag1, texmix);
}