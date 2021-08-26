
#version 330 core

out vec4 color;

struct Material{
	//(通常等同于漫反射光照) vec3 ambient; // 环境光照
	sampler2D diffuse; // 漫反射贴图
	sampler2D specular; // 镜面光照
	float shininess; // 反光度
};

struct Light{
	vec3 position;
	vec3 ambient; // 环境光照
	vec3 diffuse; // 漫反射光照
	vec3 specular; // 镜面光照
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

