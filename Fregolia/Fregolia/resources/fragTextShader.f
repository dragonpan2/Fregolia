#version 330

in vec2 fTexCoords;
uniform sampler2D Texture;
uniform vec4 Color;
uniform float time;

void main(void)
{
	vec4 outColor = vec4(Color.xyz, texture(Texture, fTexCoords).a * Color.w);
	//vec4 texColor = texture(Texture, fTexCoords);
	//outColor = texColor;
	gl_FragColor = outColor;
}