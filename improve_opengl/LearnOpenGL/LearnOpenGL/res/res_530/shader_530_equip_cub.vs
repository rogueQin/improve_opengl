#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

uniform mat4 model;

void main()
{
	gl_Position = model * vec4(aPosition, 1.0);
	// gl_Position = vec4(aPosition, 1.0);
}
