
#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

in VS_OUT{
	vec3 normal;
}gs_in[];

vec3 GetNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

void line(int index, vec3 normal)
{
	gl_Position = gl_in[index].gl_Position;
	EmitVertex();

	gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * 0.4;
	EmitVertex();
	EndPrimitive();
}

void main()
{
	vec3 normal = GetNormal();

	line(0, normal);
	// line(1, normal);
	// line(2, normal);
}
