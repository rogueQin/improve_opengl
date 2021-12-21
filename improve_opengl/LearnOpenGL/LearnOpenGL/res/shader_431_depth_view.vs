#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

out vec2 TexCoords;

void main()
{
	TexCoords = aTexCoords;
	gl_Position = projection * view * transform * vec4(aPosition, 1.0);
}
