#version 430

in layout(location=0) vec3 position;

uniform mat4 M;
uniform mat4 view;
uniform mat4 projection;

out vec3 TexCoords;

void main()
{
	vec4 pos = projection * view * M * vec4(position, 1.0);
	gl_Position = pos;
	TexCoords = position;
}