#version 330

struct DirectLightInfo 
{
	vec3 Direction;
	vec3 Color;
	float Intensity;
};

struct PointLightInfo 
{
	vec3 Position;
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

in vec3 OutPosition;
in vec3 OutNormal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 AmbientColor;
uniform MaterialInfo Material;
uniform DirectLightInfo DirectLights[4];
uniform PointLightInfo PointLights[10];
uniform int DirectLightCount = 0;
uniform int PointLightCount = 0;

#ifdef USE_BASE_MAP
uniform sampler2D BaseMap;
#endif

float IntensityFunc(float distance, float radius, float maxRadius)
{
	return clamp(1.0 - (distance - radius)/(maxRadius - radius + 0.000001), 0.0, 1.0);
}

vec3 ShadeSimple(vec3 toLight, vec3 inNormal, vec3 intensity)
{
	vec3 light = normalize(toLight);
	vec3 normal = normalize(inNormal);
	float NdL = max(dot(normal, light), 0.0);
	return intensity * NdL;
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
	for(int i = 0; i < DirectLightCount; i++){
		vec3 toLight = -DirectLights[i].Direction.xyz;		
		float intensity = DirectLights[i].Intensity;
		sumLightIntensity += ShadeSimple(toLight, OutNormal, DirectLights[i].Color * intensity);
	}
	for(int i = 0; i < PointLightCount; i++){
		vec3 toLight = PointLights[i].Position.xyz - OutPosition;		
		float intensity = PointLights[i].Intensity * IntensityFunc(length(toLight), PointLights[i].Radius, PointLights[i].Radius + PointLights[i].FadingArea);
		sumLightIntensity += ShadeSimple(toLight, OutNormal, PointLights[i].Color * intensity);
	}
	
    FragColor = vec4(ambientBase + sumLightIntensity * diffuseBase, 1.0);
}
