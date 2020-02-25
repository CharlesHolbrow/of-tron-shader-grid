#version 150

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec3 normal;
in vec2 gridPosition;
in vec3 xDirection;
in vec3 yDirection;

out float convergence;
out float viewDistance;
out vec2 gridPositionVarying;
out float xConvergence;
out float yConvergence;

void main()
{
	vec4 modelViewPos =  modelViewMatrix * position;
	vec4 modelViewNormal =  modelViewMatrix * vec4(normal, 0);
	vec4 xViewDir = normalize(modelViewMatrix * vec4(xDirection, 0));
	vec4 yViewDir = normalize(modelViewMatrix * vec4(yDirection, 0));
	
	vec4 modelViewAngle =  normalize(modelViewPos);

	// outputs
	gridPositionVarying = gridPosition;
	viewDistance = length(modelViewPos);
	convergence  = abs(dot(modelViewNormal, modelViewAngle));
	xConvergence = abs(dot(xViewDir, modelViewAngle));
	yConvergence = abs(dot(yViewDir, modelViewAngle));

	gl_Position = modelViewProjectionMatrix * position;
}
