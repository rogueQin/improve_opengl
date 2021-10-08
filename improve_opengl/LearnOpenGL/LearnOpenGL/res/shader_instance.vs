
#version 330 core

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec3 aTexCoords;
layout (location = 2) in vec2 transform;

out vec3 TexCoords;

void main()
{ 
	TexCoords = aTexCoords;
	vec2 aPos = aPosition * ((gl_InstanceID + 20) / 100.0);
	gl_Position = vec4(aPos + transform, 0.0f, 1.0f);
}
