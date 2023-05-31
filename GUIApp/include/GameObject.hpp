#pragma once
#include <memory>
#include <vector>
#include <map>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

class Model;
class Transform;
class Component;

class GameObject
{
	using ComponentPtr = std::shared_ptr<Component>;

	class IndexGenerator
	{
	private:
		size_t _nextIndex;

	public:
		static IndexGenerator& getInstance();

		template<typename Type>
		size_t getIndex();
	};

protected:
	std::shared_ptr<Transform> _transform;
	std::vector<ComponentPtr> _components;
	std::map<size_t, ComponentPtr> _componentsMap;

public:
	GameObject();
	virtual ~GameObject() = default;

	virtual void interpolate(float value) {}
	virtual void init();
	virtual void update(float delta_time);
	virtual void predraw();
	virtual void fixedUpdate(float fixed_time) {}

	template<typename CompType>
	std::shared_ptr<CompType> addComponent();

	template<typename CompType>
	std::shared_ptr<CompType> getComponent() const;

	void setPosition(const glm::vec3& position);
	void setRotation(const glm::vec3& rotation);
	void setRotation(const glm::quat& rotation);
	void setScale(const glm::vec3& scale);

	void attachChild(const std::shared_ptr<GameObject>& child);
	const std::shared_ptr<Transform>& getTransform() { return _transform; }
};


inline GameObject::IndexGenerator& GameObject::IndexGenerator::getInstance()
{
	static IndexGenerator instance;
	return instance;
}

template<typename Type>
inline size_t GameObject::IndexGenerator::getIndex()
{
	static size_t currentIndex = _nextIndex++;
	return currentIndex;
}

template<typename CompType>
std::shared_ptr<CompType> GameObject::addComponent()
{
	size_t index = IndexGenerator::getInstance().getIndex<CompType>();
	assert(_componentsMap.count(index) == 0);

	auto behTypePtr = std::shared_ptr<CompType>(new CompType());
	behTypePtr->setOwner(this);
	_components.emplace_back(behTypePtr);
	_componentsMap.emplace(index, behTypePtr);

	if (!std::is_same_v<Component, CompType::OriginType> &&
		!std::is_same_v<CompType, CompType::OriginType>) {
		size_t parentIndex = IndexGenerator::getInstance().getIndex<CompType::OriginType>();
		assert(_componentsMap.count(parentIndex) == 0);

		_componentsMap.emplace(parentIndex, behTypePtr);
	}

	return behTypePtr;
}

template<typename CompType>
std::shared_ptr<CompType> GameObject::getComponent() const
{
	size_t index = IndexGenerator::getInstance().getIndex<CompType>();

	auto foundIt = _componentsMap.find(index);
	if (foundIt != _componentsMap.end()) {
		return std::static_pointer_cast<CompType>(foundIt->second);
	}
	return nullptr;
}
