#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec2 vertexUV;
in layout(location=2) vec3 vertexNormal_modelspace;

out vec2 UV;
out vec3 Position_cameraspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;
out vec3 addLightDirection_cameraspace;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 Projection;
uniform vec3 LightPosition_cameraspace;
uniform vec3 addLightPosition_cameraspace;

void main()
{
	gl_Position = Projection*ViewMatrix*ModelMatrix*vec4(position, 1.0);

	Position_cameraspace = (ViewMatrix*ModelMatrix*vec4(position, 1.0)).xyz;

	vec3 Position_cameraspace = (ViewMatrix*ModelMatrix*vec4(position, 1.0)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - Position_cameraspace;

	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
	addLightDirection_cameraspace = addLightPosition_cameraspace + EyeDirection_cameraspace;

	Normal_cameraspace = (ViewMatrix*ModelMatrix*vec4(vertexNormal_modelspace, 0.0)).xyz;

	UV = vertexUV;
}