
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

layout (std140) uniform Camera
{
	mat4 view;
	mat4 projection;
};

uniform mat4 transform;

out vec3 Normal;

out VS_OUT
{
	vec2 TexCoords;
	vec3 FragPos;
}vs_out;

void main()
{
	vs_out.TexCoords = aTexCoords;
	vs_out.FragPos = vec3(transform * vec4(aPosition, 1.0));
	Normal = mat3(transpose(inverse(transform))) * aNormal;

	gl_Position = projection * view * vec4(vs_out.FragPos, 1.0);
}
