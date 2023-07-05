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

void AInputAxisImpl::bindToChanged(void* owner, const std::function<void(float)>& callback)
{
	auto result = _actionChanged.emplace(owner, std::vector<std::function<void(float)>>{ callback });
	if (!result.second) {
		result.first->second.push_back(callback);
	}
}

void AInputAxisImpl::unbindAllChanged(void* owner)
{
	auto foundIt = _actionChanged.find(owner);
	if (foundIt != _actionChanged.end()) {
		_actionChanged.erase(foundIt);
	}
}

float AInputAxisImpl::getValue() const
{
	return _value;
}

void AInputAxisImpl::broadcastChanged()
{
	for (auto& callbackGroup : _actionChanged) {
		for (auto& callback : callbackGroup.second) {
			callback(_value);
		}
	}
}

void AInputAxisImpl::setValue(float value)
{
	if (_value == value) {
		return;
	}

	_value = value;
	broadcastChanged();
}
