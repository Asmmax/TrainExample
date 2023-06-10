#pragma once
#include "ASystem.hpp"
#include <memory>
#include <vector>

class Transform;

/// @serializable
class TransformSystem : public SystemCommon<TransformSystem>
{
	using TransformPtr = std::shared_ptr<Transform>;

private:
	std::vector<TransformPtr> _transforms;
	std::vector<TransformPtr> _pendingAdd;
	std::vector<TransformPtr> _pendingRemove;
	bool _isInited;

public:
	TransformSystem();

	void init() override;
	void update(float delta_time) override;

	void addTransform(const TransformPtr& tranform);
	void removeTransform(const TransformPtr& tranform);

private:
	void applyChanges();
};
