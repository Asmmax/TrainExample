#include "input/KeyboardInputActionImpl.hpp"
#include "input/InputDistributor.hpp"

KeyboardInputActionImpl::KeyboardInputActionImpl(InputActionKey key):
	_state(false),
	_key(key)
{
}

void KeyboardInputActionImpl::init(InputDistributor* distributor)
{
	distributor->addKeyCallback([this](InputEvents::KeyboardKey key, InputEvents::KeyState state, InputEvents::KeyMod mod) {
		if (static_cast<InputActionKey>(key) != _key) {
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

bool KeyboardInputActionImpl::isPressed() const
{
	return _state;
}
