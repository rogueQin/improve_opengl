
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 0) in vec3 aNormal;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;

void main()
{
	FragPos = vec3(transform * vec4(aPosition, 1.0));
	Normal = aNormal; // vec3(transform * vec4(aNormal, 1.0));
	gl_Position = projection * view * transform * vec4(aPosition, 1.0);
}
