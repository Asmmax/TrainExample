#include "components/OrbitCameraManipulator.hpp"
#include "render/components/CameraComponent.hpp"
#include "common/components/TransformComponent.hpp"
#include "common/Transform.hpp"
#include "input/InputSystem.hpp"
#include "World.hpp"
#include <glm/glm.hpp>

OrbitCameraManipulator::OrbitCameraManipulator(float rotSpeed, float zoomSpeed) :
	_storagedRotation(1.0f, 0.0f, 0.0f ,0.0f),
	_sumDeltaX(0.0f),
	_sumDeltaY(0.0f),
    _rotSpeed(rotSpeed),
    _zoomSpeed(zoomSpeed)
{
}

void OrbitCameraManipulator::init()
{
	auto transformComp = getOwner()->getComponent<TransformComponent>();
	_storagedRotation = transformComp->getTransform()->getLocalRotation();

	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (inputSystem) {
		inputSystem->setMouseCaptureMode(MouseCaptureMode::WHILE_MOUSE_PRESSED);
	}
}

void OrbitCameraManipulator::update(float deltaTime)
{
    auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
    if (!inputSystem) {
        return;
    }

    auto transformComp = getOwner()->getComponent<TransformComponent>();

    if (inputSystem->isActionPressed("MouseSupport")) {

        const float deltaX = inputSystem->getAxisValue("MouseX");
        const float deltaY = inputSystem->getAxisValue("MouseY");

        if (deltaX != 0.0f || deltaY != 0.0f) {
            const float rotStep = _rotSpeed * deltaTime;
            _sumDeltaX += deltaX * rotStep;
            _sumDeltaY += deltaY * rotStep;

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

    const float deltaZoom = inputSystem->getAxisValue("Zoom");
    const float zoomStep = _zoomSpeed * deltaTime;
    const float scale = glm::pow(1.2f, -deltaZoom * zoomStep);

    auto eyeTransform = _eye->getTransform();
    auto position = eyeTransform->getLocalPosition();
    position.z *= scale;
    eyeTransform->setPosition(position);
}

void OrbitCameraManipulator::setEye(const std::shared_ptr<TransformComponent>& eye)
{
	_eye = eye;
}
