#version 120
uniform mat4 modelViewMatrix;
attribute vec2 cartesianCoords;
varying vec2 varyingCoords;
varying vec4 modelViewPos;
varying vec4 modelViewNormal;
varying vec3 normal;

void main()
{
	varyingCoords = cartesianCoords;
	modelViewPos =  gl_ModelViewMatrix * gl_Vertex;
	modelViewNormal =  gl_ModelViewMatrix * vec4(gl_Normal, 0);
	normal = gl_Normal;
	gl_Position = ftransform();
}