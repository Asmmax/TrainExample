#pragma once
#include "events/EventListener.hpp"
#include <memory>

class GameObject;

class Component : public EventListener
{
	friend class GameObject;

public:
	using OriginType = Component;
	using Super = Component;

private:
	GameObject* _owner;

public:
	virtual ~Component() = default;

	virtual void init() = 0;
	virtual void update(float delta_time) {}
	virtual void deinit();

	virtual void attachTo(GameObject& object) = 0;
	virtual bool isSameType(const Component* component) const = 0;

	GameObject* getOwner();
	const GameObject* getOwner() const;

private:
	void setOwner(GameObject* owner);
};
