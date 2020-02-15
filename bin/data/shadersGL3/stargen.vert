#version 150
in vec4 position;

// These matrices are supplied by openFrameworks. Unfortunately, they seem to be
// inaccurate when rendering to a non-default FBO.
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

// The camera matrix uniforms provided by OpenFrameworks only seem to be
// accurate when rendering to the default FBO. I manually supply the necessary
// camera matrices so that this shader can render to non-default FBOs.
uniform mat4 mv; // model view matrix
uniform mat4 p; // projection matrix

// My Billboarding algorithm also requires a screen size.
uniform vec2 screenSize;

// How big should we render the sprite?
#define SPRITE_DIM 351.0

void main() {
	// View space (aka "eye space") coordinates are in the camera frustrum
	// (which is a "truncated pyramid") https://gamedev.stackexchange.com/questions/153078/what-can-i-do-with-the-4th-component-of-gl-position
	vec4 eyePos = mv * position;
	// I believe projVoxel encodes the clip space dimensions of the cuboid that
	// effectively contains this sprite.
	vec4 projVoxel = p * vec4(SPRITE_DIM, SPRITE_DIM, eyePos.z, eyePos.w);
	// To get the size of the sprite in screen space
	// (1) divide by w to get NDC, then  (2) multiply time screen size
	vec2 projSize = screenSize * projVoxel.xy / projVoxel.w;
	gl_PointSize = 0.25 * (projSize.x + projSize.y);
	gl_Position = p * eyePos;
}
