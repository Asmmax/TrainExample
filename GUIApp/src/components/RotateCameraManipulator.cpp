#include "components/RotateCameraManipulator.hpp"
#include "render/components/CameraComponent.hpp"
#include "common/components/TransformComponent.hpp"
#include "common/Transform.hpp"
#include "input/InputSystem.hpp"
#include "World.hpp"

RotateCameraManipulator::RotateCameraManipulator(float rotSpeed) :
	_eulerAngles(),
	_rotSpeed(rotSpeed)
{
}

void RotateCameraManipulator::init()
{
	auto transformComp = getOwner()->getComponent<TransformComponent>();
	std::shared_ptr<Transform> target = transformComp->getTransform();
	_eulerAngles = target->getLocalEulerAngles();
}

void RotateCameraManipulator::update(float deltaTime)
{
}

void RotateCameraManipulator::rotate(float stepX, float stepY)
{
	auto transformComp = getOwner()->getComponent<TransformComponent>();

	std::shared_ptr<Transform> target = transformComp->getTransform();
	_eulerAngles.y = glm::mod(_eulerAngles.y - glm::radians(stepX * _rotSpeed), 2 * glm::pi<float>());
	_eulerAngles.x = glm::clamp(_eulerAngles.x - glm::radians(stepY * _rotSpeed), -0.5f * glm::pi<float>(), 0.5f * glm::pi<float>());

	target->setRotation(_eulerAngles);
}

void RotateCameraManipulator::move(const glm::vec3& direction)
{
}

void RotateCameraManipulator::zoom(float step)
{
}

std::shared_ptr<Transform> RotateCameraManipulator::getTransform()
{
	auto transformComp = getOwner()->getComponent<TransformComponent>();
	if (!transformComp) {
		return nullptr;
	}
	return transformComp->getTransform();
}

void RotateCameraManipulator::apply()
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
