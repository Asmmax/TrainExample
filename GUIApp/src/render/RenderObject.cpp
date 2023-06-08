#include "render/RenderObject.hpp"
#include "objects/Object.hpp"
#include "common/Transform.hpp"
#include "SharedMesh.hpp"
#include "assets/MaterialAsset.hpp"

RenderObject::RenderObject(const std::shared_ptr<Model>& model, const std::shared_ptr<SharedMesh>& mesh, const std::shared_ptr<MaterialAsset>& material, const std::shared_ptr<Transform>& transform):
	_model(model),
	_material(material),
	_mesh(mesh),
	_transform(transform),
	_object(nullptr)
{
	applyMaterial();
}

void RenderObject::update()
{
	if (!_object) {
		return;
	}

	if (!_transform) {
		return;
	}

	auto& matrix = _transform->getGlobalMatrix();
	_object->setMatrix(matrix);
}

void RenderObject::setMaterial(const std::shared_ptr<MaterialAsset>& material)
{
	if (_material) {
		_material->free(_object);
		_object = nullptr;
	}

	_material = material;
	applyMaterial();
}

void RenderObject::setMesh(const std::shared_ptr<SharedMesh>& mesh)
{
	_mesh = mesh;
	if (_mesh && _object) {
		_object->setMesh(_mesh->getMesh());
	}
}

void RenderObject::applyMaterial()
{
	if (!_material || _object || !_model) {
		return;
	}

	_object = _material->apply(_model);
	if (_mesh) {
		_object->setMesh(_mesh->getMesh());
	}
}
