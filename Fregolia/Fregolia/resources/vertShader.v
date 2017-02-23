#version 330

in vec2 Coord2D;
in mat2 TMat;
in vec2 texCoords;

out vec2 fTexCoords;

void main(void)
{
	fTexCoords = texCoords;
	gl_Position = TMat * vec4(Coord2D, 0, 1);
}