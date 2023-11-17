#include "input/MouseInputAxisImpl.hpp"
#include "input/InputDistributor.hpp"

MouseInputAxisImpl::MouseInputAxisImpl(MouseAxis axis, float sensitivity, float smooth, float minSpeed) :
	AInputAxisImpl(smooth, minSpeed),
	_axis(axis),
	_sensitivity(sensitivity),
	_lastXPos(0),
	_lastYPos(0),
	_xPos(0.0),
	_yPos(0.0),
	_scrollPos(0.0),
	_firstMousePos(true)
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

float MouseInputAxisImpl::getRawValue(float frameTime) const
{
	return getDelta() * _sensitivity / frameTime;
}

void MouseInputAxisImpl::setMousePos(double xPos, double yPos)
{
	if (_firstMousePos) {
		_lastXPos = xPos;
		_lastYPos = yPos;
		_firstMousePos = false;
	}
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
