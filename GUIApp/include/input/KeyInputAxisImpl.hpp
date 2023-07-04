#pragma once
#include "input/AInputAxisImpl.hpp"
#include <memory>

class InputAction;

/// @serializable @polymorphic
class KeyInputAxisImpl : public AInputAxisImpl
{
private:
	using InputActionPtr = std::shared_ptr<InputAction>;

	float _value;
	float _smooth;
	InputActionPtr _positiveAction;
	InputActionPtr _negativeAction;

public:
	KeyInputAxisImpl(const InputActionPtr& negativeAction, const InputActionPtr& positiveAction, float smooth);

	void init(InputDistributor* distributor) override;
	void update(float deltaTime) override;
	float getValue() const override;
};
