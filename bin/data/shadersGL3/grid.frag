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

// map input range to 0-1
float map(float v, float min, float max) {
    return clamp((v - min) / (max - min), 0, 1);
}

// The classic color scheme I used in development
vec4 themeClassic() {
    float width = .06;

    // Allow distant lines to grow thicker if they are at an accute angle
    width += map(viewDistance, 2, 32.) * .3  * (1-convergance);

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
    float width = .06;// + (cos(gridPositionVarying.x / 10) * 0.5 + 0.5) * 0.3;

    // Allow distant lines to grow thicker if they are at an accute angle
    width += map(viewDistance, 2, 32.) * .3  * (1-convergance);

    float distanceFallof =  pow(0.5 + 20/viewDistance, 1.3);
    float attenuation = min(1.4, distanceFallof * pow(convergance, 1.13));

    vec4 col = vec4(0, 0, 0, 1);
    // x axis
    col.rgb += xColor * (smoothstep(width, 0, fract(gridPositionVarying.x)) * attenuation);
    col.rgb += xColor * (smoothstep(1-width, 1, fract(gridPositionVarying.x)) * attenuation);

    // z axis
    col.rgb += yColor * (smoothstep(width, 0, fract(gridPositionVarying.y)) * attenuation);
    col.rgb += yColor * (smoothstep(1-width, 1, fract(gridPositionVarying.y)) * attenuation);

    return col;
}

void main()
{
    vec3 c1 = vec3(0, 0.5, 1.0);
    vec3 c2 = vec3(0, 1.0, 0.5);
    int theme = 1;
    vec4 color = vec4(0);
    switch(theme) {
    case 0:
        color = themeClassic();
        break;
    case 1:
        color = themeParametric(c1, c1);
        break;
    }
    fragColor = color;
}
