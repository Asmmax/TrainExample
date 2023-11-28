#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;

out vec3 EyeCoords;
out vec3 EyeNormal;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

void main()
{
	EyeNormal = normalize(NormalMatrix * Normal);
	EyeCoords = (ModelViewMatrix * vec4(Position, 1.0f)).xyz;
	
    gl_Position = MVP * vec4(Position, 1.0f);
}
