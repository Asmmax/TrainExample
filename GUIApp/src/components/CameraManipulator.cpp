#include "components/CameraManipulator.hpp"
#include "render/components/CameraComponent.hpp"
#include "common/components/TransformComponent.hpp"
#include "common/Transform.hpp"
#include "input/InputSystem.hpp"
#include "World.hpp"
#include <glm/glm.hpp>

CameraManipulator::CameraManipulator() :
	_storagedRotation(1.0f, 0.0f, 0.0f ,0.0f),
	_sumDeltaX(0.0f),
	_sumDeltaY(0.0f)
{
}

void CameraManipulator::init()
{
	auto transformComp = getOwner()->getComponent<TransformComponent>();
	_storagedRotation = transformComp->getTransform()->getLocalRotation();

	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (inputSystem) {
		inputSystem->setMouseCaptureMode(MouseCaptureMode::WHILE_MOUSE_PRESSED);
	}
}

void CameraManipulator::update(float delta_time)
{
	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (!inputSystem) {
		return;
	}

	auto transformComp = getOwner()->getComponent<TransformComponent>();

	float deltaX = inputSystem->getAxisValue("MouseX") * 200.0f * delta_time;
	float deltaY = inputSystem->getAxisValue("MouseY") * 200.0f * delta_time;

	if (inputSystem->isActionPressed("MouseSupport")) {

		if (deltaX != 0.0f || deltaY != 0.0f) {

			_sumDeltaX += deltaX;
			_sumDeltaY += deltaY;

			std::shared_ptr<Transform> target = transformComp->getTransform();

			auto rotY = glm::angleAxis(-glm::radians(_sumDeltaX), glm::vec3(0.0f, 1.0f, 0.0f));
			auto rotX = glm::angleAxis(-glm::radians(_sumDeltaY), glm::vec3(1.0f, 0.0f, 0.0f));

			target->setRotation(_storagedRotation * rotY * rotX);
		}
	}
	else {
		_sumDeltaX = 0.0f;
		_sumDeltaY = 0.0f;
		_storagedRotation = transformComp->getTransform()->getLocalRotation();
	}

	float scale = glm::pow(1.2f, -20.0f*inputSystem->getAxisValue("Zoom") * delta_time);

	auto eyeTransform = _eye->getTransform();
	auto position = eyeTransform->getLocalPosition();
	position.z *= scale;
	eyeTransform->setPosition(position);
}

void CameraManipulator::setEye(const std::shared_ptr<TransformComponent>& eye)
{
	_eye = eye;
}
