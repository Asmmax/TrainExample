#include "common/TransformSystem.hpp"
#include "common/Transform.hpp"

TransformSystem::TransformSystem()
{
}

void TransformSystem::init()
{
}

void TransformSystem::update(float delta_time)
{
	for (auto& transform : _transforms) {
		transform->compute();
	}
}

void TransformSystem::addTransform(const TransformPtr& tranform)
{
	_transforms.push_back(tranform);
}

void TransformSystem::removeTransform(const TransformPtr& tranform)
{
	auto foundIt = std::find(_transforms.begin(), _transforms.end(), tranform);
	if (foundIt != _transforms.end()) {
		_transforms.erase(foundIt);
	}
}
