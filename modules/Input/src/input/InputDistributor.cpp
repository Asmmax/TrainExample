#include "input/InputDistributor.hpp"
#include "Window.hpp"

void InputDistributor::bindAllTo(Window* window)
{
	window->setPreHandleCallback([this]() {
		for (auto& callback : _preHandleCallbacks) {
			callback();
		}
		});
	window->setMouseButtonCallback([this](InputEvents::MouseKey key, InputEvents::KeyState state) {
		for (auto& callback : _mouseButtonCallbacks) {
			callback(key, state);
		}
		});
	window->setMouseButtonWithMoveCallback([this](double x, double y, InputEvents::MouseKey key, InputEvents::KeyState state) {
		for (auto& callback : _mouseButtonWithMoveCallbacks) {
			callback(x, y, key, state);
		}
		});
	window->setMouseMoveCallback([this](double x, double y) {
		for (auto& callback : _mouseMoveCallbacks) {
			callback(x, y);
		}
		});
	window->setMouseScrollCallback([this](double step) {
		for (auto& callback : _mouseScrollCallbacks) {
			callback(step);
		}
		});
	window->setKeyCallback([this](InputEvents::KeyboardKey key, InputEvents::KeyState state, InputEvents::KeyMod mod) {
		for (auto& callback : _keyCallbacks) {
			callback(key, state, mod);
		}
		});
}

void InputDistributor::addPreHandleCallback(const VoidCallback& callback)
{
	_preHandleCallbacks.push_back(callback);
}

void InputDistributor::addMouseButtonCallback(const InputEvents::MouseButtonCallback& callback)
{
	_mouseButtonCallbacks.push_back(callback);
}

void InputDistributor::addMouseButtonWithMoveCallback(const InputEvents::MouseButtonWithMoveCallback& callback)
{
	_mouseButtonWithMoveCallbacks.push_back(callback);
}

void InputDistributor::addMouseMoveCallback(const InputEvents::MouseMoveCallback& callback)
{
	_mouseMoveCallbacks.push_back(callback);
}

void InputDistributor::addMouseScrollCallback(const InputEvents::MouseScrollCallback& callback)
{
	_mouseScrollCallbacks.push_back(callback);
}

void InputDistributor::addKeyCallback(const InputEvents::KeyCallback& callback)
{
	_keyCallbacks.push_back(callback);
}
