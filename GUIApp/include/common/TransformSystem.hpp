#pragma once
#include "ASystem.hpp"
#include <memory>
#include <vector>

class Transform;

class TransformSystem : public System
{
	using TransformPtr = std::shared_ptr<Transform>;

private:
	std::vector<TransformPtr> _transforms;

public:
	TransformSystem();

	void init() override;
	void update(float delta_time) override;
	void draw() override;

	void addTransform(const TransformPtr& tranform);
	void removeTransform(const TransformPtr& tranform);
};
