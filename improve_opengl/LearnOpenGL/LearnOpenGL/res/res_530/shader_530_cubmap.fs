
#version 330 core

out vec4 color;
in vec3 FragPos; 
uniform samplerCube image_cube;

uniform float mip_level;



// uniform sampler2D image_cube;

// const vec2 invAtan = vec2(0.1591, 0.3183);
// vec2 SampleSphericalMap(vec3 v)
// {
//     vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
//     uv *= invAtan;
//     uv += 0.5;
//     return uv;
// }

void main()
{

	// vec2 uv = SampleSphericalMap(normalize(vec3(FragPos)));
	// vec3 cube_color = texture(image_cube, uv).rgb;

	vec3 cube_color = textureLod(image_cube, FragPos, mip_level).rgb;
	// vec3 cube_color = texture(image_cube, FragPos).rgb;
	cube_color = cube_color / (cube_color + vec3(1.0));
	cube_color = pow(cube_color, vec3(1.0 / 2.2)); 

	color = vec4(cube_color, 1.0);
}
