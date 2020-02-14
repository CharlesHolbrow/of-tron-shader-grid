#version 150

uniform vec2 screenSize;
out vec4 fragColor;

void main() {
  // To get (-1, 1) coords at the screen level, try:
  // vec2 uv = (gl_FragCoord.xy - 0.5*screenSize) / screenSize.y;

  // To get (-1, 1) coords at the "sprite" level
  vec2 uv = gl_PointCoord * 2. - 1.;

  float d = max(0, (1-length(uv)));
  float rays = 0;
  float star = 0;
  rays += .03 / abs(uv.x);
  rays += .03 / abs(uv.y);
  // float rays = abs(min(0.9, .1/uv.x) + min(0.9, .01/uv.y));
  star += d * rays;
  star += d * 0.1;

  vec3 col = vec3(star);
  col.g = 0.3;
  
  fragColor = vec4(col, star);
  // fragColor = vec4(fract(gl_PointCoord.x * 0.5), 0, 0, 1);
}