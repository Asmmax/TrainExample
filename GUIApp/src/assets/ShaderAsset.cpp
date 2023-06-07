#include "assets/ShaderAsset.hpp"
#include "assets/AssetManager.hpp"
#include "resources/ShaderData.hpp"
#include "Loader.hpp"

ShaderAsset::ShaderAsset(const std::string& vertexShaderPath, const std::string& fragmentShaderPath):
	_shader(nullptr),
	_isLoaded(false)
{
	auto directory = AssetManager::getInstance().getPath();
	_vertexShader = loadShader(directory.find(vertexShaderPath));
	_fragmentShader = loadShader(directory.find(fragmentShaderPath));
}

void ShaderAsset::loadToGPU()
{
	Loader* loader = AssetManager::getInstance().getLoader();
	_shader = loader->loadShader(_vertexShader, _fragmentShader);
}

Shader* ShaderAsset::getShader()
{
	if (!_isLoaded) {
		loadToGPU();
		_isLoaded = true;
	}

	return _shader;
}
