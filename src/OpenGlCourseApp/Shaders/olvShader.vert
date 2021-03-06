#version 450

layout (location = 0) in vec3 pos;

out vec3 FragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() 
{
	gl_Position = projection * view * model * vec4(pos, 1.0f);
	
	FragPos = (model * vec4(pos, 1.0f)).xyz;

}