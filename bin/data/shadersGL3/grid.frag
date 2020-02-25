#version 150
#define PI 3.1415926535897932384626433832795

uniform vec2 screenSize;
uniform float time;
in vec2 gridPositionVarying;

// How perpendicular is the normal to a ray projected from the camera?
// 1 = surface is perpendicular to camera ray
// 0 = surface is parallel to camera ray
in float convergence;
in float xConvergence;
in float yConvergence;

// How var from the camera is the pixel
in float viewDistance;

// provided by openFrameworks
out vec4 fragColor;

// map input range to 0-1
float map(float v, float inMin, float inMax) {
    return (v - inMin) / (inMax - inMin);
}
// map input range to 0-1, clamping output
float mapC(float v, float inMin, float inMax) {
    return clamp((v - inMin) / (inMax - inMin), 0, 1);
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
    width += mapC(viewDistance, 2, 32.) * .3  * (1-convergence);

    float distanceFallof =  pow(0.5 + 20/viewDistance, 1.3);
    float attenuation = min(1.4, distanceFallof * pow(convergence, 1.13));

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
    width += mapC(viewDistance, 2, 32.) * .3  * (1-convergence);

    float distanceFallof =  pow(0.5 + 20/viewDistance, 1.3);
    float attenuation = min(1.4, distanceFallof * pow(convergence, 1.13));
    // attenuation = 1;

    float p = clamp(1 - map(length(gridPositionVarying), 5, 50), 0.0, 3);
    p = mapC(length(gridPositionVarying), 20, 50, 1, 0);

    float xWidth = width + max(max(0, map(pow(xConvergence, 4), 0, 1, 0, 0.4)), max(0, map(viewDistance, 10, 80, 0, 0.3)));
    float yWidth = width + max(max(0, map(pow(yConvergence, 4), 0, 1, 0, 0.4)), max(0, map(viewDistance, 10, 80, 0, 0.3)));

    // x axis
    col.rgb += xColor * (smoothstep(xWidth, 0, fract(gridPositionVarying.x)) * attenuation) * p;
    col.rgb += xColor * (smoothstep(1-xWidth, 1, fract(gridPositionVarying.x)) * attenuation) * p;

    // z axis
    col.rgb += yColor * (smoothstep(yWidth, 0, fract(gridPositionVarying.y)) * attenuation * p);
    col.rgb += yColor * (smoothstep(1-yWidth, 1, fract(gridPositionVarying.y)) * attenuation * p);

    return col;
}

vec4 colorForTheme(int theme) {
    vec3 c1 = vec3(0.8, 0.0, 0.9);
    vec3 c2 = vec3(0, 0.5, 1.0);

    switch(theme) {
    case 0:
        return themeClassic();
        break;
    case 1:
        return themeParametric(c1, c2);
        break;
    case 2:
        return themeParametric(vec3(1), vec3(1));
    }
}

void main()
{
    float amountA = sin(time * PI / 10.) * .5 + 0.5;
    float amountB = 1 - amountA;

    vec4 colorA = colorForTheme(1) * amountA;
    vec4 colorB = colorForTheme(2) * amountB;

    vec4 color = vec4(0);
    color += colorA;
    color += colorB;

    fragColor = color;
}
