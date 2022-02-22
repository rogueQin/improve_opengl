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
uniform vec3 viewPos;

out VS_OUT{
	vec2 TexCoords;
	vec3 FragPos;
	vec3 Normal;
	mat3 TBN;
} vs_out;

void main()
{
	// mat3 normalMatrix = transpose(inverse(mat3(model)));
	// vec3 T = normalize(normalMatrix * tangent);
	// vec3 B = normalize(normalMatrix * bitangent);
	// vec3 N = normalize(normalMatrix * aNormal);

	vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
	vec3 B = normalize(vec3(model * vec4(bitangent, 0.0)));
	vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));

	vs_out.TBN = mat3(T, B, N);
	vs_out.TexCoords = aTexCoords;
	vs_out.Normal = N;
	vs_out.FragPos = vec3(view * model * vec4(aPosition, 1.0));

	gl_Position = projection * view * model * vec4(aPosition, 1.0);
}
