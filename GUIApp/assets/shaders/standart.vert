#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 Tangent;
layout (location = 3) in vec2 inTexCoords;

out vec3 EyeCoords;
out mat3 SurfaceMatrix;
out vec2 TexCoords;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

void main()
{
	TexCoords = inTexCoords;
	
	vec3 norm = normalize(NormalMatrix * Normal);
	vec3 tang = normalize(NormalMatrix * Tangent);
	vec3 binormal = normalize(cross(norm, tang));
	SurfaceMatrix = mat3(
		tang.x, binormal.x, norm.x,
		tang.y, binormal.y, norm.y,
		tang.z, binormal.z, norm.z);
	
	EyeCoords = (ModelViewMatrix * vec4(Position, 1.0f)).xyz;
	
    gl_Position = MVP * vec4(Position, 1.0f);
}
