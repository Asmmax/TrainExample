#pragma once
#include "input/AInputActionImpl.hpp"

enum class MouseActionKey : int
{
	LEFT_BUTTON,
	RIGHT_BUTTON,
	MIDDLE_BUTTON,
	UNDEFINED
};

class MouseInputActionImpl : public AInputActionImpl
{
private:
	bool _state;
	MouseActionKey _key;

public:
	MouseInputActionImpl(MouseActionKey key);

	void init(InputDistributor* distributor) override;
	bool isPressed() const override;
};
