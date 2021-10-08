
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

layout (std140) uniform Camera
{
	mat4 view;
	mat4 projection;
};

out VS_OUT{
	vec3 normal;
}vs_out;

uniform mat4 transform;

void main()
{ 
	vec3 FragPos = vec3(transform * vec4(aPosition, 1.0));
	gl_Position = projection * view * vec4(FragPos, 1.0);
	mat3 normalMatrix = mat3(transpose(inverse(view * transform)));
	vs_out.normal = normalize(vec3(projection * vec4(normalMatrix * aNormal, 0.0))) ;
}
