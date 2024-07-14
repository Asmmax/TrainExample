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
	float SpecularFactor;
};

in vec3 EyeCoords;
in mat3 SurfaceMatrix;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 AmbientColor;
uniform MaterialInfo Material;
uniform LightInfo PointLights[10];
uniform int PointLightCount = 0;

#ifdef USE_BASE_MAP
uniform sampler2D BaseMap;
#endif

#ifdef USE_NORMAL_MAP
uniform sampler2D NormalMap;
#endif

#ifdef USE_SPEC_MAP
uniform sampler2D SpecMap;
#endif

#ifdef USE_AO_MAP
uniform sampler2D AoMap;
#endif

#ifdef USE_ROUGH_MAP
uniform sampler2D RoughMap;
#else
uniform float Roughness = 0.0;
#endif

#ifdef USE_METAL_MAP
uniform sampler2D MetalMap;
#else
uniform float Metalness = 0.0;
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
	vec3 diffuseBase = base * Material.DiffuseColor;
#else
	vec3 ambientBase = AmbientColor * Material.AmbientFactor;
	vec3 diffuseBase = Material.DiffuseColor;
#endif

#ifdef USE_NORMAL_MAP
	vec3 normal = 2.0 * texture(NormalMap, TexCoords).xyz - 1.0;
#else
	const vec3 normal = vec3(0.0, 0.0, 1.0);
#endif

#ifdef USE_ROUGH_MAP
	float rough = mix(0.01, 1.0, texture(RoughMap, TexCoords).x);
#else
	float rough = Roughness;
#endif

#ifdef USE_METAL_MAP
	float metal = texture(MetalMap, TexCoords).x;
#else
	float metal = Metalness;
#endif

#ifdef USE_SPEC_MAP
	float specFactor = Material.SpecularFactor * texture(SpecMap, TexCoords).x;
#else
	float specFactor = mix(Material.SpecularFactor, 1.0, metal);
#endif

	float alpha = rough * rough;
	float alpha2 = alpha * alpha;
	float power = 2.0 / alpha2 - 2.0;
	float f0 = mix(0.04, 1.0, metal);
	
	vec3 view = normalize(SurfaceMatrix * normalize(-EyeCoords));
	float NdV = max(dot(normal, view), 0.001);
	
	vec3 sumLightIntensity = vec3(0.0f);
	for(int i = 0; i < PointLightCount; i++){
		vec3 toLight = vec3(PointLights[i].Position) - EyeCoords;
		float intensity = PointLights[i].Intensity * IntensityFunc(length(toLight), PointLights[i].Radius, PointLights[i].Radius + PointLights[i].FadingArea);
		
		vec3 light = normalize(SurfaceMatrix * normalize(toLight));
		float NdL = max(dot(normal, light), 0.0);
		
		float spec = 0.0;
		if (light.z > 0 && NdL > 0){
			vec3 h = normalize(light + view);
			float HdN = max(dot(h, normal), 0.0);
			float NdL = max(dot(normal, light), 0.001);
			float VdH = max(dot(view, h), 0.001);
			
			float D = (power + 2.0) / (2.0 * PI) * pow(HdN, power);
			float G = min(1.0, min(2.0 * HdN * NdV / VdH, 2.0 * HdN * NdL / VdH));
			float F = f0 + (1 - f0) * pow(1.0 - VdH, 5.0);
			
			spec = D * G * F / (4 * NdL * NdV);
		}
		
		sumLightIntensity += PointLights[i].Color * intensity * NdL * mix(diffuseBase, vec3(spec), specFactor);
	}
	
	vec3 ambientPart = ambientBase * Material.AmbientFactor;
	
#ifdef USE_AO_MAP
	float aoScale = texture(AoMap, TexCoords).x;
#else
	const float aoScale = 1.0;
#endif
	
	vec3 diffusePart = sumLightIntensity * aoScale;
	
	FragColor = vec4(ambientPart + diffusePart, 1.0);
}
