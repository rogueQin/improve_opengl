#version 330 core

layout (location = 0) out vec4 PositionColor;
layout (location = 1) out vec3 NormalColor;
layout (location = 2) out vec4 AlbedoSpecularColor;


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

	// 法线贴图
	sampler2D texture_normal1;
	sampler2D texture_normal2;
	sampler2D texture_normal3;
	sampler2D texture_normal4;
	sampler2D texture_normal5;

	// 视差贴图
	sampler2D texture_diplamence1;
	sampler2D texture_diplamence2;
	sampler2D texture_diplamence3;
	sampler2D texture_diplamence4;
	sampler2D texture_diplamence5;

	float shininess; // 反光度
};

in VS_OUT{
	vec2 TexCoords;
	vec3 FragPos;
	mat3 TBN;
} fs_in;

uniform Material material;

const float NEAR = 0.1; // Projection matrix's near plane distance
const float FAR = 50.0f; // Projection matrix's far plane distance

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));	
}

void main()
{
	PositionColor.xyz = fs_in.FragPos;
	PositionColor.a = LinearizeDepth(gl_FragCoord.z);

	vec3 normalTexture = vec3(texture(material.texture_normal1, fs_in.TexCoords));
	vec3 diffuseTexture = vec3(texture(material.texture_diffuse1, fs_in.TexCoords));
	vec3 specularTexture = vec3(texture(material.texture_specular1, fs_in.TexCoords));
	normalTexture = normalize(normalTexture * 2.0 - 1.0);
	NormalColor = normalize(fs_in.TBN * normalTexture);
	
	AlbedoSpecularColor = vec4(diffuseTexture, specularTexture.r);
}

