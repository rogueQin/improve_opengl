

#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 objColor;
uniform vec3 lightColor;

void main()
{
	float ambientStrength = 0.1f;

	vec3 lightDir = normalize(lightPos);

	float diff = max(dot(Normal, lightDir), 0.0);

	color = vec4(objColor * lightColor * (ambientStrength + diff), 1.0);
}

