
#version 330 core

out vec4 color;
in vec2 TexCoords;

uniform sampler2D Image;

void main()
{	
	vec4 FragColor = texture(Image, TexCoords);
	color = vec4(FragColor.a,FragColor.a,FragColor.a, 1.0f);
}


