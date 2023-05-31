#include "InputController.hpp"
#include "Window.hpp"
#include <glm/glm.hpp>

InputController::InputController(double scrollSpeed):
	_scrollSpeed(scrollSpeed),
	_lastXPos(0),
	_lastYPos(0),
	_xPos(0.0),
	_yPos(0.0),
	_scrollPos(0.0),
	_isRightButtonPressed(false),
	_isLeftButtonPressed(false),
	_mouseCaptured(false)
{
}

void InputController::bind(Window* window)
{
	window->setPreHandleCallback([this]() {
		clear();
	});
	window->setMouseButtonCallback([this, window](InputEvents::MouseKey key, InputEvents::KeyState state) {
		if (state == InputEvents::KeyState::KEY_DOWN) {
			if (key == InputEvents::MouseKey::LEFT_BUTTON) {
				_isLeftButtonPressed = true;
			}
			else if (key == InputEvents::MouseKey::RIGHT_BUTTON) {
				_isRightButtonPressed = true;
			}

			if (_mouseCaptured) {
				window->captureMouse();
			}
		}
		else if (state == InputEvents::KeyState::KEY_UP) {
			if (key == InputEvents::MouseKey::LEFT_BUTTON) {
				_isLeftButtonPressed = false;
			}
			else if (key == InputEvents::MouseKey::RIGHT_BUTTON) {
				_isRightButtonPressed = false;
			}

			if (_mouseCaptured) {
				window->uncaptureMouse();
			}
		}
		});
	window->setMouseButtonWithMoveCallback([this](double x, double y, InputEvents::MouseKey key, InputEvents::KeyState state) {
		setMousePos(x, y);
		});
	window->setMouseMoveCallback([this](double x, double y) {
		setMousePos(x, y);
		});
	window->setMouseScrollCallback([this](double step) {
		addMouseScroll(step);
		});
}

void InputController::setMouseCaptureWhilePressed(bool flag)
{
	_mouseCaptured = flag;
}

double InputController::GetScrollDelta() const
{ 
	return glm::pow(_scrollSpeed, -_scrollPos);
}

void InputController::setMousePos(double xPos, double yPos)
{
	_xPos = xPos;
	_yPos = yPos;
}

void InputController::addMouseScroll(double step)
{
	_scrollPos += step;
}

void InputController::clear()
{
	_scrollPos = 0;
	_lastXPos = _xPos;
	_lastYPos = _yPos;
}
