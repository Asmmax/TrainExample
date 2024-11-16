#version 330

#define PI 3.1415926

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
	float SpecularFactor;
	float SpecularPower;
};

in vec3 OutPosition;
in mat3 SurfaceMatrix;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 ViewOrigin;
uniform vec3 AmbientColor;
uniform MaterialInfo Material;
uniform DirectLightInfo DirectLights[4];
uniform PointLightInfo PointLights[10];
uniform int DirectLightCount = 0;
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

float IntensityFunc(float distance, float radius, float maxRadius)
{
	return clamp(1.0 - (distance - radius)/(maxRadius - radius + 0.000001), 0.0, 1.0);
}

vec3 ShadeBlinnPhong(vec3 toLight, vec3 normal, vec3 view, vec3 intensity, vec3 diffuseBase, float specFactor)
{
	vec3 light = normalize(SurfaceMatrix * normalize(toLight));
	float NdL = max(dot(normal, light), 0.0);
	float NdV = max(dot(normal, view), 0.0);
		
	vec3 diff = diffuseBase * NdL;
	float spec = 0.0;
	if (light.z > -0.2 && NdL > 0.0 && NdV > 0.0){
		vec3 h = normalize(light + view);
		float HdN = max(dot(h, normal), 0.0);	
		spec = pow(HdN, Material.SpecularPower);
	}
	
	return intensity * mix(diff, vec3(spec), specFactor);
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
	
#ifdef USE_SPEC_MAP
	float specFactor = Material.SpecularFactor * texture(SpecMap, TexCoords).x;
#else
	float specFactor = Material.SpecularFactor;
#endif
	
	vec3 view = normalize(SurfaceMatrix * normalize(ViewOrigin - OutPosition));
	
	vec3 sumLightIntensity = vec3(0.0f);
	for(int i = 0; i < DirectLightCount; i++){
		vec3 toLight = -DirectLights[i].Direction.xyz;
		float intensity = DirectLights[i].Intensity;
		sumLightIntensity += ShadeBlinnPhong(toLight, normal, view, DirectLights[i].Color * intensity, diffuseBase, specFactor);
	}
	for(int i = 0; i < PointLightCount; i++){
		vec3 toLight = vec3(PointLights[i].Position) - OutPosition;
		float intensity = PointLights[i].Intensity * IntensityFunc(length(toLight), PointLights[i].Radius, PointLights[i].Radius + PointLights[i].FadingArea);
		sumLightIntensity += ShadeBlinnPhong(toLight, normal, view, PointLights[i].Color * intensity, diffuseBase, specFactor);
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
