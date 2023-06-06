#include "components/TransformComponent.hpp"
#include "Transform.hpp"
#include "common/TransformSystem.hpp"
#include "GameObject.hpp"
#include "World.hpp"

TransformComponent::TransformComponent():
	_transform(std::make_shared<Transform>())
{
}

void TransformComponent::init()
{
	if (!_transform->getParent()) {
		auto transformSystem = getOwner()->getWorld()->getSystem<TransformSystem>();
		transformSystem->addTransform(_transform);
	}
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
	auto transformSystem = getOwner()->getWorld()->getSystem<TransformSystem>();
	transformSystem->removeTransform(child->getTransform());
	_transform->addChild(child->getTransform());
}