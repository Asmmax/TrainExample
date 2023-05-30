#include "GameObject.hpp"
#include "SharedMesh.hpp"
#include "objects/Object.hpp"
#include "Transform.hpp"
#include "Material.hpp"

GameObject::GameObject():
	_transform(std::make_shared<Transform>()),
	_object(nullptr)
{
}

GameObject::GameObject(const std::shared_ptr<SharedMesh>& mesh):
	_transform(std::make_shared<Transform>()),
	_mesh(mesh),
	_object(nullptr)
{
	assert(_mesh);
}

void GameObject::init(const std::shared_ptr<Model>& model)
{
	_model = model;
	applyMaterial();
}

void GameObject::update(float delta_time)
{
	if (!_object) {
		return;
	}

	auto& matrix = _transform->getGlobalMatrix();
	_object->setMatrix(matrix);
}

void GameObject::setMaterial(const std::shared_ptr<Material>& material)
{
	if (_material) {
		_material->free(_object);
		_object = nullptr;
	}

	_material = material;
	applyMaterial();
}

void GameObject::setPosition(const glm::vec3& position)
{
	_transform->setPosition(position);
}

void GameObject::setRotation(const glm::vec3& rotation)
{
	auto radianEulers = glm::radians(rotation);
	_transform->setRotation(radianEulers);
}

void GameObject::setRotation(const glm::quat& rotation)
{
	_transform->setRotation(rotation);
}

void GameObject::setScale(const glm::vec3& scale)
{
	_transform->setScale(scale);
}

void GameObject::setMesh(const std::shared_ptr<SharedMesh>& mesh)
{
	_mesh = mesh;
	if (_mesh && _object) {
		_object->setMesh(_mesh->getMesh());
	}
}

void GameObject::attachChild(const std::shared_ptr<GameObject>& child)
{
	_transform->addChild(child->getTransform());
}

void GameObject::applyMaterial()
{
	if (!_material || _object || !_model) {
		return;
	}

	_object = _material->apply(_model);
	if (_mesh) {
		_object->setMesh(_mesh->getMesh());
	}
}
