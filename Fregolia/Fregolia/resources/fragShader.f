#version 330

in vec2 fTexCoords;
uniform sampler2D Texture;

void main(void)
{
	vec3 texColor = texture(Texture, fTexCoords).xyz;
	gl_FragColor = vec4(texColor, 1.0);
}