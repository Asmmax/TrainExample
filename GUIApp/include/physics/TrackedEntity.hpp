#pragma once
#include "physics/APhysicalEntity.hpp"

class ACurve;

class TrackedEntity : public PhysicalEntity
{
private:
	ACurve* _path;
	float _velocity;
	float _parameter;

public:
	TrackedEntity(ACurve* path, float velocity);

	virtual void fixedUpdate(float fixed_time) override;
	
	void setParameter(float parameter);
};

