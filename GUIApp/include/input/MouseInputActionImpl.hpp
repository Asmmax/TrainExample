#pragma once
#include "input/AInputActionImpl.hpp"

/// @serializable
enum class MouseActionKey : int
{
	LEFT_BUTTON,
	RIGHT_BUTTON,
	MIDDLE_BUTTON,
	UNDEFINED
};

/// @serializable @polymorphic
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
