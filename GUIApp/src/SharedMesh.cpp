#include "SharedMesh.hpp"
#include "Loader.hpp"

void SharedMesh::load(Loader& loader)
{
	_mesh = loader.loadMesh(_data);
}
