
#version 330 core

out vec4 color;

in vec2 TexCoords;
uniform float exposure;
uniform sampler2D TextureHDR;


void main()
{	
	float gamma = 2.2;
	vec3 hdrColor = vec3(texture(TextureHDR, TexCoords));

	// vec3 mapped = hdrColor / (hdrColor + vec3(1.0));

	vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
	mapped = vec3(pow(mapped.x, 1.0 / gamma), pow(mapped.y, 1.0 / gamma), pow(mapped.z, 1.0 / gamma));

	color = vec4(mapped, 1.0f);
}


