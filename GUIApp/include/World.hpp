#pragma once
#include "GameObject.hpp"
#include <memory>
#include <vector>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <string>
#include <assert.h>

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
	std::vector<GameObjectPtr> spawn(const std::string& assetId);

	template<typename SysType>
	void addSystem(const std::shared_ptr<SysType>& sys);

	template<typename SysType>
	std::shared_ptr<SysType> getSystem() const;

	template<typename CompType>
	std::shared_ptr<CompType> findComponent() const;

	void init();
	void update(float delta_time);
	void deinit();

private:
	std::vector<GameObjectPtr> _game_objects;

	std::vector<SystemPtr> _systems;
	std::map<std::type_index, SystemPtr> _systemsMap;
};

template<typename SysType>
void World::addSystem(const std::shared_ptr<SysType>& sys)
{
	static_assert(!std::is_same_v<System, SysType>);
	static_assert(!std::is_same_v<SystemCommon<SysType::OriginType>, SysType>);

	std::type_index index = std::type_index(typeid(SysType::OriginType));
	assert(_systemsMap.count(index) == 0);

	_systems.emplace_back(sys);
	_systemsMap.emplace(index, sys);
}

template<typename SysType>
std::shared_ptr<SysType> World::getSystem() const
{
	static_assert(!std::is_same_v<System, SysType>);
	static_assert(!std::is_same_v<SystemCommon<SysType::OriginType>, SysType>);

	std::type_index index = std::type_index(typeid(SysType::OriginType));

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
