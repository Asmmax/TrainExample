#include "input/AInputAxisImpl.hpp"
#include <glm/glm.hpp>

AInputAxisImpl::AInputAxisImpl(float smooth, float minSpeed):
	_value(0.0f),
	_smooth(smooth),
	_minSpeed(minSpeed),
	_currentRawValue(0.0f),
	_residualValue(0.0f),
	_interpolatingCoeff(0.0f)
{
}

void AInputAxisImpl::startFrame(float frameTime)
{
	_currentRawValue = getRawValue(frameTime);
}

void AInputAxisImpl::update(float deltaTime)
{
	const float targetValue = _residualValue + (1.0f - _interpolatingCoeff) * _currentRawValue;
	_residualValue = 0.f;
	_interpolatingCoeff = 0.f;

	const float value = getValue();

	if (_smooth < 1e-6) {
		setValue(targetValue);
		return;
	}

	const float factor = 1.f / (1 + deltaTime / _smooth);
	const float dif = targetValue - value;
	if (dif == 0.f) {
		setValue(targetValue);
		return;
	}

	if (glm::abs(dif) < _minSpeed) {
		const float dir = glm::sign(dif);
		const float linValue = value + dir * _minSpeed * (1 - factor);
		const float clampedValue = dir > 0.f ? glm::min(linValue, targetValue) : glm::max(linValue, targetValue);
		setValue(clampedValue);
		return;
	}

	setValue(glm::mix(targetValue, value, factor));
}

void AInputAxisImpl::endFrame(float interpolatingCoeff)
{
	_residualValue += (interpolatingCoeff - _interpolatingCoeff) * _currentRawValue;
	_interpolatingCoeff = interpolatingCoeff;
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
