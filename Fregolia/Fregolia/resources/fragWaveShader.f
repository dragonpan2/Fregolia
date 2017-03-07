#version 330

in vec2 fTexCoords;
uniform sampler2D Texture;
uniform float time;

void main(void)
{
	vec4 tempColor = vec4(texture(Texture, fTexCoords));
	//vec2 newTexCoords = vec2(fTexCoords.x + sin(fTexCoords.y * time) / 100, fTexCoords.y + sin(fTexCoords.x * time) / 100);
	vec2 pos = vec2(-1.0 + 2.0 * fTexCoords.x, -1.0 + 2.0 * fTexCoords.y);
	float range = length(pos);//sqrt(dot(pos, pos));
	float factor = sin(range*12 - time / 100)*0.05;

	vec2 newTexCoords = vec2(fTexCoords.x + factor*(pos.x/range), fTexCoords.y + factor*(pos.y/range));
	vec4 texColor = texture(Texture, newTexCoords);
	vec4 outColor = vec4(texColor + tempColor);
	//outColor = vec4(outColor.x * sin(fTexCoords.x), outColor.y * sin(fTexCoords.y), outColor.z, outColor.w);
	gl_FragColor = outColor;	
}