#version 120

attribute vec2 cartesianCoords;
varying vec2 varyingCoords;

void main()
{
	varyingCoords = cartesianCoords;
	gl_Position = ftransform();
}