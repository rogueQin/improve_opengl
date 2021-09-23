
#version 330 core

out vec4 color;

struct Material{
	//(ͨ����ͬ�����������) vec3 ambient; // ��������
	// ��������ͼ
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_diffuse4;
	sampler2D texture_diffuse5;

	// �������
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_specular3;
	sampler2D texture_specular4;
	sampler2D texture_specular5;

	float shininess; // �����
};


in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform sampler2D testTexture;
uniform samplerCube skybox;


float near = 0.1f;
float far = 100.0f;

void main()
{	

	vec3 I = normalize(FragPos - viewPos);
	vec3 R = reflect(I, normalize(Normal));
	// vec3 result = vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 result = vec3(texture(skybox, R));
	
	color = vec4(result, 1.0f);
}

