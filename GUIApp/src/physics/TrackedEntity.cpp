#include "physics/TrackedEntity.hpp"
#include "ACurve.hpp"
#include "common/Transform.hpp"
#include <cmath>
#include <glm/glm.hpp>

TrackedEntity::TrackedEntity(const std::shared_ptr<ACurve>& path, float velocity):
	_path(path),
	_velocity(velocity),
	_parameter(0.0f)
{
}

void TrackedEntity::fixedUpdate(float fixed_time)
{
	auto parameter_velocity = _velocity / glm::length(_path->getDerivative(_parameter));
	float step = fixed_time * parameter_velocity;
	_parameter += step;
	float intPart;
	_parameter = std::modf(_parameter, &intPart);

	setNextPosition(_path->getValue(_parameter));

	auto current_tangent = glm::normalize(_path->getDerivative(_parameter));

	auto rotation = glm::quatLookAt(current_tangent, glm::vec3(0.0f, 1.0f, 0.0f));
	setNextRotation(rotation);
}

void TrackedEntity::setParameter(float parameter)
{
	_parameter = parameter;
}
