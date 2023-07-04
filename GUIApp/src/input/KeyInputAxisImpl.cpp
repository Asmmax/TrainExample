#include "input/KeyInputAxisImpl.hpp"
#include "input/InputAction.hpp"
#include <glm/glm.hpp>

KeyInputAxisImpl::KeyInputAxisImpl(const InputActionPtr& negativeAction, const InputActionPtr& positiveAction, float smooth):
	_value(0.0f),
	_negativeAction(negativeAction),
	_positiveAction(positiveAction),
	_smooth(smooth)
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
	_value = glm::mix(targetValue, _value, factor);
}

float KeyInputAxisImpl::getValue() const
{
	return _value;
}
