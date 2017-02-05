#version 430

in layout(location=0) vec3 position;

uniform mat4 MVP;

out vec3 theColor;

void main()
{
	vec4 v = vec4(position, 1.0);
	vec4 new_position = MVP * v;
	gl_Position = new_position;	
	theColor = vec3(1.0,1.0,0);
}