#include "common/TransformSystem.hpp"
#include "common/Transform.hpp"

TransformSystem::TransformSystem()
{
}

void TransformSystem::init()
{
}

void TransformSystem::postUpdate(float delta_time)
{
	for (auto& transform : _roots) {
		transform->compute();
	}
}

void TransformSystem::addTransform(const TransformPtr& transform)
{
	if (transform->getParent()) {
		return;
	}
	_roots.push_back(transform);
}

void TransformSystem::removeTransform(const TransformPtr& transform)
{
	auto foundIt = std::find(_roots.begin(), _roots.end(), transform);
	if (foundIt != _roots.end()) {
		_roots.erase(foundIt);
	}
}
