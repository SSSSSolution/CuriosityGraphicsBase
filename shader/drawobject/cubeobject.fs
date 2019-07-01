#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D text;

void main()
{
	FragColor = texture(text, TexCoords);
	//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
