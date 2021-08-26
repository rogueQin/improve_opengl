
#version 330 core

out vec4 color;

struct Material{
	//(ͨ����ͬ�����������) vec3 ambient; // ��������
	sampler2D diffuse; // ��������ͼ
	sampler2D specular; // �������
	float shininess; // �����
};

struct Light{
	vec3 position;
	vec3 ambient; // ��������
	vec3 diffuse; // ���������
	vec3 specular; // �������
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;


void main()
{
	vec3 diffuseTexture = vec3(texture(material.diffuse, TexCoords));
	vec3 specularTexture = vec3(texture(material.specular, TexCoords));

	// ambient
	vec3 ambient = light.ambient * diffuseTexture;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * diffuseTexture);

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * specularTexture); 

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);
}

