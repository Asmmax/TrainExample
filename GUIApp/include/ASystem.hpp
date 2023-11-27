#pragma once
#include <memory>

class Window;
class World;

class System
{
public:
	using OriginType = System;

public:
	virtual ~System() = default;

	virtual void init() = 0;
	virtual void update(float delta_time) {}
	virtual void postUpdate(float delta_time) {}
	virtual void render() {}
	virtual void deinit() {}

	virtual void setWindow(Window* /*window*/) {}
	virtual void attachTo(World& world) = 0;
};
