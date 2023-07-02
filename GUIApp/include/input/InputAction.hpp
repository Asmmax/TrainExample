#pragma once
#include <functional>
#include <memory>
#include <vector>

class InputDistributor;
class AInputActionImpl;

/// @serializable @polymorphic
class InputAction
{
private:
	using ImplPtr = std::shared_ptr<AInputActionImpl>;
	std::vector<ImplPtr> _impls;

public:
	InputAction(const std::vector<ImplPtr>& impls);

	void init(InputDistributor* distributor);
	bool isPressed() const;

	void bindToPressed(void* owner, const std::function<void()>& callback);
	void bindToReleased(void* owner, const std::function<void()>& callback);
	void unbindAllPressed(void* owner);
	void unbindAllReleased(void* owner);
};
