#pragma once
#include "assets/GraphicalAsset.hpp"
#include <string>

class Shader;

/// @serializable @shared shaders
class ShaderAsset : public GraphicalAsset
{
private:
	Shader* _shader;
	std::string _vertexShader;
	std::string _fragmentShader;
	bool _isLoaded;

public:
	ShaderAsset(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	Shader* getShader();

	void loadToGPU() override;
};
