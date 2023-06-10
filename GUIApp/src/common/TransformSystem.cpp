#include "common/TransformSystem.hpp"
#include "common/Transform.hpp"

TransformSystem::TransformSystem():
	_isInited(false)
{
}

void TransformSystem::init()
{
	applyChanges();
	_isInited = true;
}

void TransformSystem::update(float delta_time)
{
	for (auto& transform : _transforms) {
		transform->compute();
	}
}

void TransformSystem::addTransform(const TransformPtr& transform)
{
	_pendingAdd.push_back(transform);
	if (_isInited) {
		applyChanges();
	}
}

void TransformSystem::removeTransform(const TransformPtr& transform)
{
	_pendingRemove.push_back(transform);
	if (_isInited) {
		applyChanges();
	}
}

void TransformSystem::applyChanges()
{
	for (auto& transform : _pendingAdd) {
		if (transform->getParent()) {
			continue;
		}
		_transforms.push_back(transform);
	}
	_pendingAdd.clear();

	for (auto& transform : _pendingRemove) {
		auto foundIt = std::find(_transforms.begin(), _transforms.end(), transform);
		if (foundIt != _transforms.end()) {
			_transforms.erase(foundIt);
		}
	}
	_pendingRemove.clear();
}
