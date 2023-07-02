#include "input/InputSystem.hpp"
#include "Window.hpp"
#include "input/InputAction.hpp"
#include "input/InputAxis.hpp"
#include "input/InputDistributor.hpp"
#include <glm/glm.hpp>

InputSystem::InputSystem(const std::vector<InputActionEntry>& actions, const std::vector<InputAxisEntry>& axes) :
	_window(nullptr),
	_needMouseCaptureWhileMousePressed(false),
	_mousePressed(false),
	_distributor(std::make_shared<InputDistributor>())
{
	for (auto& actionEntry : actions) {
		_actions.emplace(actionEntry.name, actionEntry.action);
	}
	for (auto& axisEntry : axes) {
		_axes.emplace(axisEntry.name, axisEntry.axis);
	}
}

void InputSystem::init()
{
	for (auto& action : _actions) {
		action.second->init(_distributor.get());
	}

	for (auto& axis : _axes) {
		axis.second->init(_distributor.get());
	}

	_distributor->addMouseButtonCallback([this](InputEvents::MouseKey key, InputEvents::KeyState state) {
		if (!_needMouseCaptureWhileMousePressed) {
			return;
		}

		if (state == InputEvents::KeyState::KEY_DOWN) {
			_window->captureMouse();
			_mousePressed = true;
		}
		else if (state == InputEvents::KeyState::KEY_UP) {
			_window->uncaptureMouse();
			_mousePressed = false;
		}
		});

	_distributor->bindAllTo(_window);
}

void InputSystem::update(float delta_time)
{
	for (auto& axis : _axes) {
		axis.second->update(delta_time);
	}
}

void InputSystem::setWindow(Window* window)
{
	_window = window;
}

void InputSystem::setMouseCaptureMode(MouseCaptureMode mode)
{
	switch (mode)
	{
	case MouseCaptureMode::DISABLE:
		_window->uncaptureMouse();
		_needMouseCaptureWhileMousePressed = false;
		break;
	case MouseCaptureMode::ENABLE:
		_window->captureMouse();
		_needMouseCaptureWhileMousePressed = false;
		break;
	case MouseCaptureMode::WHILE_MOUSE_PRESSED:
		if (_mousePressed) {
			_window->captureMouse();
		}
		else {
			_window->uncaptureMouse();
		}
		_needMouseCaptureWhileMousePressed = true;
		break;
	default:
		break;
	}
}

float InputSystem::getAxisValue(const std::string& name) const
{
	assert(_axes.find(name) != _axes.end());
	return _axes.at(name)->getValue();
}

bool InputSystem::isActionPressed(const std::string& name) const
{
	assert(_actions.find(name) != _actions.end());
	return _actions.at(name)->isPressed();
}

void InputSystem::bindToActionPressed(const std::string& name, void* owner, const std::function<void()>& callback)
{
	assert(_actions.find(name) != _actions.end());
	_actions.at(name)->bindToPressed(owner, callback);
}

void InputSystem::bindToActionReleased(const std::string& name, void* owner, const std::function<void()>& callback)
{
	assert(_actions.find(name) != _actions.end());
	_actions.at(name)->bindToReleased(owner, callback);
}

void InputSystem::unbindAllActionPressed(const std::string& name, void* owner)
{
	assert(_actions.find(name) != _actions.end());
	_actions.at(name)->unbindAllPressed(owner);
}

void InputSystem::unbindAllActionReleased(const std::string& name, void* owner)
{
	assert(_actions.find(name) != _actions.end());
	_actions.at(name)->unbindAllReleased(owner);
}
