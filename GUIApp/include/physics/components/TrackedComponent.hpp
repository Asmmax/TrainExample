#pragma once
#include "AComponent.hpp"
#include <memory>

class TrackedEntity;
class ACurve;

class TrackedComponent : public Component
{
private:
	std::shared_ptr<TrackedEntity> _entity;
	std::shared_ptr<ACurve> _path;
	float _velocity;
	float _parameter;

public:
	TrackedComponent();

	void init() override;

	void setPath(const std::shared_ptr<ACurve>& path);
	void setVelocity(float velocity);
	void setParameter(float param);
};