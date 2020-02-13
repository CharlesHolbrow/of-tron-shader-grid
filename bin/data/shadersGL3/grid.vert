#version 150

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec3 normal;
//in vec2 cartesianCoords;

out float convergance;
out float viewDistance;
out vec4 worldPos;

void main()
{
	vec4 modelViewPos =  modelViewMatrix * position;
	vec4 modelViewNormal =  modelViewMatrix * vec4(normal, 0);

	// outputs
	worldPos = position;
	convergance = abs(dot(modelViewNormal, normalize(modelViewPos)));
	viewDistance = length(modelViewPos);

	gl_Position = modelViewProjectionMatrix * position;
}
