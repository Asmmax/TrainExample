#pragma once
#include <memory>
#include "World.hpp"

class Window;
class World;

/// @serializable @polymorphic @abstract
class System
{
public:
	using OrigiType = System;

public:
	virtual ~System() = default;

	virtual void init() = 0;
	virtual void update(float delta_time) {}
	virtual void postUpdate(float delta_time) {}
	virtual void deinit() {}

	virtual void setWindow(Window* /*window*/) {}
	virtual void attachTo(World& world) = 0;
};

template<typename SystemType>
class SystemCommon : public System, public std::enable_shared_from_this<SystemType>
{
public:
	using OriginType = SystemType;

public:
	void attachTo(World& world) override;
};

template<typename SystemType>
void SystemCommon<SystemType>::attachTo(World& world)
{
	world.addSystem<SystemType>(shared_from_this());
}
