#include "GameObject.hpp"
#include "common/Transform.hpp"
#include "AComponent.hpp"

GameObject::GameObject(World* world):
	_world(world),
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

void GameObject::deinit()
{
	for (auto component : _components) {
		component->deinit();
	}
}
