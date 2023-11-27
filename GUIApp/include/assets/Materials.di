bind "ShaderAsset.hpp";
bind "MaterialAsset.hpp";

shared ShaderAsset
{
	ShaderAsset(std::string vertexShaderPath, std::string fragmentShaderPath);
} shaders;

shared MaterialAsset
{
	setShader(ShaderAsset shader);
	setColor(glm::vec3 color);
} materials;
