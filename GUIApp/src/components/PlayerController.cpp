#include "components/PlayerController.hpp"
#include "components/ICameraManipulator.hpp"
#include "systems/PlayerManager.hpp"
#include "input/InputSystem.hpp"
#include "common/Transform.hpp"
#include "World.hpp"

PlayerController::PlayerController():
	_target(nullptr),
	_isInited(false)
{
}

void PlayerController::setManipulator(ManipulatorPtr target)
{
	_target = target;
	if (_isInited) {
		_target->apply();
	}
}

void PlayerController::init()
{
	auto playerManager = getOwner()->getWorld()->getSystem<PlayerManager>();
	if (playerManager) {
		playerManager->setCurrentController(getOwner()->getComponent<PlayerController>());
	}
	if (_target) {
		_target->apply();
	}
	_isInited = true;
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
