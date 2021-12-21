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

uniform mat4 lightSpaceMatrix;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
out vec4 FragPosLightSpace;

void main()
{ 
	vec3 render_move = vec3(-10, -10, 0);
	Normal = mat3(transpose(inverse(transform))) * aNormal;
	TexCoords = aTexCoords;
	FragPos = vec3(transform * vec4(aPosition, 1.0));
	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);

	gl_Position = projection * view * vec4(FragPos, 1.0);
}
