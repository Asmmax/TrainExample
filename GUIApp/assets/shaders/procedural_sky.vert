#version 330

layout (location = 0) in vec3 Position;

out vec3 EyeRay;
out vec3 Rayleigh;
out vec3 SunColor;
out vec3 Mie;
out vec3 Ground;

uniform mat4 ModelMatrix;
uniform mat4 MVP;

uniform vec3 SunDirection;

uniform float AtmosphereLength = 0.01;
uniform float AtmosphereWeight = 1.0;
uniform float FogWeight = 0.2;
uniform float CameraHeight = 0.0;
uniform float SunIntensity = 30.0;
uniform float MoonIntensity = 3.0;

uniform vec3 GroundColor;

const float PI = 3.14159265;
const float PI_2 = 3.14159265/2;
const float PI_4 = 3.14159265/4;
const float Hr = 0.15;
const float Kr = 8.8421135e-8 * 6.371e6;
const vec3 bettaR = 4.0 * 3.14159265 * Kr * 1.0 / pow(vec3(0.650, 0.570, 0.475), vec3(4.0));
const float Hm = 0.02;
const float bettaM = 21e-6 * 6.371e6;
const vec3 center = vec3(0.0, -1.0, 0.0);
const int sampleCount = 8;

vec2 intersectShadow(vec2 startRay, float posY, vec3 view, vec3 light)
{
	float VdL = dot(view, light);
	float posProj = posY*posY*(1.0 - light.y*light.y) - 1.0;
	bool startInShadow = light.y < 0.0 && posProj < 0.0;
	bool stopInShadow = VdL < 0.0 && posProj > 0.0;
	if (!startInShadow && !stopInShadow){
		return startRay;
	}
	
	float base = posY*(view.y - light.y*VdL);
	float discr = base*base - (1.0 - VdL*VdL)*posProj;
	if (discr < 0.0){
		return startRay;
	}
	
	if (startInShadow){
		vec2 result;
		result.x = (-base + sqrt(discr)) / (1.0 - VdL*VdL);
		result.y = startRay.y;
		return result;
	}
	
	if (stopInShadow){
		float length = (-base - sqrt(discr)) / (1.0 - VdL*VdL);
		vec3 point =  vec3(0.0, posY, 0.0) + view * length;
		if (length > 0.0 && dot(point, light) < 0.0){
			vec2 result;
			result.x = startRay.x;
			result.y = min(startRay.x + length, startRay.y);
			return result;
		}
	}
	return startRay;
}

float scale(float c, float H0)
{
	float x = -PI_4*abs(c);
	return x + sqrt(x*x + PI_2*H0);
}

float scale(float c, float H0, float dh)
{
	float lightDepth = scale(c, H0);
	return c > 0.0 ? lightDepth : 2*sqrt(PI_2*H0)*exp(-dh/H0) - lightDepth;
}

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
	float VdN = view.y; // -h/(cameraHeight + 1);
	vec3 r = centerToCameraPos + h * view;
	float r2 = dot(r, r);
	
	bool lookToGround = VdN < 0.0 && r2 <= 1.0;
	float inner = lookToGround ? h - sqrt(1.0 - r2) : 0.0;
	bool lookToAtm = cameraHeight >= AtmosphereLength && VdN < 0.0 && r2 <= outerRadius2 || cameraHeight < AtmosphereLength;
	float outer = lookToAtm ? h + sqrt(outerRadius2 - r2) : 0.0;
	
	float atmLength = lookToGround ? inner : outer;
	vec2 ray = intersectShadow(vec2(0.0, atmLength), 1.0 + cameraHeight, view, light);	
	float ds = (ray.y - ray.x) / sampleCount;
	
	vec3 sumR = vec3(0.0);
	vec3 sumM = vec3(0.0);
	
	float H0r = Hr * AtmosphereLength;
	float H0m = Hm * AtmosphereLength;
	
	float hmin = sqrt(r2) - 1;
	float dh = max(hmin, 0.0) - cameraHeight;
	float opticalDepthRFull = scale(VdN, H0r, dh)*exp(-cameraHeight/H0r);
	float opticalDepthMFull = scale(VdN, H0m, dh)*exp(-cameraHeight/H0m);
		
	if (ds > 0.0){
		for (int i = 0; i < sampleCount; i++){
			vec3 pos = cameraPos + view * ((i + 0.5) * ds + ray.x);
			vec3 centerToPos = pos - center;
			
			float height = length(centerToPos) - 1.0;
			float Hr_sample = exp( - height/H0r);
			float Hm_sample = exp( - height/H0m);
			
			float hr = dot(-centerToPos, light);
			float LdN = -hr/(height + 1);
			vec3 rr = centerToPos + hr * light;
			float rr2 = dot(rr, rr);
			
			float dhl = max(sqrt(rr2) - 1, 0.0) - height;
			float opticalDepthRL = scale(LdN, H0r, dhl)*Hr_sample;
			float opticalDepthML = scale(LdN, H0m, dhl)*Hm_sample;
			
			float VdNL = dot(centerToPos, view)/(height + 1);
			float dhr = max(hmin, 0.0) - height;
			float opticalDepthR = opticalDepthRFull - scale(VdNL, H0r, dhr)*Hr_sample;
			float opticalDepthM = opticalDepthMFull - scale(VdNL, H0m, dhr)*Hm_sample;
			
			vec3 tau = AtmosphereWeight * bettaR * (opticalDepthRL + opticalDepthR) + FogWeight * bettaM * (opticalDepthML + opticalDepthM);
			vec3 attn = vec3(exp(-tau[0]), exp(-tau[1]), exp(-tau[2]));
			sumR += Hr_sample * attn;
			sumM += Hm_sample * attn;
		}
		sumR *= ds;
		sumM *= ds;
	}
	
	vec3 tauSun = AtmosphereWeight * bettaR * opticalDepthRFull + FogWeight * bettaM * opticalDepthMFull;
	vec3 attnSun = vec3(exp(-tauSun[0]), exp(-tauSun[1]), exp(-tauSun[2]));
	SunColor = SunIntensity * attnSun;
	
	Rayleigh = SunIntensity * AtmosphereWeight * bettaR * sumR;
	Mie = SunIntensity * FogWeight * bettaM * sumM;
	
	Ground = vec3(0.0);
	if (lookToGround){
		vec3 centerToGroundPos = centerToCameraPos + view * inner;
		float VdG = dot(centerToGroundPos, -view); // centerToGroundPos has one length
		float opticalDepthR = max(scale(VdG, H0r) - scale(-VdN, H0r)*exp(-cameraHeight/H0r), 0.0);
		float opticalDepthM = max(scale(VdG, H0m) - scale(-VdN, H0m)*exp(-cameraHeight/H0m), 0.0);

		vec3 tau = AtmosphereWeight * bettaR * opticalDepthR + FogWeight * bettaM * opticalDepthM;
		vec3 attn = vec3(exp(-tau[0]), exp(-tau[1]), exp(-tau[2]));
		vec3 groundDiff = GroundColor * (light.y > 0.0 ? light.y : -light.y * MoonIntensity / SunIntensity);
		Ground = groundDiff * attn;
	}
}
