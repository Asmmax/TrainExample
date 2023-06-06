#include "input/InputSystem.hpp"
#include "Window.hpp"
#include <glm/glm.hpp>

InputSystem::InputSystem(Window* window) :
	_window(window),
	_scrollSpeed(1.2),
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

void InputSystem::init()
{
	_window->setPreHandleCallback([this]() {
		clear();
		});
	_window->setMouseButtonCallback([this](InputEvents::MouseKey key, InputEvents::KeyState state) {
		if (state == InputEvents::KeyState::KEY_DOWN) {
			if (key == InputEvents::MouseKey::LEFT_BUTTON) {
				_isLeftButtonPressed = true;
			}
			else if (key == InputEvents::MouseKey::RIGHT_BUTTON) {
				_isRightButtonPressed = true;
			}

			if (_mouseCaptured) {
				_window->captureMouse();
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
				_window->uncaptureMouse();
			}
		}
		});
	_window->setMouseButtonWithMoveCallback([this](double x, double y, InputEvents::MouseKey key, InputEvents::KeyState state) {
		setMousePos(x, y);
		});
	_window->setMouseMoveCallback([this](double x, double y) {
		setMousePos(x, y);
		});
	_window->setMouseScrollCallback([this](double step) {
		addMouseScroll(step);
		});
}

void InputSystem::update(float delta_time)
{
}

void InputSystem::draw()
{
}


void InputSystem::setScrollSpeed(double scrollSpeed)
{
	_scrollSpeed = scrollSpeed;
}

void InputSystem::setMouseCaptureWhilePressed(bool flag)
{
	_mouseCaptured = flag;
}

double InputSystem::GetScrollDelta() const
{
	return glm::pow(_scrollSpeed, -_scrollPos);
}

void InputSystem::setMousePos(double xPos, double yPos)
{
	_xPos = xPos;
	_yPos = yPos;
}

void InputSystem::addMouseScroll(double step)
{
	_scrollPos += step;
}

void InputSystem::clear()
{
	_scrollPos = 0;
	_lastXPos = _xPos;
	_lastYPos = _yPos;
}
