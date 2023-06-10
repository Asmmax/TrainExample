#pragma once
#include "GameObject.hpp"
#include <memory>

/// @serializable @shared components @abstract
class Component
{
	friend class GameObject;

public:
	using OriginType = Component;

private:
	GameObject* _owner;

public:
	virtual ~Component() = default;

	virtual void init() = 0;
	virtual void update(float delta_time) {}

	virtual void attachTo(GameObject& object) = 0;

	GameObject* getOwner();
	const GameObject* getOwner() const;

private:
	void setOwner(GameObject* owner);
};

template <typename CompType>
class ComponentCommon : public Component, public std::enable_shared_from_this<CompType>
{
public:
	void attachTo(GameObject& object) override;
};

template<typename CompType>
void ComponentCommon<CompType>::attachTo(GameObject& object)
{
	object.addComponent<CompType>(shared_from_this());
}
