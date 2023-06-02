#include "components/TrackedComponent.hpp"
#include "WorldContext.hpp"
#include "World.hpp"
#include "GameObject.hpp"
#include "physics/PhysicalSystem.hpp"
#include "physics/TrackedEntity.hpp"

TrackedComponent::TrackedComponent():
	_velocity(0.0f)
{
}

void TrackedComponent::init()
{
	auto world = WorldContext::getInstance().getWorld();
	auto physicalSystem = world->getSystem<PhysicalSystem>();

	_entity = std::make_shared<TrackedEntity>(_path, _velocity);
	auto transform = getOwner()->getTransform();
	_entity->setTransform(transform);
	_entity->setParameter(_parameter);
	physicalSystem->addEntity(_entity);
}

void TrackedComponent::setPath(const std::shared_ptr<ACurve>& path)
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
