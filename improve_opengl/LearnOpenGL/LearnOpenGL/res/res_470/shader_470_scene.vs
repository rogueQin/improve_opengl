#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

layout (std140) uniform Camera
{
 	mat4 view;
 	mat4 projection;
};

uniform mat4 model;
uniform vec3 directionLightPos;
uniform vec3 pointLightPos[3];
uniform vec3 viewPos;

out VS_OUT{
	vec2 TexCoords;
	vec3 TangentZeroPos;
	vec3 TangentDirectionLightPos;
	vec3 TangentPointLightPos[3];
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} vs_out;

void main()
{
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 T = normalize(normalMatrix * tangent);
	vec3 B = normalize(normalMatrix * bitangent);
	vec3 N = normalize(normalMatrix * aNormal);
	mat3 TBN = transpose(mat3(T, B, N));

	vec3 zero_pos = vec3(0);

	vs_out.TexCoords = aTexCoords;
	vs_out.TangentDirectionLightPos = TBN * directionLightPos;
	vs_out.TangentPointLightPos[0] = TBN * pointLightPos[0];
	vs_out.TangentPointLightPos[1] = TBN * pointLightPos[1];
	vs_out.TangentPointLightPos[2] = TBN * pointLightPos[2];
	vs_out.TangentZeroPos = TBN * zero_pos;
	vs_out.TangentViewPos = TBN * viewPos;
	vs_out.TangentFragPos = TBN * vec3(model * vec4(aPosition, 1.0));

	gl_Position = projection * view * model * vec4(aPosition, 1.0);
}
