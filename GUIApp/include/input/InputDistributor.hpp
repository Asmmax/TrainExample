#pragma once
#include "InputEvents.hpp"
#include <vector>

class Window;

class InputDistributor
{
private:
	using VoidCallback = std::function<void()>;

	std::vector<InputEvents::MouseButtonCallback> _mouseButtonCallbacks;
	std::vector<InputEvents::MouseButtonWithMoveCallback> _mouseButtonWithMoveCallbacks;
	std::vector<InputEvents::MouseMoveCallback> _mouseMoveCallbacks;
	std::vector<InputEvents::MouseScrollCallback> _mouseScrollCallbacks;
	std::vector<InputEvents::KeyCallback> _keyCallbacks;
	std::vector<VoidCallback> _preHandleCallbacks;

public:
	void bindAllTo(Window* window);

	void addPreHandleCallback(const VoidCallback& callback);
	void addMouseButtonCallback(const InputEvents::MouseButtonCallback& callback);
	void addMouseButtonWithMoveCallback(const InputEvents::MouseButtonWithMoveCallback& callback);
	void addMouseMoveCallback(const InputEvents::MouseMoveCallback& callback);
	void addMouseScrollCallback(const InputEvents::MouseScrollCallback& callback);
	void addKeyCallback(const InputEvents::KeyCallback& callback);
};
