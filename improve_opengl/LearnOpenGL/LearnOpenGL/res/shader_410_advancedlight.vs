#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
// layout (location = 3) in mat4 instanceMat;

layout (std140) uniform Camera
{
 	mat4 view;
 	mat4 projection;
};

uniform mat4 transform;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

void main()
{ 
	Normal = aNormal;
	TexCoords = aTexCoords;
	FragPos = vec3(transform * vec4(aPosition, 1.0));

	gl_Position = projection * view * vec4(FragPos, 1.0);
}
