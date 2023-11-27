#pragma once
#include "SystemCommon.hpp"
#include <memory>
#include <vector>

class PhysicalEntity;

class PhysicalSystem : public SystemCommon<PhysicalSystem>
{
	using EntityPtr = std::shared_ptr<PhysicalEntity>;

private:
	float _fixed_time;
	float _time_redundant;
	std::vector<EntityPtr> _entities;

public:
	PhysicalSystem(float fixedTime);

	void init() override;
	void postUpdate(float delta_time) override;

	void addEntity(const EntityPtr& entity);
	void removeEntity(const EntityPtr& entity);

private:
	void fixedUpdate();
};
