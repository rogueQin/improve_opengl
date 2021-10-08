
#version 330 core

out vec4 color;
in vec3 TexCoords;


void main()
{
	color = vec4(TexCoords, 1.0f);
}

