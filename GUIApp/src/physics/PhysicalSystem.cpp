#include "physics/PhysicalSystem.hpp"
#include "physics/APhysicalEntity.hpp"

PhysicalSystem::PhysicalSystem(float fixed_time):
	_fixed_time(fixed_time),
	_time_redundant(0.0f)
{
}

void PhysicalSystem::init()
{
}

void PhysicalSystem::postUpdate(float delta_time)
{
	_time_redundant += delta_time;
	while (_time_redundant >= _fixed_time) {
		_time_redundant -= _fixed_time;
		fixedUpdate();
	}

	for (auto& entity : _entities) {
		entity->interpolate(_time_redundant / _fixed_time);
	}
}

void PhysicalSystem::addEntity(const EntityPtr& entity)
{
	_entities.push_back(entity);
}

void PhysicalSystem::removeEntity(const EntityPtr& entity)
{
	auto lastIt = std::remove(_entities.begin(), _entities.end(), entity);
	_entities.erase(lastIt, _entities.end());
}

void PhysicalSystem::fixedUpdate()
{
	for (auto& entity : _entities) {
		entity->fixedUpdate(_fixed_time);
	}
}
