#pragma once
#include "events/AEvent.hpp"
#include <functional>
#include <vector>
#include <unordered_map>

class InputDistributor;

/// @serializable @polymorphic @abstract
class AInputAxisImpl
{
private:
	float _value;
	float _smooth;
	float _minSpeed;

protected:
	Event<float> _actionChanged;

public:
	AInputAxisImpl(float smooth, float minSpeed);
	virtual ~AInputAxisImpl() = default;

	virtual void init(InputDistributor* distributor) = 0;
	virtual void update(float deltaTime) = 0;

	virtual void fixedUpdate(float deltaTime);

	void bindToChanged(EventListener* owner, const Event<float>::Callback& callback);
	void unbindAllChanged(EventListener* owner);
	float getValue() const;

protected:
	virtual float getRawValue() const = 0;

	void setValue(float value);
};
