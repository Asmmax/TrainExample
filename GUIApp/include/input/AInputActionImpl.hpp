#pragma once
#include <functional>
#include <unordered_map>
#include <vector>

class InputDistributor;

/// @serializable @polymorphic @abstract
class AInputActionImpl
{
private:
	using ActionEvent = std::unordered_map<void*, std::vector<std::function<void()>>>;
	ActionEvent _actionPressed;
	ActionEvent _actionReleased;

public:
	virtual void init(InputDistributor* distributor) = 0;
	virtual bool isPressed() const = 0;

	void bindToPressed(void* owner, const std::function<void()>& callback);
	void bindToReleased(void* owner, const std::function<void()>& callback);
	void unbindAllPressed(void* owner);
	void unbindAllReleased(void* owner);

protected:
	void broadcastPressed();
	void broadcastReleased();
};
