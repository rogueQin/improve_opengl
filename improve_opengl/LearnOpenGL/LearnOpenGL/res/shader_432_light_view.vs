#version 330 core

layout (location = 0) in vec3 aPosition;

uniform mat4 transform;
uniform mat4 light_space_matrix;

void main()
{
	gl_Position = light_space_matrix * transform * vec4(aPosition, 1.0);


}
