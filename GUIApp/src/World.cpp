#include "World.hpp"
#include "GameObject.hpp"
#include "common/Transform.hpp"
#include "Model.hpp"
#include "ASystem.hpp"
#include "assets/AssetManager.hpp"
#include "assets/units/SceneUnit.hpp"

World::World()
{
	_busiedCallbackIds.fill(false);
}

World::~World() = default;

std::shared_ptr<GameObject> World::createGameObject()
{
	auto gameObject = std::make_shared<GameObject>(this);
	_game_objects.push_back(gameObject);
	return gameObject;
}

void World::removeGameObject(const GameObjectPtr& gameObject)
{
	auto lastIt = std::remove(_game_objects.begin(), _game_objects.end(), gameObject);
	if (lastIt == _game_objects.end()) {
		return;
	}

	gameObject->deinit();
	_game_objects.erase(lastIt, _game_objects.end());
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

size_t World::delay(float delayTime, const std::function<void(World*)>& callback)
{
	size_t newId = getNextCallbackId();
	TimedCallback tc;
	tc.callback = callback;
	tc.redundantTime = delayTime;
	_timedCallbacks.emplace(newId, tc);
	return newId;
}

size_t World::repeat(float periodTime, const std::function<void(World*)>& callback)
{
	assert(periodTime > 0.f);
	if (periodTime <= 0.f) {
		return size_t(-1);
	}

	size_t newId = getNextCallbackId();
	TimedCallback tc;
	tc.callback = callback;
	tc.redundantTime = periodTime;
	tc.periodTime = periodTime;
	_timedCallbacks.emplace(newId, tc);
	return newId;
}

void World::stop(size_t id)
{
	auto foundIt = _timedCallbacks.find(id);
	if (foundIt == _timedCallbacks.end()) {
		return;
	}
	_timedCallbacks.erase(foundIt);
	freeCallbackId(id);
}

void World::init()
{
	for (auto& system : _systems) {
		system->init();
	}

	for (auto& game_object : _game_objects) {
		game_object->init();
	}
}

void World::update(float delta_time)
{
	for (auto it = _timedCallbacks.begin(); it != _timedCallbacks.end();) {
		auto& tc = it->second;
		tc.redundantTime -= delta_time;
		if (tc.redundantTime <= 0.f) {
			tc.redundantTime += tc.periodTime;
			tc.callback(this);
		}
		while (tc.redundantTime <= 0.f && tc.periodTime > 0.f) {
			tc.redundantTime += tc.periodTime;
			tc.callback(this);
		}

		if (tc.redundantTime <= 0.f) {
			it = _timedCallbacks.erase(it);
		}
		else {
			it++;
		}
	}

	for (auto& system : _systems) {
		system->update(delta_time);
	}

	for (auto& game_object : _game_objects) {
		game_object->update(delta_time);
	}

	for (auto& system : _systems) {
		system->postUpdate(delta_time);
	}
}

void World::deinit()
{
	for (auto& game_object : _game_objects) {
		game_object->deinit();
	}

	for (auto& system : _systems) {
		system->deinit();
	}
}

size_t World::getNextCallbackId()
{
	auto firstFree = std::find(_busiedCallbackIds.begin(), _busiedCallbackIds.end(), false);
	assert(firstFree != _busiedCallbackIds.end());
	if (firstFree == _busiedCallbackIds.end()) {
		return size_t(-1);
	}
	*firstFree = true;
	return std::distance(_busiedCallbackIds.begin(), firstFree);
}

void World::freeCallbackId(size_t id)
{
	assert(id < MAX_COUNT_TIMED_CALLBACKS);
	_busiedCallbackIds[id] = false;
}
