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

void InputAxis::startFrame(float frameTime)
{
	for (auto& axisImpl : _impls) {
		axisImpl->startFrame(frameTime);
	}
}

void InputAxis::update(float deltaTime)
{
	for (auto& axisImpl : _impls) {
		axisImpl->update(deltaTime);
	}
}

void InputAxis::endFrame(float value)
{
	for (auto& axisImpl : _impls) {
		axisImpl->endFrame(value);
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

void InputAxis::resetMouse()
{
	for (auto& axisImpl : _impls) {
		axisImpl->resetMouse();
	}
}

void InputAxis::bindToChanged(EventListener* owner, const std::function<void(float)>& callback)
{
	for (auto& axisImpl : _impls) {
		axisImpl->bindToChanged(owner, callback);
	}
}

void InputAxis::unbindAllChanged(EventListener* owner)
{
	for (auto& axisImpl : _impls) {
		axisImpl->unbindAllChanged(owner);
	}
}
