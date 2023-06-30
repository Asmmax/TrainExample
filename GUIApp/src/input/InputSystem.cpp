#include "input/InputSystem.hpp"
#include "Window.hpp"
#include <glm/glm.hpp>

InputSystem::InputSystem(const std::vector<Action>& actions) :
	_window(nullptr),
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
	for (auto& action : actions) {
		_actionPressed.emplace(action.name, ActionEvent());
		_actionReleased.emplace(action.name, ActionEvent());
		_actionStates[action.name] = false;
		for (auto& key : action.keys) {
			_keysToActions[key] = action.name;
		}
	}
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
	_window->setKeyCallback([this](InputEvents::KeyboardKey key, InputEvents::KeyState state, InputEvents::KeyMod mod) {
		if (state == InputEvents::KeyState::KEY_DOWN) {
			setActionState(static_cast<ActionKey>(key), true);
			broadcastActionPressed(static_cast<ActionKey>(key));
		}
		else if (state == InputEvents::KeyState::KEY_UP) {
			setActionState(static_cast<ActionKey>(key), false);
			broadcastActionReleased(static_cast<ActionKey>(key));
		}
		});
}

void InputSystem::update(float delta_time)
{
}

void InputSystem::setWindow(Window* window)
{
	_window = window;
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

bool InputSystem::isActionPressed(const std::string& name) const
{
	assert(_actionStates.find(name) != _actionStates.end());
	return _actionStates.at(name);
}

void InputSystem::bindToActionPressed(const std::string& name, void* owner, const std::function<void()>& callback)
{
	assert(_actionPressed.find(name) != _actionPressed.end());
	auto& pressedEvent = _actionPressed.at(name);
	
	auto result = pressedEvent.emplace(owner, std::vector<std::function<void()>>{ callback });
	if (!result.second) {
		result.first->second.push_back(callback);
	}
}

void InputSystem::bindToActionReleased(const std::string& name, void* owner, const std::function<void()>& callback)
{
	assert(_actionReleased.find(name) != _actionReleased.end());
	auto& releasedEvent = _actionReleased.at(name);

	auto result = releasedEvent.emplace(owner, std::vector<std::function<void()>>{ callback });
	if (!result.second) {
		result.first->second.push_back(callback);
	}
}

void InputSystem::unbindAllActionPressed(const std::string& name, void* owner)
{
	assert(_actionPressed.find(name) != _actionPressed.end());
	auto& pressedEvent = _actionPressed.at(name);

	auto foundIt = pressedEvent.find(owner);
	if (foundIt != pressedEvent.end()) {
		pressedEvent.erase(foundIt);
	}
}

void InputSystem::unbindAllActionReleased(const std::string& name, void* owner)
{
	assert(_actionReleased.find(name) != _actionReleased.end());
	auto& releasedEvent = _actionReleased.at(name);

	auto foundIt = releasedEvent.find(owner);
	if (foundIt != releasedEvent.end()) {
		releasedEvent.erase(foundIt);
	}
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

void InputSystem::setActionState(ActionKey key, bool state)
{
	const std::string& action = _keysToActions[key];
	_actionStates[action] = state;
}

void InputSystem::broadcastActionPressed(ActionKey key)
{
	const std::string& action = _keysToActions[key];
	auto actionEvent = _actionPressed[action];

	for (auto& callbackGroup : actionEvent) {
		for (auto& callback : callbackGroup.second) {
			callback();
		}
	}
}

void InputSystem::broadcastActionReleased(ActionKey key)
{
	const std::string& action = _keysToActions[key];
	auto actionEvent = _actionReleased[action];

	for (auto& callbackGroup : actionEvent) {
		for (auto& callback : callbackGroup.second) {
			callback();
		}
	}
}
