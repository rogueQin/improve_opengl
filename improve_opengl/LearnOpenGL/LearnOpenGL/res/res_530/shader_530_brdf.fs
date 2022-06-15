
#version 330 core

out vec2 color;

in vec2 TexCoords;
in vec3 FragPos;

const float PI = 3.14159265359;

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

// 几何遮蔽函数(IBL)
float GeometrySchlickGGX(float NdotV, float roughness)
{
	float a = roughness;
	float k = a * a / 2.0;

	float nom = NdotV;
	float denom = NdotV * (1 - k) + k;

	return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
	float NdotV = max(dot(N,V), 0.0);
	float NdotL = max(dot(N,L), 0.0);
	float ggx1 = GeometrySchlickGGX(NdotV, roughness);
	float ggx2 = GeometrySchlickGGX(NdotL, roughness);

	return ggx1 * ggx2;
}

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

vec2 IntegrateBRDF(float NdotV, float roguness)
{
	// 观察向量
	vec3 view_dir;
	view_dir.x = sqrt(1.0 - NdotV * NdotV);
	view_dir.y = 0.0;
	view_dir.z = NdotV;

	// 法向量
	vec3 normal_dir = vec3(0.0, 0.0, 1.0);

	float A = 0.0;
	float B = 0.0;

	const uint SAMPLE_COUNT = 1024u;
	for(uint i = 0u; i < SAMPLE_COUNT; i++)
	{
		vec2 Xi = Hammersley(i, SAMPLE_COUNT);
		vec3 half_dir = ImportanceSampleGGX(Xi, normal_dir, roguness);
		vec3 light_dir = normalize(2.0 * dot(view_dir, half_dir) * half_dir - view_dir);

		float NdotL = max(light_dir.z, 0.0);
		float NdotH = max(half_dir.z, 0.0);
		float VdotH = max(dot(view_dir, half_dir), 0.0);

		if(NdotL > 0.0)
		{
			float G = GeometrySmith(normal_dir, view_dir, light_dir, roguness);
			float G_vis = (G * VdotH) / (NdotH * NdotV);

			// float D = DistributionGGX(normal_dir, half_dir, roguness);
			float Fc = pow(1.0 - VdotH, 5.0);
			
			A += (1.0 - Fc) * G_vis;
			B += Fc * G_vis;
		}
	}

	A /= float(SAMPLE_COUNT);
	B /= float(SAMPLE_COUNT);

	return vec2(A, B);
}

void main()
{
	vec2 integrateBRDF = IntegrateBRDF(TexCoords.x, TexCoords.y);
	// vec2 integrateBRDF = vec2(TexCoords.x, TexCoords.y);
	color = integrateBRDF;
}
