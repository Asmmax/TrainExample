#include "input/AInputAxisImpl.hpp"
#include <glm/glm.hpp>

AInputAxisImpl::AInputAxisImpl(float smooth, float minSpeed):
	_value(0.0f),
	_smooth(smooth),
	_minSpeed(minSpeed)
{
}

void AInputAxisImpl::fixedUpdate(float deltaTime)
{
	const float targetValue = getRawValue();

	if (_smooth < 1e-6) {
		setValue(targetValue);
		return;
	}

	const float factor = 1.f / (1 + deltaTime / _smooth);
	const float dif = targetValue - _value;
	if (dif == 0.f) {
		setValue(targetValue);
		return;
	}

	if (glm::abs(dif) < _minSpeed) {
		const float dir = glm::sign(dif);
		setValue(dir * glm::min(dir * _value + _minSpeed * (1 - factor), dir * targetValue));
		return;
	}

	setValue(glm::mix(targetValue, _value, factor));
}

void AInputAxisImpl::bindToChanged(EventListener* owner, const Event<float>::Callback& callback)
{
	_actionChanged.bind(owner, callback);
}

void AInputAxisImpl::unbindAllChanged(EventListener* owner)
{
	_actionChanged.unbindAll(owner);
}

float AInputAxisImpl::getValue() const
{
	return _value;
}

void AInputAxisImpl::setValue(float value)
{
	if (_value == value) {
		return;
	}

	_value = value;
	_actionChanged.broadcast(_value);
}
