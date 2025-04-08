# version 450 core

layout(location = 0) in vec3 in_Vertex;
layout(location = 1) in vec2 in_TexCoord;
layout(location = 2) in vec3 in_Normal;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(in_Vertex, 1.0);
	v_TexCoord = in_TexCoord;
}