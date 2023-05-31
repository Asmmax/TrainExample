#include "GameObject.hpp"
#include "Transform.hpp"
#include "components/AComponent.hpp"

GameObject::GameObject():
	_transform(std::make_shared<Transform>())
{
}

void GameObject::init()
{
	for (auto component : _components) {
		component->init();
	}
}

void GameObject::update(float delta_time)
{
	for (auto component : _components) {
		component->update(delta_time);
	}
}

void GameObject::predraw()
{
	for (auto component : _components) {
		component->predraw();
	}
}

void GameObject::setPosition(const glm::vec3& position)
{
	_transform->setPosition(position);
}

void GameObject::setRotation(const glm::vec3& rotation)
{
	auto radianEulers = glm::radians(rotation);
	_transform->setRotation(radianEulers);
}

void GameObject::setRotation(const glm::quat& rotation)
{
	_transform->setRotation(rotation);
}

void GameObject::setScale(const glm::vec3& scale)
{
	_transform->setScale(scale);
}

void GameObject::attachChild(const std::shared_ptr<GameObject>& child)
{
	_transform->addChild(child->getTransform());
}
