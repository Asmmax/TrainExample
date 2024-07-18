#version 330

const float PI = 3.14159265;

in vec3 GlobalCoords;

out vec4 FragColor;

uniform sampler2D skyMap;
uniform vec3 skyColor;
uniform vec3 farColor;
uniform vec3 groundColor;
uniform float borderFactor;

void main(void)
{
	float vertical = normalize(GlobalCoords).y;
	float skyScalar = max(vertical, 0.0);
	float groundScalar = max(-vertical, 0.0);
	float sky = vertical < 0.0 ? 0.0 : 1.0;
	
	vec3 color = mix(mix(groundColor, farColor, pow(1.0 - groundScalar, 100.0)), mix(skyColor, farColor, pow(1.0 - skyScalar, borderFactor)), sky);
	FragColor = vec4(color, 1.0);
}
