#include "input/KeyInputAxisImpl.hpp"
#include "input/InputAction.hpp"

KeyInputAxisImpl::KeyInputAxisImpl(const InputActionPtr& negativeAction, const InputActionPtr& positiveAction, float smooth, float minSpeed):
	AInputAxisImpl(smooth, minSpeed),
	_negativeAction(negativeAction),
	_positiveAction(positiveAction)
{
}

void KeyInputAxisImpl::init(InputDistributor* distributor)
{
	_negativeAction->init(distributor);
	_positiveAction->init(distributor);
}

float KeyInputAxisImpl::getRawValue(float frameTime) const
{
	float rawValue = 0.f;
	if (_negativeAction->isPressed()) {
		rawValue -= 1.0f;
	}
	if (_positiveAction->isPressed()) {
		rawValue += 1.0f;
	}
	return rawValue;
}
