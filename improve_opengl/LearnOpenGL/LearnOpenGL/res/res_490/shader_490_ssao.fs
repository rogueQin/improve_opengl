
#version 330 core

out float SSAOColor;
in vec2 TexCoords;

uniform sampler2D ImagePosition;
uniform sampler2D ImageNormal;
uniform sampler2D ImageAlbedoSpecular;
uniform sampler2D ImageNorise;

const int NR_SAMPLES = 64;
uniform vec3 samples[NR_SAMPLES];
uniform float radius;

uniform mat4 projection;


const vec2 noiseScale = vec2(800.0f/4.0f, 600.0f/4.0f); 

const float NEAR = 0.1; // Projection matrix's near plane distance
const float FAR = 50.0f; // Projection matrix's far plane distance

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));	
}

void main()
{
	vec3 FragPos = texture(ImagePosition, TexCoords).xyz;
	vec3 Normal = texture(ImageNormal, TexCoords).rgb;

	vec3 randomVec = texture(ImageNorise, TexCoords * noiseScale).xyz;
	vec3 tangent = normalize(randomVec - Normal * dot(randomVec, Normal));
	vec3 bitangent = cross(Normal, tangent);

	mat3 TBN = mat3(tangent, bitangent, Normal);

	float occlusion = 0.0;

	for(int i = 0; i < NR_SAMPLES; i++)
	{
		vec3 sample_pos = TBN * samples[i];
		sample_pos = FragPos + sample_pos * radius;

		vec4 offset = vec4(sample_pos, 1.0);
		offset = projection * offset;
		offset.xyz /= offset.w;
		offset.xyz = offset.xyz * 0.5 + 0.5;
		float sample_depth = -texture(ImagePosition, offset.xy).w;
		
		float rangeCheck = smoothstep(0.0, 1.0, radius / abs(FragPos.z - sample_depth));
		occlusion += (sample_depth >= sample_pos.z ? 1.0 : 0.0) * rangeCheck;
	}
	occlusion = 1.0 - (occlusion / NR_SAMPLES);
	SSAOColor = occlusion;
}


