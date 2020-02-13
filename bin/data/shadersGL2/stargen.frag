#version 120

uniform vec2 screenSize;

void main() {
  vec2 uv = (gl_FragCoord.xy - 0.5*screenSize) / screenSize.y;

  
  float d = max(0, (1-length(uv*4)));
  float rays = abs(.01/uv.x * .01/uv.y);
  float star = d * rays + d *0.1;
  vec3 col = vec3(star);
  
  gl_FragColor = vec4(col, 1);
}