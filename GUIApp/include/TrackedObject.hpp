#pragma once
#include "DynamicObject.hpp"

class ACurve;

class TrackedObject : public DynamicObject
{
	using CurvePtr = std::shared_ptr<ACurve>;
public:
	TrackedObject(const CurvePtr& path, float velocity);
	TrackedObject(const std::shared_ptr<SharedMesh>& mesh, const CurvePtr& path, float velocity);
	
	void setParameter(float parameter);

	virtual void fixedUpdate(float fixed_time) override;

private:
	float _parameter;
	float _velocity;
	CurvePtr _path;
};

