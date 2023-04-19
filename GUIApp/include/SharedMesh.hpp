#pragma once
#include "framework/mesh.h"

// Оболочка для меша. Движковый меш нельзя копировать и нельзя использовать внешние функции-хелперы в парадигме ООП. 
// Таким образом нам нужен общий меш.
class SharedMesh
{
public:
	SharedMesh() = default;
	SharedMesh(const SharedMesh& other) = delete;

	Mesh* getMesh() { return &_mesh; }

private:
	Mesh _mesh;
};
