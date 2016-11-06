#version 400 core

in layout(location = 0) vec3 vertPosition;
in layout(location = 1) vec3 vertNormal;
in layout(location = 2) vec3 vertColour;
in layout(location = 3) mat4 transform;

uniform mat4 camera;

out vec3 fragPosition;
out vec3 fragNormal;
out vec3 fragColour;
out mat4 transformMatrix;
out mat4 normalMatrix;

void main(void)
{
	gl_Position = camera * transform * vec4(vertPosition.xyz, 1); // consider xz axes
	fragPosition = vertPosition.xyz;
	fragNormal = vertNormal;
	fragColour = vertColour;
	transformMatrix = transform;
	normalMatrix = transpose(inverse(transform)); // do this done cpu-side
}