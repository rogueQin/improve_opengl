
#version 330 core

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D diffuse_texture;

void main()
{
	vec4 texColor = texture(diffuse_texture, TexCoords);
	// if(texColor.a < 0.1f)
	// {
	// 	discard;
	// }
	color = texColor;
}
