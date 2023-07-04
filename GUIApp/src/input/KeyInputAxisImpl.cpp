#include "input/KeyInputAxisImpl.hpp"
#include "input/InputAction.hpp"
#include <glm/glm.hpp>

KeyInputAxisImpl::KeyInputAxisImpl(const InputActionPtr& negativeAction, const InputActionPtr& positiveAction, float smooth, float minSpeed):
	_value(0.0f),
	_negativeAction(negativeAction),
	_positiveAction(positiveAction),
	_smooth(smooth),
	_minSpeed(minSpeed)
{
}

void KeyInputAxisImpl::init(InputDistributor* distributor)
{
	_negativeAction->init(distributor);
	_positiveAction->init(distributor);
}

void KeyInputAxisImpl::update(float deltaTime)
{
	float targetValue = 0.f;
	if (_negativeAction->isPressed()) {
		targetValue -= 1.0f;
	}
	if (_positiveAction->isPressed()) {
		targetValue += 1.0f;
	}

	if (_smooth < 1e-6) {
		_value = targetValue;
		return;
	}

	const float factor = 1.f / (1 + deltaTime / _smooth);
	const float dif = targetValue - _value;
	if (dif == 0.f) {
		_value = targetValue;
		return;
	}

	if (glm::abs(dif) < _minSpeed) {
		const float dir = glm::sign(dif);
		_value = dir * glm::min(dir * _value + _minSpeed * (1 - factor), dir * targetValue);
		return;
	}

	_value = glm::mix(targetValue, _value, factor);
}

float KeyInputAxisImpl::getValue() const
{
	return _value;
}
