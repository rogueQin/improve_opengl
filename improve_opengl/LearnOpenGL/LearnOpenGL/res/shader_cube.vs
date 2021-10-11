
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
// layout (location = 2) in vec2 aTexCoords;

layout (std140) uniform Camera
{
	mat4 view;
	mat4 projection;
};

uniform mat4 transform;

//out VS_OUT{
//	vec2 texCoords;
//}vs_out;

void main()
{ 
	// vs_out.texCoords = aTexCoords;
	vec3 FragPos = vec3(transform * vec4(aPosition, 1.0));

	gl_Position = projection * view * vec4(FragPos, 1.0);
}
