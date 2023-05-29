#include "GameObject.hpp"
#include "SharedMesh.hpp"
#include "Model.hpp"
#include "objects/Batch.hpp"
#include "objects/Object.hpp"
#include "Transform.hpp"
#include "Material.hpp"

GameObject::GameObject():
	_transform(std::make_shared<Transform>()),
	_object(nullptr),
	_batch(nullptr)
{
}

GameObject::GameObject(const std::shared_ptr<SharedMesh>& mesh):
	_transform(std::make_shared<Transform>()),
	_mesh(mesh),
	_object(nullptr),
	_batch(nullptr)
{
	assert(_mesh);
}

void GameObject::init(const std::shared_ptr<Model>& model)
{
	_model = model;
	_batch = _model->createBatch();
	_object = _batch->createObject();
	if (_mesh) {
		_object->setMesh(_mesh->getMesh());
	}
	if (_material) {
		_batch->setShader(_material->getShader());
	}
}

void GameObject::update(float delta_time)
{
	auto& matrix = _transform->getGlobalMatrix();
	_object->setMatrix(matrix);

	if (_material) {
		auto& state = _batch->getState();
		state.clear();
		_material->apply(state);
	}
}

void GameObject::setMaterial(const std::shared_ptr<Material>& material)
{
	_material = material;
	if (_material && _batch) {
		_batch->setShader(_material->getShader());
	}
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
