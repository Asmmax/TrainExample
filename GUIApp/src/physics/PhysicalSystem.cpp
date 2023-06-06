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

void PhysicalSystem::update(float delta_time)
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

void PhysicalSystem::draw()
{
}

void PhysicalSystem::addEntity(const EntityPtr& entity)
{
	_entities.push_back(entity);
}

void PhysicalSystem::fixedUpdate()
{
	for (auto& entity : _entities) {
		entity->fixedUpdate(_fixed_time);
	}
}
