#include "World.hpp"
#include "GameObject.hpp"
#include "common/Transform.hpp"
#include "Model.hpp"
#include "ASystem.hpp"
#include "assets/AssetManager.hpp"
#include "assets/units/SceneUnit.hpp"

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

std::vector<std::shared_ptr<GameObject>> World::spawn(const std::string& assetId)
{
	auto sceneUnit = AssetManager::getInstance().cloneAsset<SceneUnit>(assetId);
	auto objects = sceneUnit->attachTo(*this);
	for (auto& game_object : objects) {
		game_object->init();
	}
	return objects;
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

void World::deinit()
{
	for (auto& system : _systems) {
		system->deinit();
	}

	for (auto& game_object : _game_objects) {
		game_object->deinit();
	}
}
