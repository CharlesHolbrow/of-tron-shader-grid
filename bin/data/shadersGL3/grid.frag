#version 150

uniform vec2 screenSize;
in vec4 worldPos;

// How perpendicular is the normal a ray project from the camera?
// 1 = surface is perpendicular camera ray
// 0 = surface is parallel camera ray
in float convergance;

// How var from the camera is the pixel
in float viewDistance;

// provided by openFrameworks
out vec4 fragColor;

// map input range to 0-1
float map(float v, float min, float max) {
    return clamp((v - min) / (max - min), 0, 1);
}

void main()
{
    //vec2 uv = gl_FragCoord.xy / screenSize;
    float width = .06;
    // Allow distant lines to grow thicker if they are at an accute angle
    width += map(viewDistance, 100, 1600) * .3  * (1-convergance);

    float distanceFallof =  pow(0.5 + 1000/viewDistance, 1.3);
    float attenuation = min(1.4, distanceFallof * pow(convergance, 1.13));
    float cellSize = 50.;

    vec3 col = vec3(0);

    // x axis
    col.rb += smoothstep(width, 0, fract(worldPos.x / cellSize)) * attenuation * 0.5;
    col.rb += smoothstep(1-width, 1, fract(worldPos.x / cellSize)) * attenuation * 0.5;
    col.r *= 2;
    // z axis
    col.g  += smoothstep(width, 0, fract(worldPos.z / cellSize)) * attenuation;
    col.g  += smoothstep(1-width, 1, fract(worldPos.z / cellSize)) * attenuation;
    col.rgb += attenuation * 0.025;

	fragColor = vec4(col, 1.);
}