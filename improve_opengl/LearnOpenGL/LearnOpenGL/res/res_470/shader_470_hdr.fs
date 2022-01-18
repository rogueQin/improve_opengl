
#version 330 core

out vec4 color;
in vec2 TexCoords;

uniform sampler2D FragImg;
uniform sampler2D BloomImg;

void main()
{	
	vec3 FragColor = vec3(texture(FragImg, TexCoords));
	vec3 BloomColor = vec3(texture(BloomImg, TexCoords));

	color = vec4(FragColor + BloomColor, 1.0f);
}


