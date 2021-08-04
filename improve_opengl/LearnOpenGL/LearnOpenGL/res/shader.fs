

#version 330 core

out vec4 color;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D ourTexture;

void main()
{
	color = texture(ourTexture, texCoord) * vec4(vertexColor, 1.0);
	// color = vec4(vertexColor, 1.0);
}

