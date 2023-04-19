#include "DynamicObject.hpp"
#include "SharedMesh.hpp"
#include "framework/engine.h"

DynamicObject::DynamicObject() : GameObject::GameObject()
{
}

DynamicObject::DynamicObject(const SharedMeshPtr& mesh) : GameObject::GameObject(mesh)
{
}

void DynamicObject::interpolate(float value)
{
	_object->setPosition(glm::mix(_position, _next_position, value) + _offset);
	_object->setRotation(glm::slerp(_rotation, _next_rotation, value));
	_object->setScale(glm::mix(_scale, _next_scale, value));
}

void DynamicObject::init()
{
	_next_position = _position;
	_next_rotation = _rotation;
	_next_scale = _scale;
	if (_mesh) {
		_object->setMesh(_mesh->getMesh());
	}
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
