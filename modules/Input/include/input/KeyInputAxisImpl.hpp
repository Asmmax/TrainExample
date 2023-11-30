#pragma once
#include "input/AInputAxisImpl.hpp"
#include <memory>

class InputAction;

class KeyInputAxisImpl : public AInputAxisImpl
{
private:
	using InputActionPtr = std::shared_ptr<InputAction>;

	InputActionPtr _positiveAction;
	InputActionPtr _negativeAction;

public:
	KeyInputAxisImpl(const InputActionPtr& negativeAction, const InputActionPtr& positiveAction, float smooth, float minSpeed);

	void init(InputDistributor* distributor) override;

protected:
	float getRawValue(float frameTime) const override;
};
