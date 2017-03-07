#version 330

in vec2 fTexCoords;
uniform sampler2D Texture;
uniform float time;

void main(void)
{
	vec4 texColor = texture(Texture, fTexCoords);
	vec4 outColor = texColor;
	gl_FragColor = outColor;	
}