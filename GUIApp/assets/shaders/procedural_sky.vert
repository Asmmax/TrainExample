#version 330

layout (location = 0) in vec3 Position;

out vec3 EyeRay;
out vec3 Rayleigh;
out float Mie;
out vec3 Ground;

uniform mat4 ModelMatrix;
uniform mat4 MVP;

uniform vec3 SunDirection;

uniform float AtmosphereLength = 0.01;
uniform float AtmosphereWeight = 1.0;
uniform float FogWeight = 0.1;
uniform float CameraHeight = 0.0;
uniform float SunIntensity = 30.0;
uniform float MoonIntensity = 3.0;

uniform vec3 GroundColor;

const float PI = 3.14159265;
const float Hr = 0.15;
const float Kr = 8.8421135e-8 * 6.371e6;
const vec3 bettaR = 4.0 * 3.14159265 * Kr * 1.0 / pow(vec3(0.650, 0.570, 0.475), vec3(4.0));
const float Hm = 0.02;
const float bettaM = 21e-6 * 6.371e6;
const vec3 center = vec3(0.0, -1.0, 0.0);

void main()
{
	gl_Position = MVP * vec4(Position, 1.0f);
	
	vec3 light = -normalize(SunDirection);
	vec3 view = normalize(vec3(ModelMatrix * vec4(Position, 1.0f)));
	EyeRay = view;
	
	float cameraHeight = mix(0.5e-6, AtmosphereLength, CameraHeight);
	vec3 cameraPos = vec3(0.0, cameraHeight, 0.0);
	float outerRadius = 1.0 + AtmosphereLength;
	float outerRadius2 = outerRadius * outerRadius;
	
	vec3 centerToCameraPos = cameraPos - center;
	float h = -view.y * (cameraHeight + 1.0); // dot(-centerToCameraPos, view);
	vec3 r = centerToCameraPos + h * view;
	float r2 = dot(r, r);
	
	bool lookToGround = view.y < 0.0 && r2 <= 1.0;
	float inner = lookToGround ? h - sqrt(1.0 - r2) : 0.0;
	bool lookToAtm = cameraHeight >= AtmosphereLength && view.y < 0.0 && r2 <= outerRadius2 || cameraHeight < AtmosphereLength;
	float outer = lookToAtm ? h + sqrt(outerRadius2 - r2) : 0.0;
	
	float atmLength = lookToGround ? inner : outer;
	
	int N = 16;
	int M = 8;
	float ds = atmLength / N;
	
	vec3 sumR = vec3(0.0);
	float sumM = 0.0;
	
	float opticalDepthR = 0.0;
	float opticalDepthM = 0.0;
	
	if (ds > 0.0){
		for (int i = 0; i < N; i++){
			vec3 pos = cameraPos + view * (i + 0.5) * ds;
			vec3 centerToPos = pos - center;
			
			float height = length(centerToPos) - 1.0;
			float Hr_sample = exp( - height/(Hr * AtmosphereLength)) * ds;
			float Hm_sample = exp( - height/(Hm * AtmosphereLength)) * ds;
			
			opticalDepthR += Hr_sample;
			opticalDepthM += Hm_sample;
			
			float hr = dot(-centerToPos, light);
			vec3 rr = centerToPos + hr * light;
			float rr2 = dot(rr, rr);
			bool lightThroughGround = hr > 0.0 && rr2 <= 1.0;
			if (lightThroughGround){
				continue;
			}
			
			float pathL = hr + sqrt(outerRadius2 - rr2);
			
			float opticalDepthRL = 0.0;
			float opticalDepthML = 0.0;
			float dl = pathL / M;
			int j = 0;
			for (j = 0; j < M; j++){
				vec3 posL = pos + light * (j + 0.5) * dl;
				float heightL = length(posL - center) - 1.0;
				opticalDepthRL += exp( - heightL /(Hr * AtmosphereLength)) * dl;
				opticalDepthML += exp( - heightL /(Hm * AtmosphereLength)) * dl;
			}
			
			vec3 tauR = AtmosphereWeight * bettaR * (opticalDepthRL + opticalDepthR);
			vec3 attnR = vec3(exp(-tauR[0]), exp(-tauR[1]), exp(-tauR[2]));
			float tauM = FogWeight * bettaM * (opticalDepthML + opticalDepthM);
			float attnM = exp(-tauM);
			sumR += Hr_sample * attnR;
			sumM += Hm_sample * attnM;
		}
	}
	
	Rayleigh = SunIntensity * AtmosphereWeight * bettaR * sumR;
	Mie = SunIntensity * FogWeight * bettaM * sumM;
	
	Ground = vec3(0.0);
	if (lookToGround){
		vec3 tauR = AtmosphereWeight * bettaR * opticalDepthR;
		vec3 attnR = vec3(exp(-tauR[0]), exp(-tauR[1]), exp(-tauR[2]));
		float tauM = FogWeight * bettaM * opticalDepthM;
		float attnM = exp(-tauM);
		vec3 groundDiff = GroundColor * (light.y > 0.0 ? light.y : -light.y * MoonIntensity / SunIntensity);
		Ground = groundDiff * (attnR + attnM);
	}
}
