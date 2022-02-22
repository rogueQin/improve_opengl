
#version 330 core

out vec4 color;
in vec2 TexCoords;

uniform sampler2D ImagePosition;
uniform sampler2D ImageNormal;
uniform sampler2D ImageAlbedoSpecular;
uniform sampler2D ImageSSAO;

struct Light{
	vec3 Position;
	vec3 Color;
};

const int NR_LIGHRTS = 16;
uniform Light lights[NR_LIGHRTS];
uniform vec3 viewPos;

void main()
{	
	vec3 FragPos = texture(ImagePosition, TexCoords).rgb;
	vec3 Normal = texture(ImageNormal, TexCoords).rgb;
	vec3 Albedo = texture(ImageAlbedoSpecular, TexCoords).rgb;
	float Specular = texture(ImageAlbedoSpecular, TexCoords).a;
	float SSAO_value = texture(ImageSSAO, TexCoords).r;

	// vec3 lighting = Albedo * 0.1 * SSAO_value;
	vec3 lighting = Albedo * 0.1;
	vec3 viewDir = normalize(viewPos - FragPos);

	for(int i = 0; i < NR_LIGHRTS; i ++)
	{
		vec3 lightDir = normalize(lights[i].Position - FragPos);
		vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo * lights[i].Color * 0.1;
		lighting += diffuse;
	}
	lighting *= SSAO_value;
	// color = vec4(SSAO_value, SSAO_value, SSAO_value, 1.0);
	color = vec4(lighting.r,lighting.g,lighting.b, 1.0f);
}


