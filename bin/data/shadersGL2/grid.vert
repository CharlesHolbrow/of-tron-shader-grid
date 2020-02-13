#version 120

uniform mat4 modelViewMatrix;
attribute vec2 cartesianCoords;
varying float convergance;
varying float viewDistance;
varying vec4 worldPos;

void main()
{
	vec4 modelViewPos =  gl_ModelViewMatrix * gl_Vertex;
	vec4 modelViewNormal =  gl_ModelViewMatrix * vec4(gl_Normal, 0);

	// outputs
	worldPos = gl_Vertex;
	convergance = abs(dot(modelViewNormal, normalize(modelViewPos)));
	viewDistance = length(modelViewPos);

	gl_Position = ftransform();
}