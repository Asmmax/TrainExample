#pragma once
#include "SystemCommon.hpp"
#include <memory>
#include <vector>

class Transform;

class TransformSystem : public SystemCommon<TransformSystem>
{
	using TransformPtr = std::shared_ptr<Transform>;

private:
	std::vector<TransformPtr> _roots;

public:
	TransformSystem();

	void init() override;
	void postUpdate(float delta_time) override;

	void addTransform(const TransformPtr& tranform);
	void removeTransform(const TransformPtr& tranform);

private:
	void applyChanges();
};
