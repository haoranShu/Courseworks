#version 430

out vec4 daColor;
in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{
	//reverse the y coordinates as the texture coordinates
	daColor = texture(skybox,TexCoords * vec3(1.0,-1.0,1.0));
}