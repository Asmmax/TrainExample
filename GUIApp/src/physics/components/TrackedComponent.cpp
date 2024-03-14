#include "physics/components/TrackedComponent.hpp"
#include "common/components/TransformComponent.hpp"
#include "World.hpp"
#include "GameObject.hpp"
#include "physics/PhysicalSystem.hpp"
#include "physics/TrackedEntity.hpp"
#include "common/Transform.hpp"
#include "ACurve.hpp"

TrackedComponent::TrackedComponent():
	_path(nullptr),
	_velocity(0.0f),
	_parameter(0.0f)
{
}

void TrackedComponent::init()
{
	auto transformComp = getOwner()->getComponent<TransformComponent>();
	auto transform = transformComp->getTransform();

	// set initial position
	transform->setPosition(_path->getValue(_parameter));

	// set initial rotation
	auto initial_tangent = glm::normalize(_path->getDerivative(_parameter));
	auto rotation = glm::quatLookAt(initial_tangent, glm::vec3(0.0f, 1.0f, 0.0f));
	transform->setRotation(rotation);

	auto world = getOwner()->getWorld();
	auto physicalSystem = world->getSystem<PhysicalSystem>();
	if (!physicalSystem) {
		return;
	}

	_entity = std::make_shared<TrackedEntity>(_path, _velocity);
	_entity->setTransform(transform);
	_entity->setParameter(_parameter);
	physicalSystem->addEntity(_entity);
}

void TrackedComponent::deinit()
{
	auto world = getOwner()->getWorld();
	auto physicalSystem = world->getSystem<PhysicalSystem>();
	if (!physicalSystem) {
		return;
	}
	physicalSystem->removeEntity(_entity);
}

void TrackedComponent::setPath(ACurve* path)
{
	_path = path;
}

void TrackedComponent::setVelocity(float velocity)
{
	_velocity = velocity;
}

void TrackedComponent::setParameter(float param)
{
	_parameter = param;
	if (_entity) {
		_entity->setParameter(_parameter);
	}
}
