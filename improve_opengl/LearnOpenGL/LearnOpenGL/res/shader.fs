
#version 330 core

out vec4 color;

struct Material{
	//(通常等同于漫反射光照) vec3 ambient; // 环境光照
	// 漫反射贴图
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_diffuse4;
	sampler2D texture_diffuse5;

	// 镜面光照
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_specular3;
	sampler2D texture_specular4;
	sampler2D texture_specular5;

	float shininess; // 反光度
};

in vec3 Normal;

in VS_OUT
{
	vec2 TexCoords;
	vec3 FragPos;
}fs_in;

uniform vec3 viewPos;
uniform Material material;
uniform sampler2D testTexture;
uniform samplerCube skybox;

float near = 0.1f;
float far = 100.0f;

void main()
{	
	float ratio = 1.0f / 1.52f;
	vec3 I = normalize(fs_in.FragPos - viewPos);
	// vec3 R = reflect(I, normalize(Normal));
	vec3 R = refract(I, normalize(Normal), ratio);
	// vec3 result = vec3(texture(material.texture_diffuse1, fs_in.TexCoords));
	vec3 result = vec3(texture(skybox, R));
	
	color = vec4(result, 1.0f);
}

