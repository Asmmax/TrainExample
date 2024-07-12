#version 330

#define PI 3.1415926

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
};

in vec3 EyeCoords;
in mat3 SurfaceMatrix;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 AmbientColor;
uniform MaterialInfo Material;
uniform LightInfo PointLights[10];
uniform int PointLightCount = 0;

uniform sampler2D baseMap;
uniform sampler2D normalMap;
uniform sampler2D roughMap;
uniform sampler2D metalMap;
uniform sampler2D aoMap;

float IntensityFunc(float distance, float radius, float maxRadius)
{
	return clamp(1.0 - (distance - radius)/(maxRadius - radius + 0.000001), 0.0, 1.0);
}

void main()
{
	vec3 view = normalize(SurfaceMatrix * normalize(-EyeCoords));
	vec3 base = texture(baseMap, TexCoords).xyz;
	vec3 normal = 2.0 * texture(normalMap, TexCoords).xyz - 1.0;
	float rough = mix(0.01, 1.0, texture(roughMap, TexCoords).x);
	float metal = texture(metalMap, TexCoords).x;
	
	float alpha = rough * rough;
	float alpha2 = alpha * alpha;
	float power = 2.0 / alpha2 - 2.0;
	float f0 = mix(0.04, 1.0, metal);
	float specFactor = mix(0.1, 1.0, metal);
	
	float NdV = max(dot(normal, view), 0.001);
	
	vec3 sumLightIntensity = vec3(0.0f);
	for(int i = 0; i < PointLightCount; i++){
		vec3 toLight = vec3(PointLights[i].Position) - EyeCoords;
		float intensity = PointLights[i].Intensity * IntensityFunc(length(toLight), PointLights[i].Radius, PointLights[i].Radius + PointLights[i].FadingArea);
		
		vec3 light = normalize(SurfaceMatrix * normalize(toLight));
		vec3 h = normalize(light + view);
		
		float NdL = max(dot(normal, light), 0.001);
		float HdN = max(dot(h, normal), 0.0);
		float VdH = max(dot(view, h), 0.001);
		
		float D = (power + 2.0) / (2.0 * PI) * pow(HdN, power);
		float G = min(1.0, min(2 * HdN * NdV / VdH, 2 * HdN * NdL / VdH));
		float F = f0 + (1 - f0) * pow(1.0 - VdH, 5.0);
		
		float spec = D * G * F / (4 * NdL * NdV);		
		
		sumLightIntensity += PointLights[i].Color * intensity * NdL * mix(base, vec3(spec), specFactor);
	}
	
	vec3 ambientPart = AmbientColor * Material.AmbientFactor * base;
	vec3 diffusePart = sumLightIntensity * Material.DiffuseColor;
	
	float aoScale = texture(aoMap, TexCoords).x;
	FragColor = vec4((ambientPart + diffusePart) * aoScale, 1.0);
}
