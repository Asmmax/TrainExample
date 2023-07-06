#include "components/FlyCameraManipulator.hpp"
#include "render/components/CameraComponent.hpp"
#include "common/components/TransformComponent.hpp"
#include "common/Transform.hpp"
#include "input/InputSystem.hpp"
#include "World.hpp"
#include <glm/glm.hpp>

FlyCameraManipulator::FlyCameraManipulator(float rotSpeed, float speed, float speedUpCoef):
	_eulerAngles(),
	_rotSpeed(rotSpeed),
	_speed(speed),
	_speedUpCoef(speedUpCoef)
{
}

void FlyCameraManipulator::init()
{
	auto transformComp = getOwner()->getComponent<TransformComponent>();
	std::shared_ptr<Transform> target = transformComp->getTransform();
	_eulerAngles = target->getLocalEulerAngles();

	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (inputSystem) {
		inputSystem->setMouseCaptureMode(MouseCaptureMode::ENABLE);
	}
}

void FlyCameraManipulator::update(float deltaTime)
{
	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (!inputSystem) {
		return;
	}

	auto transformComp = getOwner()->getComponent<TransformComponent>();

	const float deltaX = inputSystem->getAxisValue("MouseX");
	const float deltaY = inputSystem->getAxisValue("MouseY");

	if (deltaX != 0.0f || deltaY != 0.0f) {
		const float rotStep = _rotSpeed * deltaTime;
		std::shared_ptr<Transform> target = transformComp->getTransform();
		_eulerAngles.y = glm::mod(_eulerAngles.y - glm::radians(deltaX * rotStep), 2 * glm::pi<float>());
		_eulerAngles.x = glm::clamp(_eulerAngles.x - glm::radians(deltaY * rotStep), -0.5f * glm::pi<float>(), 0.5f * glm::pi<float>());

		target->setRotation(_eulerAngles);
	}

	const float horizontal = inputSystem->getAxisValue("Horizontal");
	const float vertical = inputSystem->getAxisValue("Vertical");

	if (horizontal != 0.0f || vertical != 0.0f) {
		float step = _speed * deltaTime;
		if (inputSystem->isActionPressed("SpeedUp")) {
			step *= _speedUpCoef;
		}

		std::shared_ptr<Transform> target = transformComp->getTransform();
		auto position = target->getLocalPosition();
		auto forward = target->getLocalForward();
		auto right = target->getLocalRight();

		auto direction = forward * vertical + right * horizontal;
		transformComp->setPosition(position + direction * step);
	}
}
