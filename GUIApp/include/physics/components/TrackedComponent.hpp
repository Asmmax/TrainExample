#pragma once
#include "AComponent.hpp"
#include <memory>

class TrackedEntity;
class ACurve;

/// @serializable
class TrackedComponent : public ComponentCommon<TrackedComponent>
{
private:
	std::shared_ptr<TrackedEntity> _entity;
	std::shared_ptr<ACurve> _path;
	float _velocity;
	float _parameter;

public:
	TrackedComponent();

	void init() override;

	/// @inject
	void setPath(const std::shared_ptr<ACurve>& path);
	/// @inject
	void setVelocity(float velocity);
	/// @inject
	void setParameter(float param);
};