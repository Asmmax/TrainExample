#pragma once

class System
{
public:
	virtual ~System() = default;

	virtual void init() = 0;
	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;
};
