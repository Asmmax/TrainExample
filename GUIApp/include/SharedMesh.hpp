#pragma once
#include "resources/MeshData.hpp"

class Mesh;
class Loader;

class SharedMesh
{
public:
	SharedMesh() = default;
	SharedMesh(const SharedMesh& other) = delete;

	void load(Loader& loader);

	Mesh* getMesh() { return _mesh; }

private:
	Mesh* _mesh = nullptr;
protected:
	MeshData _data;
};
