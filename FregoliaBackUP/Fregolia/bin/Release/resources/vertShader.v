#version 330

in vec2 Coord2D;
uniform mat4 PMat;
uniform mat4 VMat;
uniform mat4 MMat;
in vec2 texCoords;

out vec2 fTexCoords;

void main(void)
{
	fTexCoords = texCoords;
	gl_Position = PMat * VMat * MMat * vec4(Coord2D, 1.0, 1);
}