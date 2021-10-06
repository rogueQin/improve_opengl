
#version 330 core

layout (lines) in;
layout (line_strip, max_vertices = 12) out;

// in VS_OUT{
// 	vec3 color;
// }gs_in[];

// out vec3 fColor;

void build_house(vec4 position, float scale)
{
	gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0) * scale;
	EmitVertex();
	gl_Position = position + vec4(0.2, -0.2, 0.0, 0.0) * scale;
	EmitVertex();
	gl_Position = position + vec4(0.2, 0.2, 0.0, 0.0) * scale;
	EmitVertex();
	gl_Position = position + vec4(0.0, 0.4, 0.0, 0.0) * scale;
	EmitVertex();
	gl_Position = position + vec4(-0.2, 0.2, 0.0, 0.0) * scale;
	EmitVertex();
	gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0) * scale;
	EmitVertex();

	EndPrimitive();
}

void main()
{
	build_house(gl_in[0].gl_Position, 1);
	build_house(gl_in[1].gl_Position, 1.2);
	// build_house(gl_in[2].gl_Position, 1.5);

}
