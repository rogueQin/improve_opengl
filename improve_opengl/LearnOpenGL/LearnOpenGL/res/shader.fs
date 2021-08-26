
#version 330 core

out vec4 color;

struct Material{
	//(ͨ����ͬ�����������) vec3 ambient; // ��������
	sampler2D diffuse; // ��������ͼ
	sampler2D specular; // �������
	float shininess; // �����
};

// ƽ�й�
struct DirectionLight{
	// vec3 position;
	vec3 direction; // 
	vec3 ambient; // ��������
	vec3 diffuse; // ���������
	vec3 specular; // �������
};

// ���Դ
struct PointLight{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
// uniform DirectionLight directionLight;
uniform PointLight pointLight;


void main()
{
	vec3 diffuseTexture = vec3(texture(material.diffuse, TexCoords));
	vec3 specularTexture = vec3(texture(material.specular, TexCoords));

	float diatance = length(pointLight.position - FragPos);
	float attenuation = 1.0 / (pointLight.constant + pointLight.linear * diatance + pointLight.quadratic * diatance * diatance);

	// ambient
	vec3 ambient = pointLight.ambient * diffuseTexture;
	ambient *= attenuation;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(pointLight.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = pointLight.diffuse * (diff * diffuseTexture);
	diffuse *= attenuation;

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = pointLight.specular * (spec * specularTexture); 
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);
}

