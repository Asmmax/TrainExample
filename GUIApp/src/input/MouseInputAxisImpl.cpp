#include "input/MouseInputAxisImpl.hpp"
#include "input/InputDistributor.hpp"
#include <glm/glm.hpp>

MouseInputAxisImpl::MouseInputAxisImpl(MouseAxis axis, float sensitivity) :
	_axis(axis),
	_sensitivity(sensitivity),
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
	distributor->addMouseButtonWithMoveCallback([this](double x, double y, InputEvents::MouseKey key, InputEvents::KeyState state) {
		setMousePos(x, y);
		});
	distributor->addMouseMoveCallback([this](double x, double y) {
		setMousePos(x, y);
		});
	distributor->addMouseScrollCallback([this](double step) {
		addMouseScroll(step);
		});
}

void MouseInputAxisImpl::update(float deltaTime)
{

}

float MouseInputAxisImpl::getValue() const
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

	return glm::clamp(delta * _sensitivity, -1.0f, 1.0f);
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
