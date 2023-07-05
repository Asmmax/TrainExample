#include "input/InputAction.hpp"
#include "input/AInputActionImpl.hpp"

InputAction::InputAction(const std::vector<ImplPtr>& impls) :
	_impls(impls)
{
}

void InputAction::init(InputDistributor* distributor)
{
	for (auto& actionImpl : _impls) {
		actionImpl->init(distributor);
	}
}

bool InputAction::isPressed() const
{
	for (auto& actionImpl : _impls) {
		if (actionImpl->isPressed()) {
			return true;
		}
	}
	return false;
}

void InputAction::bindToPressed(EventListener* owner, const std::function<void()>& callback)
{
	for (auto& actionImpl : _impls) {
		actionImpl->bindToPressed(owner, callback);
	}
}

void InputAction::bindToReleased(EventListener* owner, const std::function<void()>& callback)
{
	for (auto& actionImpl : _impls) {
		actionImpl->bindToReleased(owner, callback);
	}
}

void InputAction::unbindAllPressed(EventListener* owner)
{
	for (auto& actionImpl : _impls) {
		actionImpl->unbindAllPressed(owner);
	}
}

void InputAction::unbindAllReleased(EventListener* owner)
{
	for (auto& actionImpl : _impls) {
		actionImpl->unbindAllReleased(owner);
	}
}
