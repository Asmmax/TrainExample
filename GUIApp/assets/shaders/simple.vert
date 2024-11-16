#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 inTexCoords;
layout (location = 2) in vec3 Normal;

out vec3 OutPosition;
out vec3 OutNormal;
out vec2 TexCoords;

uniform mat3 NormalMatrix;
uniform mat4 ModelMatrix;
uniform mat4 MVP;

void main()
{
	TexCoords = inTexCoords;
	OutNormal = normalize(NormalMatrix * Normal);
	OutPosition = (ModelMatrix * vec4(Position, 1.0f)).xyz;
	
    gl_Position = MVP * vec4(Position, 1.0f);
}
