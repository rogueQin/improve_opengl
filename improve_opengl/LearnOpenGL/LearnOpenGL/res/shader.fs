

#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;

uniform vec3 lightPos;
uniform vec3 objColor;
uniform vec3 lightColor;

void main()
{
	float ambientStrength = 0.1f;

	float specularStrength = 0.5f;

	vec3 normal = normalize(Normal);

	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 lightDir = normalize(lightPos - FragPos);

	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32) * specularStrength;

	float diff = max(dot(normal, lightDir), 0.0);

	color = vec4(objColor * lightColor * (ambientStrength + diff + spec), 1.0);
	// color = vec4(spec, 1.0, 1.0, 1.0);
}

