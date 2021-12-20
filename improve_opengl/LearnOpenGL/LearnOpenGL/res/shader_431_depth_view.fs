
#version 330 core

out vec4 color;

in vec2 TexCoords;

uniform sampler2D texture_diffuse;

void main()
{
	// vec3 result = vec3(texture(texture_diffuse, TexCoords));
	float depthValue = texture(texture_diffuse, TexCoords).r;
	// vec3(depthValue), 
	color = vec4(vec3(depthValue), 1.0f);
}

