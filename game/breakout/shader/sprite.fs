#version 450 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D sprite; 
uniform vec3 spriteColor;

void main() {
	color = vec4(spriteColor, 1.0) * texture(sprite, TexCoords);
	//color = texture(image, TexCoords);
	//color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
