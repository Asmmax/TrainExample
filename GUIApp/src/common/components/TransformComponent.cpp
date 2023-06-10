#include "common/components/TransformComponent.hpp"
#include "common/Transform.hpp"
#include "common/TransformSystem.hpp"
#include "GameObject.hpp"
#include "World.hpp"

TransformComponent::TransformComponent(const std::vector<Ptr>& children /*= std::vector<Ptr>()*/):
	_transform(std::make_shared<Transform>()),
	_pendingChildren(children),
	_isInited(false)
{
}

void TransformComponent::init()
{
	auto transformSystem = getOwner()->getWorld()->getSystem<TransformSystem>();
	if (!transformSystem) {
		return;
	}

	transformSystem->addTransform(_transform);
	applyAttachChild();

	_isInited = true;
}

void TransformComponent::setPosition(const glm::vec3& position)
{
	_transform->setPosition(position);
}

void TransformComponent::setRotation(const glm::vec3& rotation)
{
	auto radianEulers = glm::radians(rotation);
	_transform->setRotation(radianEulers);
}

void TransformComponent::setRotation(const glm::quat& rotation)
{
	_transform->setRotation(rotation);
}

void TransformComponent::setScale(const glm::vec3& scale)
{
	_transform->setScale(scale);
}

void TransformComponent::attachChild(const std::shared_ptr<TransformComponent>& child)
{
	_pendingChildren.push_back(child);
	if (_isInited) {
		applyAttachChild();
	}
}

void TransformComponent::applyAttachChild()
{
	auto transformSystem = getOwner()->getWorld()->getSystem<TransformSystem>();
	if (!transformSystem) {
		return;
	}

	for (auto& child : _pendingChildren) {
		transformSystem->removeTransform(child->getTransform());
		_transform->addChild(child->getTransform());
	}
	_pendingChildren.clear();
}
