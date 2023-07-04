#include "input/InputAxis.hpp"
#include "input/AInputAxisImpl.hpp"

InputAxis::InputAxis(const std::vector<ImplPtr>& impls):
	_impls(impls)
{
}

void InputAxis::init(InputDistributor* distributor)
{
	for (auto& axisImpl : _impls) {
		axisImpl->init(distributor);
	}
}

void InputAxis::update(float deltaTime)
{
	for (auto& axisImpl : _impls) {
		axisImpl->update(deltaTime);
	}
}

void InputAxis::fixedUpdate(float deltaTime)
{
	for (auto& axisImpl : _impls) {
		axisImpl->fixedUpdate(deltaTime);
	}
}

float InputAxis::getValue() const
{
	float avgValue = 0.f;
	for (auto& axisImpl : _impls) {
		avgValue += axisImpl->getValue();
	}
	avgValue /= _impls.size();
	return avgValue;
}
