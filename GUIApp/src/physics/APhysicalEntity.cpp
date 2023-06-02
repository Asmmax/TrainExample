#include "physics/APhysicalEntity.hpp"
#include "Transform.hpp"

void PhysicalEntity::setTransform(const std::shared_ptr<Transform>& transform)
{
	_transform = transform;
	_prev_position = _transform->getLocalPosition();
	_next_position = _prev_position;
	_prev_rotation = _transform->getLocalRotation();
	_next_rotation = _prev_rotation;
	_prev_scale = _transform->getLocalScale();
	_next_scale = _prev_scale;
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

void PhysicalEntity::interpolate(float value)
{
	_transform->setPosition(glm::mix(_prev_position, _next_position, value));
	_transform->setRotation(glm::slerp(_prev_rotation, _next_rotation, value));
	_transform->setScale(glm::mix(_prev_scale, _next_scale, value));
}
