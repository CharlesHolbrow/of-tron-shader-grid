#version 120

uniform vec2 screenSize;
varying vec4 worldPos;

// How perpendicular is the normal a ray project from the camera?
// 1 = surface is perpendicular camera ray
// 0 = surface is parallel camera ray
varying float convergance;

// How var from the camera is the pixel
varying float viewDistance;

void main()
{
    vec2 uv = gl_FragCoord.xy / screenSize;
    float width = .1;
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

	gl_FragColor = vec4(col, 1.);
}