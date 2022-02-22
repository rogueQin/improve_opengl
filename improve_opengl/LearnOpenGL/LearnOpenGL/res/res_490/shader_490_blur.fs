
#version 330 core

out float blurColor;
in vec2 TexCoords;

uniform sampler2D ImageSSAO;

void main()
{	
	float SSAO_value = texture(ImageSSAO, TexCoords).r;
	vec2 texelSize = 1.0 / vec2(textureSize(ImageSSAO, 0));

	float result = 0.0;
	for(int i = -2; i < 2; i++)
	{
		for(int j = -2; j < 2; j++)
		{
			vec2 offset = vec2(i, j) * texelSize;
			result += texture(ImageSSAO, TexCoords + offset).r;
		}
	}

	blurColor = result / 16;
}


