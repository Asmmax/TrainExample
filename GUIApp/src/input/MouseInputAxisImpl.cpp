#include "input/MouseInputAxisImpl.hpp"
#include "input/InputDistributor.hpp"
#include <glm/glm.hpp>

MouseInputAxisImpl::MouseInputAxisImpl(MouseAxis axis, float sensitivity, float smooth, float minSpeed) :
	_axis(axis),
	_sensitivity(sensitivity),
	_smooth(smooth),
	_minSpeed(minSpeed),
	_value(0.0f),
	_rawValue(0.0f),
	_lastXPos(0),
	_lastYPos(0),
	_xPos(0.0),
	_yPos(0.0),
	_scrollPos(0.0)
{
}

void MouseInputAxisImpl::init(InputDistributor* distributor)
{
	distributor->addPreHandleCallback([this]() {
		clear();
		});

	switch (_axis)
	{
	case MouseAxis::HORIZONTAL:
	case MouseAxis::VERTICAL:
		distributor->addMouseButtonWithMoveCallback([this](double x, double y, InputEvents::MouseKey key, InputEvents::KeyState state) {
			setMousePos(x, y);
			});
		distributor->addMouseMoveCallback([this](double x, double y) {
			setMousePos(x, y);
			});
		break;
	case MouseAxis::SCROLL:
		distributor->addMouseScrollCallback([this](double step) {
			addMouseScroll(step);
			});
		break;
	default:
		break;
	}
}

void MouseInputAxisImpl::update(float deltaTime)
{
	_rawValue += getDelta() * _sensitivity;
}

void MouseInputAxisImpl::fixedUpdate(float deltaTime)
{
	const float targetValue = _rawValue;
	_rawValue = 0.f;

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

float MouseInputAxisImpl::getValue() const
{
	return _value;
}

void MouseInputAxisImpl::setMousePos(double xPos, double yPos)
{
	_xPos = xPos;
	_yPos = yPos;
}

void MouseInputAxisImpl::addMouseScroll(double step)
{
	_scrollPos += step;
}

void MouseInputAxisImpl::clear()
{
	_scrollPos = 0;
	_lastXPos = _xPos;
	_lastYPos = _yPos;
}

float MouseInputAxisImpl::getDelta() const
{
	float delta = 0.f;

	switch (_axis)
	{
	case MouseAxis::HORIZONTAL:
		delta = static_cast<float>(_xPos - _lastXPos);
		break;
	case MouseAxis::VERTICAL:
		delta = static_cast<float>(_yPos - _lastYPos);
		break;
	case MouseAxis::SCROLL:
		delta = static_cast<float>(_scrollPos);
		break;
	default:
		break;
	}

	return delta;
}
