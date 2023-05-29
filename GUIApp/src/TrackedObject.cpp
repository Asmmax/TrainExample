#include "TrackedObject.hpp"
#include "ACurve.hpp"

#include <glm/glm.hpp>

TrackedObject::TrackedObject(const CurvePtr& path, float velocity):
	DynamicObject::DynamicObject(),
	_path(path),
	_velocity(velocity),
	_parameter(0.0f)
{

}

TrackedObject::TrackedObject(const std::shared_ptr<SharedMesh>& mesh, const CurvePtr& path, float velocity):
	DynamicObject::DynamicObject(mesh),
	_path(path),
	_velocity(velocity),
	_parameter(0.0f)
{
	setParameter(0.0f);
}

void TrackedObject::setParameter(float parameter)
{
	_parameter = parameter;

	// set initial position
	setPosition(_path->getValue(_parameter));

	// set initial rotation
	auto initial_tangent = glm::normalize(_path->getDerivative(_parameter));
	auto rotation = glm::quatLookAt(initial_tangent, glm::vec3(0.0f, 1.0f, 0.0f));
	setRotation(rotation);
}

void TrackedObject::fixedUpdate(float fixed_time)
{
	auto parameter_velocity = _velocity / glm::length(_path->getDerivative(_parameter));
	float step = fixed_time * parameter_velocity;
	_parameter += step;
	_parameter = std::fmodf(_parameter,1.0f);

	setNextPosition(_path->getValue(_parameter));

	auto current_tangent = glm::normalize(_path->getDerivative(_parameter));

	auto rotation = glm::quatLookAt(current_tangent, glm::vec3(0.0f, 1.0f, 0.0f));
	setNextRotation(rotation);
}
