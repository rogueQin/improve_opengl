
#version 330 core

uniform vec3 LightColor;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

void main()
{
	FragColor = vec4(LightColor, 1.0f);
	BrightColor = vec4(LightColor, 1.0f);
}
