#pragma once
#include "ComponentCommon.hpp"
#include <memory>

class TrackedEntity;
class ACurve;

class TrackedComponent : public ComponentCommon<TrackedComponent>
{
private:
	std::shared_ptr<TrackedEntity> _entity;
	ACurve* _path;
	float _velocity;
	float _parameter;

public:
	TrackedComponent();

	void init() override;
	void deinit() override;

	void setPath(ACurve* path);
	void setVelocity(float velocity);
	void setParameter(float param);
};