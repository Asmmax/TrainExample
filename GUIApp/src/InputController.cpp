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
	_isLeftButtonPressed(false)
{
}

void InputController::bind(Window* window)
{
	window->setPreHandleCallback([this]() {
		clear();
	});
	window->setMouseRightButtonDownCallback([this](double x, double y) {
		_isRightButtonPressed = true;
		});
	window->setMouseRightButtonUpCallback([this](double x, double y) {
		_isRightButtonPressed = false;
		});
	window->setMouseLeftButtonDownCallback([this](double x, double y) {
		_isLeftButtonPressed = true;
		});
	window->setMouseLeftButtonUpCallback([this](double x, double y) {
		_isLeftButtonPressed = false;
		});
	window->setMouseMoveCallback([this](double x, double y) {
		setMousePos(x, y);
		});
	window->setMouseScrollCallback([this](double step) {
		addMouseScroll(step);
		});
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
