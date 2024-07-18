#version 330

const float PI = 3.14159265;

in vec3 GlobalCoords;

out vec4 FragColor;

uniform sampler2D skyMap;


vec2 vec3ToUV( vec3 vector )
{
    float theta = acos(-vector.y);
    float phi = -atan(vector.z, vector.x);
    float u = ( phi) / (2. * PI);
    float v = theta / PI;
    return vec2(u,v);
}

void main(void)
{
	vec2 uv = vec3ToUV(normalize(GlobalCoords));
	FragColor = texture(skyMap, uv);
}
