#include "input/KeyInputAxisImpl.hpp"
#include "input/InputAction.hpp"
#include <glm/glm.hpp>

KeyInputAxisImpl::KeyInputAxisImpl(const InputActionPtr& negativeAction, const InputActionPtr& positiveAction, float speed, float recoverySpeed):
	_value(0.0f),
	_negativeAction(negativeAction),
	_positiveAction(positiveAction),
	_speed(speed),
	_recoverySpeed(recoverySpeed)
{
}

void KeyInputAxisImpl::init(InputDistributor* distributor)
{
	_negativeAction->init(distributor);
	_positiveAction->init(distributor);
}

void KeyInputAxisImpl::update(float deltaTime)
{
	float direction = 0.f;
	if (_negativeAction->isPressed()) {
		direction -= 1.0f;
	}
	if (_positiveAction->isPressed()) {
		direction += 1.0f;
	}

	_value += direction * _speed * deltaTime;

	float recoveryDirection = glm::sign(-_value);
	float recoveryStep = recoveryDirection * _recoverySpeed * deltaTime;
	recoveryStep = glm::sign(recoveryStep) * glm::min(glm::abs(recoveryStep), glm::abs(_value));
	_value += recoveryStep;
}

float KeyInputAxisImpl::getValue() const
{
	return _value;
}
