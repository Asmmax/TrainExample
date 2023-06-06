#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

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
	virtual ~GameObject() = default;

	virtual void init();
	virtual void update(float delta_time);

	World* getWorld() { return _world; }

	template<typename CompType>
	std::shared_ptr<CompType> addComponent();

	template<typename CompType>
	std::shared_ptr<CompType> getComponent() const;
};

template<typename CompType>
std::shared_ptr<CompType> GameObject::addComponent()
{
	std::type_index index = std::type_index(typeid(CompType));
	assert(_componentsMap.count(index) == 0);

	auto behTypePtr = std::shared_ptr<CompType>(new CompType());
	behTypePtr->setOwner(this);
	_components.emplace_back(behTypePtr);
	_componentsMap.emplace(index, behTypePtr);

	if (!std::is_same_v<Component, CompType::OriginType> &&
		!std::is_same_v<CompType, CompType::OriginType>) {
		std::type_index parentIndex = std::type_index(typeid(CompType::OriginType));
		assert(_componentsMap.count(parentIndex) == 0);

		_componentsMap.emplace(parentIndex, behTypePtr);
	}

	return behTypePtr;
}

template<typename CompType>
std::shared_ptr<CompType> GameObject::getComponent() const
{
	std::type_index index = std::type_index(typeid(CompType));

	auto foundIt = _componentsMap.find(index);
	if (foundIt != _componentsMap.end()) {
		return std::static_pointer_cast<CompType>(foundIt->second);
	}
	return nullptr;
}
