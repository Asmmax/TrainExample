#pragma once
#include "ASystem.hpp"
#include <memory>
#include <vector>

class PhysicalEntity;

class PhysicalSystem : public System
{
	using EntityPtr = std::shared_ptr<PhysicalEntity>;

private:
	float _fixed_time;
	float _time_redundant;
	std::vector<EntityPtr> _entities;

public:
	PhysicalSystem(float fixed_time);

	void init() override;
	void update(float delta_time) override;
	void draw() override;

	void addEntity(const EntityPtr& entity);

private:
	void fixedUpdate();
};
