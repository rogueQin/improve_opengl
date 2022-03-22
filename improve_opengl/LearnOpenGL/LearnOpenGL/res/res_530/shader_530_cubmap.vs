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

out vec3 FragPos;

void main()
{
	FragPos = vec3(model * vec4(aPosition, 1.0));

	mat4 sky_view = mat4(mat3(view));

	vec4 pos = projection * sky_view * vec4(FragPos, 1.0);

	// gl_Position = vec4(pos.x, pos.y, pos.w - 0.00001, pos.w);
	gl_Position = pos.xyww;
}
