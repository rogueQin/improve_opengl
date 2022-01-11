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
uniform vec3 lightPos;
uniform vec3 viewPos;

out VS_OUT{
	vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
	vec3 Normal;
	vec3 ViewPos;
	vec3 LightPos;
} vs_out;

void main()
{
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 T = normalize(normalMatrix * tangent);
	vec3 B = normalize(normalMatrix * bitangent);
	vec3 N = normalize(normalMatrix * aNormal);
	// mat3 TBN = mat3(T, B, N);
	mat3 TBN = transpose(mat3(T, B, N));

	vs_out.FragPos = vec3(model * vec4(aPosition, 1.0));
	vs_out.TexCoords = aTexCoords;
	vs_out.TangentLightPos = TBN * lightPos;
	vs_out.TangentViewPos = TBN * viewPos;
	vs_out.TangentFragPos = TBN * vs_out.FragPos;
	vs_out.Normal = normalize(aNormal);
	vs_out.ViewPos = viewPos;
	vs_out.LightPos = lightPos;

	gl_Position = projection * view * model * vec4(aPosition, 1.0);
}
