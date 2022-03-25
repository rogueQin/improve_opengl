
#version 330 core

out vec4 color;

in vec4 FragPos;

// uniform vec3 camPos;
uniform samplerCube image_cube;
uniform float roughness;

const float PI = 3.14159265359;

float RadicalInverse_VdC(uint bits) 
{
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

vec2 Hammersley(uint i, uint N)
{
    return vec2(float(i)/float(N), RadicalInverse_VdC(i));
}

vec3 ImportanceSampleGGX(vec2 Xi, vec3 normal, float roughness)
{
	float a = roughness * roughness;
	float phi = 2.0 * PI * Xi.x;
	float cosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a * a - 1.0) * Xi.y));
	float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

	vec3 half_dir;
	half_dir.x = cos(phi) * sinTheta;
	half_dir.y = sin(phi) * sinTheta;
	half_dir.z = cosTheta;

	vec3 up = abs(normal.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
	vec3 tangent = normalize(cross(up, normal));
	vec3 bitangent = cross(normal, tangent);

	vec3 samplerVec = tangent * half_dir.x + bitangent * half_dir.y + normal * half_dir.z;
	return normalize(samplerVec);
}

// 法线分布函数
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(N,H), 0.0);
	float NdotH2 = NdotH * NdotH;

	float nom = a2;
	float denom = NdotH2 * (a2 - 1.0) + 1.0;
	denom = PI * denom * denom;

	return nom / denom;
}

void main()
{
	vec3 normal_dir = normalize(vec3(FragPos));
	vec3 reflect_dir = normal_dir;
	vec3 view_dir = normal_dir;

	const uint SAMPLE_COUNT = 32u;
	vec3 prefilteredColor = vec3(0.0);
	float totalWeight = 0.0;

	for(uint i = 0u; i < SAMPLE_COUNT; i++)
	{
		vec2 Xi = Hammersley(i, SAMPLE_COUNT);
		vec3 half_dir = ImportanceSampleGGX(Xi, normal_dir, roughness);
		vec3 light_dir = normalize(2.0 * dot(view_dir, half_dir) * half_dir - view_dir);

		float NDotL = max(dot(normal_dir, light_dir), 0.0);
		if(NDotL > 0.0)
		{

			float distribution = DistributionGGX(normal_dir, half_dir, roughness);
			float NDotH = max(dot(normal_dir, half_dir), 0.0);
			float HDotV = max(dot(half_dir, view_dir), 0.0);
			float pdf = distribution * NDotH / (4.0 * HDotV) + 0.0001;

			float resolution = 512.0;
			float saTexel = 4.0 * PI / (6.0 + resolution * resolution);
			float saSample = 1.0 / (float(SAMPLE_COUNT) * pdf + 0.0001);

			float mipLevel = roughness == 0.0 ? 0.0 : 0.5 * log2(saSample / saTexel);

			// prefilteredColor += texture(image_cube, light_dir).rgb * NDotL;
			prefilteredColor += textureLod(image_cube, light_dir, mipLevel).rgb * NDotL;
			totalWeight += NDotL;
		}
	}

	prefilteredColor = prefilteredColor / totalWeight;

	// prefilteredColor = texture(image_cube, normal_dir).rgb;

	color = vec4(prefilteredColor, 1.0);
}