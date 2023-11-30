#pragma once
#include "events/AEvent.hpp"
#include <functional>
#include <vector>
#include <unordered_map>

class InputDistributor;

class AInputAxisImpl
{
private:
	float _value;
	float _smooth;
	float _minSpeed;

	float _currentRawValue;
	float _residualValue;
	float _interpolatingCoeff;

protected:
	Event<float> _actionChanged;

public:
	AInputAxisImpl(float smooth, float minSpeed);
	virtual ~AInputAxisImpl() = default;

	virtual void init(InputDistributor* distributor) = 0;

	void startFrame(float frameTime);
	void update(float deltaTime);
	void endFrame(float interpolatingCoeff);

	void bindToChanged(EventListener* owner, const Event<float>::Callback& callback);
	void unbindAllChanged(EventListener* owner);
	float getValue() const;

	void reset();
	virtual void resetMouse() {}

protected:
	virtual float getRawValue(float frameTime) const = 0;
	void setValue(float value);
};
