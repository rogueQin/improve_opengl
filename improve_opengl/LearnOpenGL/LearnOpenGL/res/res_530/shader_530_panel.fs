
#version 330 core

out vec4 color;
in vec3 FragPos; 
in vec2 TexCoods;

uniform sampler2D image_BRDF;

void main()
{
	vec2 cube_color = texture(image_BRDF, TexCoods).rg;
	color = vec4(cube_color, 1.0, 1.0);
	// color = vec4(1.0);
}
