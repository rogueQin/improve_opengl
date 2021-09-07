
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

uniform float outline;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
	TexCoords = aTexCoords;
	Normal = mat3(transpose(inverse(transform))) * aNormal;
	vec3 outline_pos = Normal * outline;
	FragPos = vec3(transform * vec4(aPosition + outline_pos, 1.0));
	gl_Position = projection * view * vec4(FragPos, 1.0);
}
