#pragma once
#include "ASystem.hpp"
#include <memory>
#include <vector>

class PhysicalEntity;

/// @serializable
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
	void update(float delta_time) override;

	void addEntity(const EntityPtr& entity);

private:
	void fixedUpdate();
};
