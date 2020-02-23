#version 150

uniform vec2 screenSize;
in vec2 gridPositionVarying;

// How perpendicular is the normal to a ray projected from the camera?
// 1 = surface is perpendicular to camera ray
// 0 = surface is parallel to camera ray
in float convergance;

// How var from the camera is the pixel
in float viewDistance;

// provided by openFrameworks
out vec4 fragColor;

// map input range to 0-1, clamping output
float mapC(float v, float inMin, float inMax) {
    return clamp((v - inMin) / (inMax - inMin), 0, 1);
}
float map(float v, float inMin, float inMax) {
    return (v - inMin) / (inMax - inMin);
}
float map(float v, float inMin, float inMax, float outMin, float outMax) {
    return (v - inMin) / (inMax - inMin) * (outMax - outMin) + outMin;
}
float mapC(float v, float inMin, float inMax, float outMin, float outMax) {
    float mapped = (v - inMin) / (inMax - inMin) * (outMax - outMin) + outMin;
    if (outMin > outMax) return clamp(mapped, outMax, outMin);
    return clamp(mapped, outMin, outMax);
}


// The classic color scheme I used in development
vec4 themeClassic() {
    float width = .06;

    // Allow distant lines to grow thicker if they are at an accute angle
    width += mapC(viewDistance, 2, 32.) * .3  * (1-convergance);

    float distanceFallof =  pow(0.5 + 20/viewDistance, 1.3);
    float attenuation = min(1.4, distanceFallof * pow(convergance, 1.13));

    vec4 col = vec4(0, 0, 0, 1);
    // x axis
    col.rb += smoothstep(width, 0, fract(gridPositionVarying.x)) * attenuation * 0.5;
    col.rb += smoothstep(1-width, 1, fract(gridPositionVarying.x)) * attenuation * 0.5;
    col.r *= 2;
    // z axis
    col.g  += smoothstep(width, 0, fract(gridPositionVarying.y)) * attenuation;
    col.g  += smoothstep(1-width, 1, fract(gridPositionVarying.y)) * attenuation;
    col.rgb += attenuation * 0.025;
    return col;
}


vec4 themeParametric(vec3 xColor, vec3 yColor) {
    float width = .06;
    vec4 col = vec4(0, 0, 0, 1);

    // Allow distant lines to grow thicker if they are at an accute angle
    width += mapC(viewDistance, 2, 32.) * .3  * (1-convergance);

    float distanceFallof =  pow(0.5 + 20/viewDistance, 1.3);
    float attenuation = min(1.4, distanceFallof * pow(convergance, 1.13));

    float p = clamp(1 - map(length(gridPositionVarying), 5, 50), 0.0, 3);
    p = mapC(length(gridPositionVarying), 10, 30, 1, 0);

    // x axis
    col.rgb += xColor * (smoothstep(width, 0, fract(gridPositionVarying.x)) * attenuation) * p;
    col.rgb += xColor * (smoothstep(1-width, 1, fract(gridPositionVarying.x)) * attenuation) * p;

    // z axis
    col.rgb += yColor * (smoothstep(width, 0, fract(gridPositionVarying.y)) * attenuation * p);
    col.rgb += yColor * (smoothstep(1-width, 1, fract(gridPositionVarying.y)) * attenuation * p);

    return col;
}

void main()
{
    vec3 c1 = vec3(0, 0.5, 1.0);
    vec3 c2 = vec3(0.8, 0.0, 0.9);
    int theme = 1;
    vec4 color = vec4(0);
    switch(theme) {
    case 0:
        color = themeClassic();
        break;
    case 1:
        color = themeParametric(c1, c2);
        break;
    }
    fragColor = color;
}
