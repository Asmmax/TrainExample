#include "components/RenderComponent.hpp"
#include "Material.hpp"
#include "SharedMesh.hpp"
#include "objects/Object.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "WorldContext.hpp"
#include "World.hpp"

RenderComponent::RenderComponent():
	_object(nullptr)
{
}

void RenderComponent::init()
{
	_model = WorldContext::getInstance().getWorld()->getModel();
	applyMaterial();
}

void RenderComponent::predraw()
{
	if (!_object) {
		return;
	}

	auto transform = getOwner()->getTransform();
	if (!transform) {
		return;
	}

	auto& matrix = transform->getGlobalMatrix();
	_object->setMatrix(matrix);
}

void RenderComponent::setMaterial(const std::shared_ptr<Material>& material)
{
	if (_material) {
		_material->free(_object);
		_object = nullptr;
	}

	_material = material;
	applyMaterial();
}

void RenderComponent::setMesh(const std::shared_ptr<SharedMesh>& mesh)
{
	_mesh = mesh;
	if (_mesh && _object) {
		_object->setMesh(_mesh->getMesh());
	}
}

void RenderComponent::applyMaterial()
{
	if (!_material || _object || !_model) {
		return;
	}

	_object = _material->apply(_model);
	if (_mesh) {
		_object->setMesh(_mesh->getMesh());
	}
}