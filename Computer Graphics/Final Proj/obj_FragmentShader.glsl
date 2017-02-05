#version 430

in vec2 UV;
in vec3 Position_cameraspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 addLightDirection_cameraspace;

out vec3 color;

uniform sampler2D myTextureSampler;
uniform sampler2D myTextureSampler2;
uniform samplerCube skybox;
uniform vec3 LightPosition_cameraspace;
uniform vec3 addLightPosition_cameraspace;
uniform float LightPower_Diffuse;
uniform float LightPower_Specular;
uniform float addLightPower_Diffuse;
uniform float addLightPower_Specular;
uniform bool normalMapping_flag;
uniform bool multipleMapping_flag;
uniform float lambda;
uniform mat4 ViewMatrix;

void main()
{
	vec3 incident_eye = normalize(Position_cameraspace);
	vec3 normal = normalize(Normal_cameraspace);

	vec3 reflected = reflect(incident_eye, normal);
	// convert from eye to world space
	reflected = vec3(inverse(ViewMatrix) * vec4(reflected, 0.0)) * vec3(1.0,-1.0,1.0);
	vec3 frag_colour = texture(skybox, reflected).rgb;

	vec3 LightColor = vec3(1,1,1);
	vec3 addLightColor = vec3(0,0,1);

	vec3 MaterialDiffuseColor = texture(myTextureSampler, UV).rgb;
	if (multipleMapping_flag) {
		MaterialDiffuseColor = lambda*texture(myTextureSampler, UV).rgb + (1-lambda)*texture(myTextureSampler2, UV).rgb;
	}
	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1)*MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);

	float distance = length(LightPosition_cameraspace - Position_cameraspace);

	vec3 n = normalize(Normal_cameraspace);
	if (normalMapping_flag){
		n = texture(myTextureSampler2, UV).rgb;
		n = normalize(n*2.0-1.0);
	}

	vec3 l = normalize(LightDirection_cameraspace);
	float cosTheta = clamp(dot(n,l),0,1);

	vec3 E = normalize(EyeDirection_cameraspace);
	vec3 R = reflect(-l, n);
	float cosAlpha = clamp(dot(E,R),0,1);

	color = MaterialAmbientColor + MaterialDiffuseColor*LightColor*LightPower_Diffuse*cosTheta/(distance*distance) + MaterialSpecularColor*LightColor*LightPower_Specular*pow(cosAlpha,5)/(distance*distance);

	vec3 addMaterialDiffuseColor = texture(myTextureSampler, UV).rgb;
	if (multipleMapping_flag) {
		addMaterialDiffuseColor = lambda*texture(myTextureSampler, UV).rgb + (1-lambda)*texture(myTextureSampler2, UV).rgb;
	}
	vec3 addMaterialAmbientColor = vec3(0.1,0.1,0.1)*addMaterialDiffuseColor;
	vec3 addMaterialSpecularColor = vec3(0.3,0.3,0.3);

	float adddistance = length(addLightPosition_cameraspace - Position_cameraspace);

	vec3 addl = normalize(addLightDirection_cameraspace);
	float addcosTheta = clamp(dot(n,addl),0,1);

	vec3 addR = reflect(-addl, n);
	float addcosAlpha = clamp(dot(E,addR),0,1);

	color += addMaterialAmbientColor + addMaterialDiffuseColor*addLightColor*addLightPower_Diffuse*addcosTheta/(adddistance*adddistance) + addMaterialSpecularColor*addLightColor*addLightPower_Specular*pow(addcosAlpha,5)/(adddistance*adddistance);
	color += vec3(0.2,0.2,0.2) * frag_colour;
}