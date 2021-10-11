
#version 330 core

out vec4 color;
in vec2 TexCoords;

uniform sampler2D screen_texture;

void main()
{	
	vec3 result = vec3(texture(screen_texture, TexCoords));
	
	color = vec4(result, 1.0f);
}

