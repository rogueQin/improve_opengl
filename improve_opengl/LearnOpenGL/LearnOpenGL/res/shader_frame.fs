
#version 330 core

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D diffuse_texture;

void main()
{
	vec4 texColor = texture(diffuse_texture, TexCoords);
	// 反向
	// vec4 outColor = vec4(vec3(1.0f) - vec3(texColor), 1.0f);
	
	// 灰度
	// float average = (texColor.r + texColor.g + texColor.b) / 3.0f;
	// vec4 outColor = vec4(average, average, average, 1.0f);

	// 核效果
	// float offset = 1.0f / 300.0f;
	// vec2 offsets[9] = vec2[](
	// 	vec2(-offset, offset),
	// 	vec2(0.0f, offset),
	// 	vec2(offset, offset),
	// 	vec2(-offset, 0.0f),
	// 	vec2(0.0f, 0.0f),
	// 	vec2(offset, 0.0f),
	// 	vec2(-offset, -offset),
	// 	vec2(0.0f, -offset),
	// 	vec2(offset, -offset)
	// );
	// 
	// float kernal[9] = float[](
	// 	-1.0f, -1.0f, -1.0f,
	// 	-1.0f, 9.0f, -1.0f,
	// 	-1.0f, -1.0f, -1.0f
	// );
	// 
	// vec3 sampleTex[9];
	// for(int i = 0; i < 9; i ++)
	// {
	// 	sampleTex[i] = vec3(texture(diffuse_texture, TexCoords + offsets[i]));
	// }
	// vec3 kenal_col = vec3(0.0f);
	// for(int i = 0; i < 9; i ++)
	// {
	// 	kenal_col += sampleTex[i] * kernal[i];
	// }
	// vec4 outColor = vec4(kenal_col, 1.0f);

	// 模糊
	float offset = 1.0f / 300.0f;
	vec2 offsets[25] = vec2[](
		vec2(-offset*2, offset*2),	vec2(-offset, offset*2),	vec2(0.0f, offset*2),		vec2(offset, offset*2),		vec2(offset*2, offset*2),
		vec2(-offset*2, offset),	vec2(-offset, offset),		vec2(0.0f, offset),			vec2(offset, offset),		vec2(offset*2, offset),
		vec2(-offset*2, 0.0f),		vec2(-offset, 0.0f),		vec2(0.0f, 0.0f),			vec2(offset, 0.0f),			vec2(offset*2, 0.0f),
		vec2(-offset*2, -offset),	vec2(-offset, -offset),		vec2(0.0f, -offset),		vec2(offset, -offset),		vec2(offset*2, -offset),
		vec2(-offset*2, offset*2),	vec2(-offset, offset*2),	vec2(0.0f, offset*2),		vec2(offset, offset*2),		vec2(offset*2, offset*2)
	);
	
	float kernal[25] = float[](
		1.0f, 2.0f, 3.0f, 2.0f, 1.0f,
		2.0f, 3.0f, 4.0f, 3.0f, 2.0f,
		3.0f, 4.0f, 6.0f, 4.0f, 3.0f,
		2.0f, 3.0f, 4.0f, 3.0f, 2.0f,
		1.0f, 2.0f, 3.0f, 2.0f, 1.0f
	);
	
	vec3 sampleTex[25];
	for(int i = 0; i < 25; i ++)
	{
		sampleTex[i] = vec3(texture(diffuse_texture, TexCoords + offsets[i]));
	}
	vec3 kenal_col = vec3(0.0f);
	for(int i = 0; i < 25; i ++)
	{
		kenal_col += sampleTex[i] * (kernal[i] / 66);
	}
	vec4 outColor = vec4(kenal_col, 1.0f);

	// 边缘检测
	// float offset = 1.0f / 300.0f;
	// vec2 offsets[9] = vec2[](
	// 	vec2(-offset, offset),
	// 	vec2(0.0f, offset),
	// 	vec2(offset, offset),
	// 	vec2(-offset, 0.0f),
	// 	vec2(0.0f, 0.0f),
	// 	vec2(offset, 0.0f),
	// 	vec2(-offset, -offset),
	// 	vec2(0.0f, -offset),
	// 	vec2(offset, -offset)
	// );
	// 
	// float kernal[9] = float[](
	// 	1.0f, 1.0f, 1.0f,
	// 	1.0f, -8.0f, 1.0f,
	// 	1.0f, 1.0f, 1.0f
	// );
	// 
	// vec3 sampleTex[9];
	// for(int i = 0; i < 9; i ++)
	// {
	// 	sampleTex[i] = vec3(texture(diffuse_texture, TexCoords + offsets[i]));
	// }
	// vec3 kenal_col = vec3(0.0f);
	// for(int i = 0; i < 9; i ++)
	// {
	// 	kenal_col += sampleTex[i] * kernal[i];
	// }
	// vec4 outColor = vec4(kenal_col, 1.0f);


	color = outColor;
}
