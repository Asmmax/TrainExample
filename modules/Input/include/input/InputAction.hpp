#pragma once
#include <functional>
#include <memory>
#include <vector>

class InputDistributor;
class AInputActionImpl;
class EventListener;

class InputAction
{
private:
	using ImplPtr = std::shared_ptr<AInputActionImpl>;
	std::vector<ImplPtr> _impls;

public:
	InputAction(const std::vector<ImplPtr>& impls);

	void init(InputDistributor* distributor);
	bool isPressed() const;

	void bindToPressed(EventListener* owner, const std::function<void()>& callback);
	void bindToReleased(EventListener* owner, const std::function<void()>& callback);
	void unbindAllPressed(EventListener* owner);
	void unbindAllReleased(EventListener* owner);
};
