#pragma once
#include "resources/MeshData.hpp"

class Mesh;
class Loader;

/// @serializable @abstract @shared meshes
class MeshAsset
{
private:
	Mesh* _mesh;
	bool _isLoaded;

protected:
	MeshData _data;

public:
	MeshAsset();

	void loadToGPU();

	Mesh* getMesh();
};
