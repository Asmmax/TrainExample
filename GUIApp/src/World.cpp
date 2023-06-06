#include "World.hpp"
#include "GameObject.hpp"
#include "common/Transform.hpp"
#include "Model.hpp"
#include "ASystem.hpp"

World::World()
{
}

World::~World() = default;

std::shared_ptr<GameObject> World::createGameObject()
{
	auto gameObject = std::make_shared<GameObject>(this);
	_game_objects.push_back(gameObject);
	return gameObject;
}

void World::init()
{
	for (auto& game_object : _game_objects) {
		game_object->init();
	}

	for (auto& system : _systems) {
		system->init();
	}
}

void World::update(float delta_time)
{
	for (auto& game_object : _game_objects) {
		game_object->update(delta_time);
	}

	for (auto& system : _systems) {
		system->update(delta_time);
	}
}
