#include "DynamicObject.hpp"
#include "SharedMesh.hpp"
#include "Transform.hpp"

DynamicObject::DynamicObject() : GameObject::GameObject()
{
}

DynamicObject::DynamicObject(const std::shared_ptr<SharedMesh>& mesh) : GameObject::GameObject(mesh)
{
}

void DynamicObject::interpolate(float value)
{
	_transform->setPosition(glm::mix(_transform->getLocalPosition(), _next_position, value));
	_transform->setRotation(glm::slerp(_transform->getLocalRotation(), _next_rotation, value));
	_transform->setScale(glm::mix(_transform->getLocalScale(), _next_scale, value));
}

void DynamicObject::init(const std::shared_ptr<Model>& model)
{
	GameObject::init(model);

	_next_position = _transform->getLocalPosition();
	_next_rotation = _transform->getLocalRotation();
	_next_scale = _transform->getLocalScale();
}

void DynamicObject::update(float delta_time)
{
	GameObject::update(delta_time);
}

void DynamicObject::setNextPosition(const glm::vec3& position)
{
	setPosition(_next_position);
	_next_position = position;
}

void DynamicObject::setNextRotation(const glm::vec3& rotation)
{
	glm::vec3 euler = glm::radians(rotation);
	setRotation(_next_rotation);
	_next_rotation = glm::quat(euler);
}

void DynamicObject::setNextRotation(const glm::quat& rotation)
{
	setRotation(_next_rotation);
	_next_rotation = rotation;
}

void DynamicObject::setNextScale(const glm::vec3& scale)
{
	setScale(_next_scale);
	_next_scale = scale;
}
