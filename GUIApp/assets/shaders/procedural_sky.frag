#version 330

in vec3 EyeRay;
in vec3 Rayleigh;
in float Mie;
in vec3 Ground;

out vec4 FragColor;

uniform vec3 SunDirection;

uniform float AtmosphereLength = 0.01;
uniform float CameraHeight = 0.0;
uniform float SunIntensity = 30.0;
uniform float SunSize = 0.02;
uniform float SunSmooth = 50.0;
uniform float MoonSize = 0.03;
uniform float MoonIntensity = 3.0;

const float PI = 3.14159265;
const float g = 0.76;
const vec3 center = vec3(0.0, -1.0, 0.0);

vec3 exposition(vec3 color, float factor)
{
	return 1.0 - vec3(exp(-factor * color.r), exp(-factor * color.g), exp(-factor * color.b));
}

void main(void)
{
	vec3 view = normalize(EyeRay);
	vec3 light = -normalize(SunDirection);
	
	float VdL = dot(view, light);
	
	float cameraHeight = mix(0.5e-6, AtmosphereLength, CameraHeight);
	vec3 cameraPos = vec3(0.0, cameraHeight, 0.0);
	
	vec3 centerToCameraPos = cameraPos - center;
	float h = dot(-centerToCameraPos, view);
	vec3 r = centerToCameraPos + h * view;
	float sqrR = dot(r, r);
	
	bool lookToGround = sqrR <= 1.0 && h >= 0.0;
	
	float minMoonCos = 2.0 / sqrt(4.0 + MoonSize * MoonSize);
	float moon = max(-VdL,0.0) > minMoonCos ? MoonIntensity : 0.0;
	float minSunCos = 2.0 / sqrt(4.0 + SunSize * SunSize);
	float sun = SunIntensity * max(1.0 - exp(-pow(max(VdL,0.0)/minSunCos, SunSmooth * 1e3)), 0.0);
	
	float pVdL = max(VdL, 0.0);
	float phaseR = mix(3.0/4.0 * (1 + pVdL * pVdL), 1.5, abs(light.y)) /(4.0 * PI); // fix dark sky overhead due to single scattering
	const float g2 = g * g;
	float phaseM = 3.0 /(8.0 * PI)*(1.0 - g2)/((2.0 + g2) * pow(1.0 + g2 - 2.0 * g * pVdL, 1.5)) * (1 + pVdL * pVdL);
	
	vec3 color = Rayleigh * phaseR + Mie * phaseM + Ground + (lookToGround ? 0.0 : (VdL > 0.0 ? sun : moon));
	vec3 finalColor = exposition(color, 2.0);
	FragColor = vec4(finalColor, 1.0);
}
