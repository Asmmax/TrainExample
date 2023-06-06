#include "physics/APhysicalEntity.hpp"
#include "common/Transform.hpp"

void PhysicalEntity::setTransform(const std::shared_ptr<Transform>& transform)
{
	_transform = transform;
	resetPosition(_transform->getLocalPosition());
	resetRotation(_transform->getLocalRotation());
	resetScale(_transform->getLocalScale());
}

void PhysicalEntity::setNextPosition(const glm::vec3& position)
{
	_prev_position = _next_position;
	_next_position = position;
}

void PhysicalEntity::setNextRotation(const glm::vec3& rotation)
{
	glm::vec3 euler = glm::radians(rotation);
	setNextRotation(glm::quat(euler));
}

void PhysicalEntity::setNextRotation(const glm::quat& rotation)
{
	_prev_rotation = _next_rotation;
	_next_rotation = rotation;
}

void PhysicalEntity::setNextScale(const glm::vec3& scale)
{
	_prev_scale = _next_scale;
	_next_scale = scale;
}

void PhysicalEntity::resetPosition(const glm::vec3& position)
{
	_prev_position = position;
	_next_position = _prev_position;
}

void PhysicalEntity::resetRotation(const glm::vec3& rotation)
{
	glm::vec3 euler = glm::radians(rotation);
	resetRotation(glm::quat(euler));
}

void PhysicalEntity::resetRotation(const glm::quat& rotation)
{
	_prev_rotation = rotation;
	_next_rotation = _prev_rotation;
}

void PhysicalEntity::resetScale(const glm::vec3& scale)
{
	_prev_scale = scale;
	_next_scale = _prev_scale;
}

void PhysicalEntity::interpolate(float value)
{
	_transform->setPosition(glm::mix(_prev_position, _next_position, value));
	_transform->setRotation(glm::slerp(_prev_rotation, _next_rotation, value));
	_transform->setScale(glm::mix(_prev_scale, _next_scale, value));
}
