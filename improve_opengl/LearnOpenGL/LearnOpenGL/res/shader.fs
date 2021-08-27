
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

// �۹��
struct SpotLight{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
// uniform DirectionLight directionLight;
// uniform PointLight pointLight;
uniform SpotLight spotLight;

void main()
{
	vec3 diffuseTexture = vec3(texture(material.diffuse, TexCoords));
	vec3 specularTexture = vec3(texture(material.specular, TexCoords));

	vec3 lightDir = normalize(spotLight.position - FragPos);
	float theta = dot(lightDir, normalize(-spotLight.direction));

	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);

	// ambient
	vec3 ambient = spotLight.ambient * diffuseTexture;
	vec3 result = ambient;

	if(theta > spotLight.outerCutOff)
	{
		// diffuse
		vec3 norm = normalize(Normal);
		float diff = max(dot(norm, lightDir), 0.0f);
		vec3 diffuse = spotLight.diffuse * (diff * diffuseTexture);
		diffuse *= intensity;
		
		// specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = spotLight.specular * (spec * specularTexture); 
		specular *= intensity;

		result = result + diffuse + specular;
	}

	color = vec4(result, 1.0f);
}

