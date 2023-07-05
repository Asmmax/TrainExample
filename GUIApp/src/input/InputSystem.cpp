#include "input/InputSystem.hpp"
#include "Window.hpp"
#include "input/InputAction.hpp"
#include "input/InputAxis.hpp"
#include "input/InputDistributor.hpp"
#include <algorithm>

InputSystem::InputSystem(const std::vector<InputActionEntry>& actions, const std::vector<InputAxisEntry>& axes, float fixedTime) :
	_window(nullptr),
	_needMouseCaptureWhileMousePressed(false),
	_fixedTime(fixedTime),
	_timeRedutant(0.f),
	_distributor(std::make_shared<InputDistributor>())
{
	for (auto& actionEntry : actions) {
		_actions.emplace(actionEntry.name, actionEntry.action);
	}
	for (auto& axisEntry : axes) {
		_axes.emplace(axisEntry.name, axisEntry.axis);
	}
	_mousePressed.resize(static_cast<size_t>(InputEvents::MouseKey::MAX_COUNT), false);
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

		const size_t keyId = static_cast<size_t>(key);

		if (state == InputEvents::KeyState::KEY_DOWN) {
			if (!anyMousePressed()) {
				_window->captureMouse();
			}
			markMousePressed(keyId, true);
		}
		else if (state == InputEvents::KeyState::KEY_UP) {
			markMousePressed(keyId, false);
			if (!anyMousePressed()) {
				_window->uncaptureMouse();
			}
		}
		});

	_distributor->bindAllTo(_window);
}

void InputSystem::update(float delta_time)
{
	_timeRedutant += delta_time;
	while (_timeRedutant >= _fixedTime) {
		_timeRedutant -= _fixedTime;
		fixedUpdate();
	}

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
		if (anyMousePressed()) {
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

void InputSystem::bindToAxisChanged(const std::string& name, void* owner, const std::function<void(float)>& callback)
{
	assert(_axes.find(name) != _axes.end());
	_axes.at(name)->bindToChanged(owner, callback);
}

void InputSystem::unbindAllAxisChanged(const std::string& name, void* owner)
{
	assert(_axes.find(name) != _axes.end());
	_axes.at(name)->unbindAllChanged(owner);
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

void InputSystem::fixedUpdate()
{
	for (auto& axis : _axes) {
		axis.second->fixedUpdate(_fixedTime);
	}
}

void InputSystem::markMousePressed(size_t keyId, bool isPressed)
{
	_mousePressed[keyId] = isPressed;
}

bool InputSystem::anyMousePressed()
{
	auto fountIt = std::find(_mousePressed.begin(), _mousePressed.end(), true);
	return fountIt != _mousePressed.end();
}
