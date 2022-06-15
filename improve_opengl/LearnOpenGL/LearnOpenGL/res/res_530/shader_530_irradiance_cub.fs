
#version 330 core

out vec4 color;

in vec4 FragPos;

// uniform vec3 camPos;
uniform samplerCube image_cube;

const float PI = 3.14159265359;

void main()
{
    vec3 N = normalize(vec3(FragPos));
    vec3 irradiance = vec3(0.0);

    vec3 up    = vec3(0.0, 1.0, 0.0);
    vec3 right = normalize(cross(up, N));
    up = normalize(cross(N, right));

    float sampleDelta = 0.05;
    float nrSamples = 0.0;

    for(float phi = 0; phi < 2.0 * PI; phi += sampleDelta)
    {
        for(float theta = 0.0; theta < 0.5 * PI; theta += sampleDelta)
        {
            vec3 tangentSample = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
            vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N;
            irradiance += texture(image_cube, sampleVec).rgb * cos(theta) * sin(theta);

            nrSamples ++;
        }
    }

    irradiance = PI * irradiance * (1.0 / float(nrSamples));

	color = vec4(irradiance, 1.0);
}
