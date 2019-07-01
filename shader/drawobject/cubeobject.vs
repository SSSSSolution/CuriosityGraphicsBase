#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 project;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = project * view * model * vec4(aPos, 1.0);
	TexCoords = aTexCoords;
}
