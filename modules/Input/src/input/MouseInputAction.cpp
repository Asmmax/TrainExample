#include "input/MouseInputActionImpl.hpp"
#include "input/InputDistributor.hpp"

MouseInputActionImpl::MouseInputActionImpl(MouseActionKey key) :
	_state(false),
	_key(key)
{
}

void MouseInputActionImpl::init(InputDistributor* distributor)
{
	distributor->addMouseButtonCallback([this](InputEvents::MouseKey key, InputEvents::KeyState state) {
		if (static_cast<MouseActionKey>(key) != _key) {
			return;
		}

		if (state == InputEvents::KeyState::KEY_DOWN) {
			_state = true;
			_actionPressed.broadcast();
		}
		else if (state == InputEvents::KeyState::KEY_UP) {
			_state = false;
			_actionReleased.broadcast();
		}
		});
}

bool MouseInputActionImpl::isPressed() const
{
	return _state;
}
