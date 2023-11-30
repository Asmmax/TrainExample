#pragma once
#include "GameObject.hpp"
#include "ASystem.hpp"
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <array>
#include <typeindex>
#include <typeinfo>
#include <string>
#include <functional>
#include <assert.h>

#define MAX_COUNT_TIMED_CALLBACKS 1000

class Transform;

class World
{
	using GameObjectPtr = std::shared_ptr<GameObject>;
	using SystemPtr = std::shared_ptr<System>;
	
	struct TimedCallback
	{
		std::function<void(World*)> callback;
		float redundantTime = 0.f;
		float periodTime = 0.f;
	};

public:
	World();
	~World();

	GameObjectPtr createGameObject();
	void removeGameObject(const GameObjectPtr& gameObject);
	std::vector<GameObjectPtr> spawn(const std::string& assetId);

	template<typename SysType>
	void addSystem(const std::shared_ptr<SysType>& sys);

	template<typename SysType>
	std::shared_ptr<SysType> getSystem() const;

	template<typename CompType>
	std::shared_ptr<CompType> findComponent() const;

	size_t delay(float delayTime, const std::function<void(World*)>& callback);
	size_t repeat(float periodTime, const std::function<void(World*)>& callback);
	void stop(size_t id);

	void init();
	void update(float delta_time);
	void render();
	void deinit();

private:
	size_t getNextCallbackId();
	void freeCallbackId(size_t id);

private:
	std::vector<GameObjectPtr> _game_objects;

	std::vector<SystemPtr> _systems;
	std::map<std::type_index, SystemPtr> _systemsMap;

	std::unordered_map<size_t, TimedCallback> _timedCallbacks;
	std::array<bool, MAX_COUNT_TIMED_CALLBACKS> _busiedCallbackIds;
};

template<typename SysType>
void World::addSystem(const std::shared_ptr<SysType>& sys)
{
	static_assert(!std::is_same_v<System, SysType>);

	std::type_index index = std::type_index(typeid(typename SysType::OriginType));
	assert(_systemsMap.count(index) == 0);

	_systems.emplace_back(sys);
	_systemsMap.emplace(index, sys);
}

template<typename SysType>
std::shared_ptr<SysType> World::getSystem() const
{
	static_assert(!std::is_same_v<System, SysType>);

	std::type_index index = std::type_index(typeid(typename SysType::OriginType));

	auto foundIt = _systemsMap.find(index);
	if (foundIt != _systemsMap.end()) {
		return std::static_pointer_cast<SysType>(foundIt->second);
	}
	return nullptr;
}

template<typename CompType>
std::shared_ptr<CompType> World::findComponent() const
{
	for (const auto& gameObject : _game_objects) {
		auto result = gameObject->getComponent<CompType>();
		if (result) {
			return result;
		}
	}
	return nullptr;
}
