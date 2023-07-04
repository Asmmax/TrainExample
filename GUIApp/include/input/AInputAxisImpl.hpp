#pragma once

class InputDistributor;

/// @serializable @polymorphic @abstract
class AInputAxisImpl
{
public:
	virtual void init(InputDistributor* distributor) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void fixedUpdate(float deltaTime) = 0;
	virtual float getValue() const = 0;
};
