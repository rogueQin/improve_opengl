

#version 330 core

out vec4 color;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D fallTexture;
uniform sampler2D faceTexture;

void main()
{
	color = mix(texture(fallTexture, texCoord) , texture(faceTexture, texCoord), 0.2) * vec4(vertexColor, 1.0);
}

