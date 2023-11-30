#include "assets/units/SceneUnit.hpp"
#include "World.hpp"
#include "AComponent.hpp"

SceneUnit::SceneUnit(const std::vector<SceneObject>& objects):
	_objects(objects)
{
}

std::vector<std::shared_ptr<GameObject>> SceneUnit::attachTo(World& world)
{
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	gameObjects.reserve(_objects.size());

	for (auto& object : _objects) {
		auto newGameObject = world.createGameObject();
		gameObjects.push_back(newGameObject);
		for (auto& component : object) {
			component->attachTo(*newGameObject);
		}
	}

	return gameObjects;
}
