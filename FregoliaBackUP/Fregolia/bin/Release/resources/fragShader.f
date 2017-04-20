#version 330

in vec2 fTexCoords;
uniform sampler2D Texture;
uniform float time;

void main(void)
{
	vec4 outColor = vec4(1.0, 1.0, 1.0, 0.0);
	vec4 texColor = texture(Texture, fTexCoords);
	outColor = texColor;
	gl_FragColor = outColor;
}