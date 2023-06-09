#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <assert.h>

class GameObject;
class System;
class Transform;

class World
{
	using GameObjectPtr = std::shared_ptr<GameObject>;
	using SystemPtr = std::shared_ptr<System>;

public:
	World();
	~World();

	GameObjectPtr createGameObject();

	template<typename SysType>
	void addSystem(const std::shared_ptr<SysType>& sys);

	template<typename SysType>
	std::shared_ptr<SysType> getSystem() const;

	void init();
	void update(float delta_time);

private:
	std::vector<GameObjectPtr> _game_objects;

	std::vector<SystemPtr> _systems;
	std::unordered_map<std::type_index, SystemPtr> _systemsMap;
};

template<typename SysType>
void World::addSystem(const std::shared_ptr<SysType>& sys)
{
	std::type_index index = std::type_index(typeid(SysType));
	assert(_systemsMap.count(index) == 0);

	_systems.emplace_back(sys);
	_systemsMap.emplace(index, sys);
}

template<typename SysType>
std::shared_ptr<SysType> World::getSystem() const
{
	std::type_index index = std::type_index(typeid(SysType));

	auto foundIt = _systemsMap.find(index);
	if (foundIt != _systemsMap.end()) {
		return std::static_pointer_cast<SysType>(foundIt->second);
	}
	return nullptr;
}
