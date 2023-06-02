#pragma once
#include "physics/APhysicalEntity.hpp"

class ACurve;

class TrackedEntity : public PhysicalEntity
{
private:
	std::shared_ptr<ACurve> _path;
	float _velocity;
	float _parameter;

public:
	TrackedEntity(const std::shared_ptr<ACurve>& path, float velocity);

	virtual void fixedUpdate(float fixed_time) override;
	
	void setParameter(float parameter);
};

