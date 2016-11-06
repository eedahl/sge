#version 400 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec3 fragColour;
in mat4 transformMatrix;
in mat4 normalMatrix;

uniform mat4 camera;
//uniform vec3 ambiance;
//uniform light lightSource;

// helpful source:
// http://www.tomdalling.com/blog/modern-opengl/06-diffuse-point-lighting/

void main(void)
{
	vec3 ambience = vec3(0.11, 0.11, 0.11);

	vec3 worldPosition = (transformMatrix * vec4(fragPosition, 1)).xyz;
	vec3 worldNormal = normalize((normalMatrix * vec4(fragNormal,1)).xyz);

	//test light, world coords
	vec3 lightPosition = vec3(0.f, 0.f, 1.f);
	vec3 lightIntensities = vec3(0.3, 0.3, 0.3);

	vec3 surfaceToLight = normalize(lightPosition - worldPosition);
	
	//diffuse light
	float brightness = clamp(dot(surfaceToLight, worldNormal), 0, 1);

	//specular light
	vec3 cameraPosition = vec3(-camera[3].x, -camera[3].y, -camera[3].z); // not completely right: the projection may move, too
	vec3 surfaceToCamera = normalize(cameraPosition - worldPosition);
	vec3 reflectedRay = reflect(-surfaceToLight, worldNormal);
	float specularBrightness = pow(clamp(dot(surfaceToCamera, reflectedRay), 0, 1), 8);
	
	vec3 surfaceColour = fragColour;

	gl_FragColor = vec4(ambience + brightness * lightIntensities * surfaceColour + specularBrightness * lightIntensities * surfaceColour, 1);
}