#version 330

layout (location = 0) in vec3 Position;

out vec3 GlobalCoords;

uniform mat4 ModelMatrix;
uniform mat4 MVP;

void main()
{
	GlobalCoords = vec3(ModelMatrix * vec4(Position, 1.0f));
	
    gl_Position = MVP * vec4(Position, 1.0f);
}
