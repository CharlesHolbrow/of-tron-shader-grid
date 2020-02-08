#version 120

uniform vec2 screenSize;
varying vec2 varyingCoords;

void main()
{
    vec2 uv = gl_FragCoord.xy / screenSize;
    
    vec3 col = vec3(0);
    col.rb += smoothstep(0.1, 0., fract(varyingCoords.x));
    col.b  += smoothstep(0.1, 0., fract(varyingCoords.y));
    col.rb += smoothstep(0.9, 1., fract(varyingCoords.x));
    col.b  += smoothstep(0.9, 1., fract(varyingCoords.y));

	float a = 1.0;
	gl_FragColor = vec4(col, a);
}