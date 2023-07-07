#include "components/FlyCameraManipulator.hpp"
#include "render/components/CameraComponent.hpp"
#include "common/components/TransformComponent.hpp"
#include "common/Transform.hpp"
#include "input/InputSystem.hpp"
#include "render/components/CameraComponent.hpp"
#include "World.hpp"

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
}

void FlyCameraManipulator::update(float deltaTime)
{
}

void FlyCameraManipulator::rotate(float stepX, float stepY)
{
	auto transformComp = getOwner()->getComponent<TransformComponent>();

	std::shared_ptr<Transform> target = transformComp->getTransform();
	_eulerAngles.y = glm::mod(_eulerAngles.y - glm::radians(stepX * _rotSpeed), 2 * glm::pi<float>());
	_eulerAngles.x = glm::clamp(_eulerAngles.x - glm::radians(stepY * _rotSpeed), -0.5f * glm::pi<float>(), 0.5f * glm::pi<float>());

	target->setRotation(_eulerAngles);
}

void FlyCameraManipulator::move(const glm::vec3& direction)
{
	auto transformComp = getOwner()->getComponent<TransformComponent>();

	float speed = _speed;
	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (inputSystem && inputSystem->isActionPressed("SpeedUp")) {
		speed *= _speedUpCoef;
	}

	std::shared_ptr<Transform> target = transformComp->getTransform();
	auto position = target->getLocalPosition();
	transformComp->setPosition(position + speed *direction);
}

void FlyCameraManipulator::zoom(float step)
{
}

std::shared_ptr<Transform> FlyCameraManipulator::getTransform()
{
	auto transformComp = getOwner()->getComponent<TransformComponent>();
	if (!transformComp) {
		return nullptr;
	}
	return transformComp->getTransform();
}

void FlyCameraManipulator::apply()
{
	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (inputSystem) {
		inputSystem->setMouseCaptureMode(MouseCaptureMode::ENABLE);
	}

	auto camera = getOwner()->getComponent<CameraComponent>();
	if (camera) {
		camera->setMain();
	}
}
