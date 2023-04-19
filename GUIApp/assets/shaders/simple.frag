#version 430

struct LightInfo 
{
	vec4 Position;
	vec3 Color;
	float Intensity;
	float Radius;
	float FadingArea;
};

struct MaterialInfo 
{
	vec3 DiffuseColor;
	float AmbientFactor;
	float DiffuseFactor;
};

in vec3 EyeCoords;
in vec3 EyeNormal;

out vec4 FragColor;

uniform vec3 AmbientColor;
uniform MaterialInfo Material;
uniform LightInfo PointLights[10];
uniform int PointLightCount = 0;

float IntensityFunc(float distance, float radius, float maxRadius)
{
	return clamp(1.0 - (distance - radius)/(maxRadius - radius + 0.000001), 0.0, 1.0);
}

void main()
{
	vec3 sumLightIntensity = vec3(0.0f);
	for(int i = 0; i < PointLightCount; i++){
		vec3 toLight = vec3(PointLights[i].Position) - EyeCoords;
		vec3 toLight_n = normalize(toLight);
		float intensity = PointLights[i].Intensity * IntensityFunc(length(toLight), PointLights[i].Radius, PointLights[i].Radius + PointLights[i].FadingArea);
		sumLightIntensity += max(dot(toLight_n, EyeNormal), 0.0) * PointLights[i].Color * intensity;
	}
	
	vec3 ambientPart = AmbientColor * Material.AmbientFactor;
	vec3 diffusePart = sumLightIntensity * Material.DiffuseColor * Material.DiffuseFactor;
	
    FragColor = vec4(diffusePart + ambientPart, 1.0);
}
