#pragma once
#include "ASystem.hpp"
#include <vector>
#include <unordered_map>
#include <functional>

class InputAction;
class InputAxis;
class InputDistributor;
class Window;
class EventListener;

enum class MouseCaptureMode
{
	DISABLE,
	ENABLE,
	WHILE_MOUSE_PRESSED
};

/// @serializable
struct InputActionEntry
{
	std::string name;
	std::shared_ptr<InputAction> action;
};

/// @serializable
struct InputAxisEntry
{
	std::string name;
	std::shared_ptr<InputAxis> axis;
};

/// @serializable
class InputSystem : public SystemCommon<InputSystem>
{
private:
	using InputActionPtr = std::shared_ptr<InputAction>;
	using InputAxisPtr = std::shared_ptr<InputAxis>;

	Window* _window;

	bool _needMouseCaptureWhileMousePressed;
	float _fixedTime;
	float _timeRedutant;

	std::shared_ptr<InputDistributor> _distributor;
	std::unordered_map<std::string, InputActionPtr> _actions;
	std::unordered_map<std::string, InputAxisPtr> _axes;
	std::vector<bool> _mousePressed;

public:
	explicit InputSystem(const std::vector<InputActionEntry>& actions, const std::vector<InputAxisEntry>& axes, float fixedTime);

	void init() override;
	void update(float delta_time) override;

	void setWindow(Window* window) override;

	void setMouseCaptureMode(MouseCaptureMode mode);

	float getAxisValue(const std::string& name) const;
	void bindToAxisChanged(const std::string& name, EventListener* owner, const std::function<void(float)>& callback);
	void unbindAllAxisChanged(const std::string& name, EventListener* owner);

	bool isActionPressed(const std::string& name) const;
	void bindToActionPressed(const std::string& name, EventListener* owner, const std::function<void()>& callback);
	void bindToActionReleased(const std::string& name, EventListener* owner, const std::function<void()>& callback);
	void unbindAllActionPressed(const std::string& name, EventListener* owner);
	void unbindAllActionReleased(const std::string& name, EventListener* owner);

protected:
	void fixedUpdate();
	void markMousePressed(size_t keyId, bool isPressed);
	bool anyMousePressed();
};
