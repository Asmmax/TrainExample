#pragma once
#include "DynamicObject.h"

class ACurve;

class TrackedObject : public DynamicObject
{
	using CurvePtr = std::shared_ptr<ACurve>;
public:
	TrackedObject(const SharedMeshPtr& mesh, const CurvePtr& path, float velocity);
	
	void setParameter(float parameter);

	virtual void fixedUpdate(float fixed_time) override;

private:
	float _parameter;
	float _velocity;
	CurvePtr _path;
};

