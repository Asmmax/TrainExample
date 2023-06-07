#pragma once

class GameObject;

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

	GameObject* getOwner();
	const GameObject* getOwner() const;

private:
	void setOwner(GameObject* owner);
};
