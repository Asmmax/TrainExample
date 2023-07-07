#include "components/PlayerController.hpp"
#include "components/ICameraManipulator.hpp"
#include "input/InputSystem.hpp"
#include "common/Transform.hpp"
#include "World.hpp"

PlayerController::PlayerController(const std::vector<ManipulatorPtr>& manipulators) :
	_manipulators(manipulators)
{
	assert(!_manipulators.empty());
	_target = _manipulators.front();
}

void PlayerController::init()
{
	_target->apply();

	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (!inputSystem) {
		return;
	}
	inputSystem->bindToActionPressed("SwitchManipulator", this, [this]() {switchManipulator(); });
}

void PlayerController::update(float deltaTime)
{
	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (!inputSystem) {
		return;
	}

	const float deltaX = inputSystem->getAxisValue("MouseX");
	const float deltaY = inputSystem->getAxisValue("MouseY");

	if (deltaX != 0.0f || deltaY != 0.0f) {
		_target->rotate(deltaX * deltaTime, deltaY * deltaTime);
	}

	const float horizontal = inputSystem->getAxisValue("Horizontal");
	const float vertical = inputSystem->getAxisValue("Vertical");

	if (horizontal != 0.0f || vertical != 0.0f) {

		std::shared_ptr<Transform> targetTransform = _target->getTransform();
		auto forward = targetTransform->getLocalForward();
		auto right = targetTransform->getLocalRight();

		auto direction = forward * vertical + right * horizontal;
		_target->move(direction * deltaTime);
	}

	const float deltaZoom = inputSystem->getAxisValue("Zoom");
	if (deltaZoom != 0.0f) {
		_target->zoom(deltaZoom * deltaTime);
	}
}

void PlayerController::switchManipulator()
{
	auto foundIt = std::find(_manipulators.begin(), _manipulators.end(), _target);
	foundIt++;
	if (foundIt == _manipulators.end()) {
		_target = _manipulators.front();
	}
	else {
		_target = *foundIt;
	}

	_target->apply();
}
