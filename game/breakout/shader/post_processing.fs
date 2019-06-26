#version 450 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D scene;
uniform vec2	offsets[9];
uniform int edge_kernel[9];
uniform float blur_kernel[9];

uniform bool shake;

void main() {
	color = vec4(0.0f);
	vec3 samp[9];

	if (shake) {
		for (int i = 0; i < 9; i++)
			samp[i] = vec3(texture(scene, TexCoords.st + offsets[i]));
	}

	if (shake) {
		for (int i = 0; i < 9; i++) {
			color += vec4(samp[i] * blur_kernel[i], 0.0f);
		}
		//color.a = 1.0f;
		color = texture(scene, TexCoords);
	} else {  
		color = texture(scene, TexCoords);
	}
}
