
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

	// 法线贴图
	sampler2D texture_normal1;
	sampler2D texture_normal2;
	sampler2D texture_normal3;
	sampler2D texture_normal4;
	sampler2D texture_normal5;

	// 镜面光照
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_specular3;
	sampler2D texture_specular4;
	sampler2D texture_specular5;

	float shininess; // 反光度
};

// 平行光
struct DirectionLight{
	// vec3 position;
	// vec3 direction; // 
	vec3 ambient; // 环境光照
	vec3 diffuse; // 漫反射光照
	vec3 specular; // 镜面光照
};

// 点光源
struct PointLight{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

// 聚光灯
struct SpotLight{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
};

// 平行光
vec3 calcDirectionLight(DirectionLight light);
// 点光源
vec3 calcPointLight(PointLight light, vec3 normal); //, vec3 viewDir, vec3 fragPos);
// 聚光灯
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos);


in VS_OUT{
	vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
	vec3 Normal;
	vec3 ViewPos;
	vec3 LightPos;
} fs_in;


uniform Material material;
uniform DirectionLight directionLight; 
uniform PointLight pointLight;

// #define POINT_LIGHT_COUNT 3
// uniform PointLight pointLights[POINT_LIGHT_COUNT];


void main()
{
	vec3 result = vec3(0.0f);
	
	// result += calcPointLight(pointLight, normal);
	// vec3 normal = fs_in.Normal;
	
	result += calcDirectionLight(directionLight);
	
	// vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	// result += lightDir;

	color = vec4(result, 1.0f);
}

// 平行光
vec3 calcDirectionLight(DirectionLight light)
{
	// 贴图
	vec3 diffuseTexture = vec3(texture(material.texture_diffuse1, fs_in.TexCoords));
	vec3 specularTexture = vec3(texture(material.texture_specular1, fs_in.TexCoords));
	// vec3 specularTexture = vec3(1.0);
	vec3 normal = vec3(texture(material.texture_normal1, fs_in.TexCoords));
	normal = normalize(normal * 2.0 - 1.0);
	// normal = normalize(fs_in.Normal);
	vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);

	// ambient
	vec3 ambient = light.ambient * diffuseTexture;
	
	// diffuse
	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * diffuseTexture);
	
	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * specularTexture); 

	// float shadow = ShadowCalculation(FragPosLightSpace);

	// float shadow = 0.0f;

	return ambient + diffuse + specular;
	// return specular;
}

// 点光源
vec3 calcPointLight(PointLight light, vec3 normal) // , vec3 viewDir, vec3 fragPos)
{
	// 贴图
	vec3 diffuseTexture = vec3(texture(material.texture_diffuse1, fs_in.TexCoords));
	vec3 specularTexture = vec3(1.0f);

	float distance = length(fs_in.TangentLightPos - fs_in.TangentFragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	// ambient
	vec3 ambient = light.ambient * diffuseTexture * attenuation;
	
	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
	vec3 halfwayDir = normalize(viewDir + lightDir);

	// diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * diffuseTexture) * attenuation;

	// specular
	float spec = 0.0f;
	spec = pow(max(dot(normal, -halfwayDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * specularTexture);//  * attenuation; 

	return ambient + diffuse + specular;
}

// 聚光灯
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
	// 贴图
	vec3 diffuseTexture = vec3(texture(material.texture_diffuse1, fs_in.TexCoords));
	vec3 specularTexture = vec3(texture(material.texture_specular1, fs_in.TexCoords));

	// ambient
	vec3 result = light.ambient * diffuseTexture;
	vec3 ambient = light.ambient * diffuseTexture;

	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	if (theta > light.outerCutOff)
	{
		// diffuse
		float diff = max(dot(normal, lightDir), 0.0f);
		vec3 diffuse = light.diffuse * (diff * diffuseTexture);
		diffuse *= intensity;

		// specular
		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * (spec * specularTexture); 
		specular *= intensity;

		result = ambient + diffuse + specular;
	}
	
	return result;
}

