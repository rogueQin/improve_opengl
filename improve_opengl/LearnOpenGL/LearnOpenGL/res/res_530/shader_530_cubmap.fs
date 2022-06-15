
#version 330 core

out vec4 color;
in vec3 FragPos; 
uniform samplerCube image_cube;

void main()
{

	// vec2 uv = SampleSphericalMap(normalize(vec3(FragPos)));
	// vec3 cube_color = texture(image_cube, uv).rgb;
	vec3 cube_color = texture(image_cube, FragPos).rgb;
	cube_color = cube_color / (cube_color + vec3(1.0));
	cube_color = pow(cube_color, vec3(1.0 / 2.2)); 

	color = vec4(cube_color, 1.0);
}
