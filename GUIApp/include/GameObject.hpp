#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <assert.h>

class World;
class Transform;
class Component;

class GameObject
{
	using ComponentPtr = std::shared_ptr<Component>;

protected:
	World* _world;
	std::shared_ptr<Transform> _transform;
	std::vector<ComponentPtr> _components;
	std::unordered_map<std::type_index, ComponentPtr> _componentsMap;

public:
	GameObject(World* world);

	void init();
	void update(float delta_time);
	void deinit();

	World* getWorld() { return _world; }

	template<typename CompType>
	void addComponent(const std::shared_ptr<CompType>& comp);

	template<typename CompType>
	std::shared_ptr<CompType> getComponent() const;
};

template<typename CompType>
void GameObject::addComponent(const std::shared_ptr<CompType>& comp)
{
	static_assert(!std::is_same_v<Component, CompType>);
	static_assert(!std::is_same_v<ComponentCommon<CompType::OriginType>, CompType>);

	std::type_index index = std::type_index(typeid(CompType::OriginType));
	assert(_componentsMap.count(index) == 0);

	comp->setOwner(this);
	_components.emplace_back(comp);
	_componentsMap.emplace(index, comp);
}

template<typename CompType>
std::shared_ptr<CompType> GameObject::getComponent() const
{
	static_assert(!std::is_same_v<Component, CompType>);
	static_assert(!std::is_same_v<ComponentCommon<CompType::OriginType>, CompType>);

	std::type_index index = std::type_index(typeid(CompType::OriginType));

	auto foundIt = _componentsMap.find(index);
	if (foundIt != _componentsMap.end()) {
		return std::static_pointer_cast<CompType>(foundIt->second);
	}
	return nullptr;
}
