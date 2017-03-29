#version 330

in vec3 Coord2D;
uniform mat4 PMat;
uniform mat4 VMat;
uniform mat4 MMat;

void main(void)
{
	gl_Position = PMat * VMat * MMat * vec4(Coord2D.xy, 1.0, 1);
}