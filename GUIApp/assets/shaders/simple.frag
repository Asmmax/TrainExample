#version 330

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
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 AmbientColor;
uniform MaterialInfo Material;
uniform LightInfo PointLights[10];
uniform int PointLightCount = 0;

#ifdef USE_BASE_MAP
uniform sampler2D BaseMap;
#endif

float IntensityFunc(float distance, float radius, float maxRadius)
{
	return clamp(1.0 - (distance - radius)/(maxRadius - radius + 0.000001), 0.0, 1.0);
}

void main()
{
#ifdef USE_BASE_MAP
	vec3 base = texture(BaseMap, TexCoords).xyz;
	vec3 ambientBase = base * AmbientColor * Material.AmbientFactor;
	vec3 diffuseBase = base * Material.DiffuseColor * Material.DiffuseFactor;
#else
	vec3 ambientBase = AmbientColor * Material.AmbientFactor;
	vec3 diffuseBase = Material.DiffuseColor * Material.DiffuseFactor;
#endif

	vec3 sumLightIntensity = vec3(0.0f);
	for(int i = 0; i < PointLightCount; i++){
		vec3 toLight = vec3(PointLights[i].Position) - EyeCoords;
		vec3 light = normalize(toLight);
		float NdL = max(dot(EyeNormal, light), 0.0);
		
		float intensity = PointLights[i].Intensity * IntensityFunc(length(toLight), PointLights[i].Radius, PointLights[i].Radius + PointLights[i].FadingArea);
		sumLightIntensity += PointLights[i].Color * intensity * NdL;
	}
	
    FragColor = vec4(ambientBase + sumLightIntensity * diffuseBase, 1.0);
}
