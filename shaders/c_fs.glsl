#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main() {
  vec2 dimensions = vec2(800,600);
  // vec4 filterArea = vec4(1.0);
  // vec2 pixelCoord = TexCoords  ; //* filterArea.xy;
  // vec2 uv = pixelCoord.xy / dimensions.xy;
  // uv -= 0.5;
  // float r = 0.5;
  // float d = length(uv);
  // float c = smoothstep(d,d+0.003,r);
  // FragColor = vec4(vec3(c,0.5,0.),1.0);

  vec2 midpoint = dimensions.xy * 0.5;
  float radius = min(dimensions.x, dimensions.y) * 0.2;
  float dist = length(gl_FragCoord.xy - midpoint);
  float circle = smoothstep(radius - 1.0, radius + 1.0, dist);
  FragColor = vec4(vec3(circle,0.5,0.),1.0);

  // vec2 st= gl_FragCoord.xy;
  // st = TexCoords;
  // // vec4 colorx=mix(vec4(1.,1.,1.,1.),vec4(.0,.0,.0,1.0), 2
  // *length(st-vec2(.5,.5))); FragColor = texture(texture1, TexCoords);
}