
#version 330 core

out vec4 color;

in vec2 TexCoords;

// 深度值变换非线性
float LinearizeDepth(float depth);

uniform sampler2D texture_diffuse;
uniform float near;
uniform float far;

void main()
{
	// vec3 result = vec3(texture(texture_diffuse, TexCoords));
	float depthValue = texture(texture_diffuse, TexCoords).r;
	depthValue = LinearizeDepth(depthValue) / far;
	color = vec4(vec3(depthValue), 1.0f);
	// color = vec4(0.5);
}

float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0;
	return (2*near*far)/(far + near - z*(far - near));
}
