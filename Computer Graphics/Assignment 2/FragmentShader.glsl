#version 400

in vec2 UV;
in vec3 Position_cameraspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

out vec3 color;

uniform sampler2D myTextureSampler;
uniform vec3 LightPosition_cameraspace;
uniform float LightPower_Diffuse;
uniform float LightPower_Specular;

void main()
{

	vec3 LightColor = vec3(1,1,1);

	vec3 MaterialDiffuseColor = texture(myTextureSampler, UV).rgb;
	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1)*MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);

	float distance = length(LightPosition_cameraspace - Position_cameraspace);

	vec3 n = normalize(Normal_cameraspace);
	vec3 l = normalize(LightDirection_cameraspace);
	float cosTheta = clamp(dot(n,l),0,1);

	vec3 E = normalize(EyeDirection_cameraspace);
	vec3 R = reflect(-l, n);
	float cosAlpha = clamp(dot(E,R),0,1);

	color = MaterialAmbientColor + MaterialDiffuseColor*LightColor*LightPower_Diffuse*cosTheta/(distance*distance) + MaterialSpecularColor*LightColor*LightPower_Specular*pow(cosAlpha,5)/(distance*distance);
}