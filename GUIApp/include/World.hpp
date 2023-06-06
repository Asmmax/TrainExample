#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>

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

	template<typename SysType, typename... Args>
	std::shared_ptr<SysType> addSystem(Args&&... args);

	template<typename SysType>
	std::shared_ptr<SysType> getSystem() const;

	void init();
	void update(float delta_time);

private:
	std::vector<GameObjectPtr> _game_objects;

	std::vector<SystemPtr> _systems;
	std::unordered_map<std::type_index, SystemPtr> _systemsMap;
};

template<typename SysType, typename... Args>
std::shared_ptr<SysType> World::addSystem(Args&&... args)
{
	std::type_index index = std::type_index(typeid(SysType));
	assert(_systemsMap.count(index) == 0);

	auto sysTypePtr = std::shared_ptr<SysType>(new SysType(std::forward<Args>(args)...));
	_systems.emplace_back(sysTypePtr);
	_systemsMap.emplace(index, sysTypePtr);
	return sysTypePtr;
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
