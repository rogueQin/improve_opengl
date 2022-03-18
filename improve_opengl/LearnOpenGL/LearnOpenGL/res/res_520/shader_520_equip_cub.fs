
#version 330 core

out vec4 color;

in vec4 FragPos;

// uniform vec3 camPos;

uniform sampler2D image_equimap;

const vec2 invAtan = vec2(0.1591, 0.3183);

vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}

void main()
{
	vec2 uv = SampleSphericalMap(normalize(vec3(FragPos)));
	vec3 cube_color = texture(image_equimap, uv).rgb;

	color = vec4(cube_color, 1.0);
}
