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
	virtual void init() = 0;
	virtual void update(float delta_time) {}
	virtual void predraw() {}

	GameObject* getOwner();
	const GameObject* getOwner() const;

private:
	void setOwner(GameObject* owner);
};
