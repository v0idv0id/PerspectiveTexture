#version 330 core


void main() {
  vec2 coord = gl_PointCoord - vec2(0.5); 
  if (length(coord) > 0.5)                
    discard;
  gl_FragColor = vec4(1.0,0.0,1.0,0.1);
}