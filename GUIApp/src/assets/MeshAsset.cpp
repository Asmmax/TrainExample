#include "assets/MeshAsset.hpp"
#include "assets/AssetManager.hpp"
#include "Loader.hpp"

MeshAsset::MeshAsset():
	_mesh(nullptr),
	_isLoaded(false)
{
}

void MeshAsset::loadToGPU()
{
	Loader* loader = AssetManager::getInstance().getLoader();
	_mesh = loader->loadMesh(_data);
}

Mesh* MeshAsset::getMesh()
{
	if (!_isLoaded) {
		loadToGPU();
		_isLoaded = true;
	}
	return _mesh;
}
