#version 150

uniform vec2 screenSize;
out vec4 fragColor;

void main() {
  // To get (-1, 1) coords at the screen level, try:
  // vec2 uv = (gl_FragCoord.xy - 0.5*screenSize) / screenSize.y;

  // To get (-1, 1) coords at the "sprite" level
  vec2 uv = gl_PointCoord * 2. - 1.;

  // 1 at the center, 0 at edge of sprite circle. Clamped 1-0
  float d = max(0., (1.-length(uv)));

  // create lens flare rays
  float shape = 0.03;
  float rays = 0.;
  rays += min(shape / (abs(uv.x) + shape), 1.);
  rays += min(shape / (abs(uv.y) + shape), 1.);

  float star = 0.;
  star += d * rays;
  star += d * 0.1;

  vec3 col = star * vec3(1, 1, 1); // Optionally adjust color

  fragColor = vec4(col, star);
}