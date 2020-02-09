#version 120

uniform vec2 screenSize;
varying vec2 varyingCoords;
varying vec4 modelViewPos;
varying vec4 modelViewNormal;
varying vec3 normal;

void main()
{
    vec2 uv = gl_FragCoord.xy / screenSize;
    
    vec3 col = vec3(0);
    col.rb += smoothstep(0.1, 0., fract(varyingCoords.x)) * 0.5;
    col.rb += smoothstep(0.9, 1., fract(varyingCoords.x)) * 0.5;
    col.b  += smoothstep(0.1, 0., fract(varyingCoords.y));
    col.b  += smoothstep(0.9, 1., fract(varyingCoords.y));
    col.g = abs(dot(normalize(modelViewPos.xyz), modelViewNormal.xyz)) * 0.5;

	gl_FragColor = vec4(col, 1.);
}