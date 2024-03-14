#include "components/OrbitCameraManipulator.hpp"
#include "render/components/CameraComponent.hpp"
#include "common/components/TransformComponent.hpp"
#include "common/Transform.hpp"
#include "input/InputSystem.hpp"
#include "render/components/CameraComponent.hpp"
#include "World.hpp"
#include <glm/glm.hpp>

OrbitCameraManipulator::OrbitCameraManipulator(float rotSpeed, float zoomSpeed) :
    _eye(nullptr),
	_storagedRotation(1.0f, 0.0f, 0.0f ,0.0f),
	_sumDeltaX(0.0f),
	_sumDeltaY(0.0f),
    _rotSpeed(rotSpeed),
    _zoomSpeed(zoomSpeed),
    _supportActive(false)
{
}

void OrbitCameraManipulator::setEye(TransformComponent* eye)
{
    _eye = eye;
}

void OrbitCameraManipulator::init()
{
	auto transformComp = getOwner()->getComponent<TransformComponent>();
	_storagedRotation = transformComp->getTransform()->getLocalRotation();

    auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
    if (!inputSystem) {
        return;
    }
    inputSystem->bindToActionPressed("MouseSupport", this, [this]() {startSupport(); });
    inputSystem->bindToActionReleased("MouseSupport", this, [this]() {stopSupport(); });
}

void OrbitCameraManipulator::update(float deltaTime)
{
}

void OrbitCameraManipulator::rotate(float stepX, float stepY)
{
    if (!_supportActive) {
        return;
    }

    _sumDeltaX += stepX * _rotSpeed;
    _sumDeltaY += stepY * _rotSpeed;

    auto transformComp = getOwner()->getComponent<TransformComponent>();
    std::shared_ptr<Transform> target = transformComp->getTransform();

    auto rotY = glm::angleAxis(-glm::radians(_sumDeltaX), glm::vec3(0.0f, 1.0f, 0.0f));
    auto rotX = glm::angleAxis(-glm::radians(_sumDeltaY), glm::vec3(1.0f, 0.0f, 0.0f));

    target->setRotation(_storagedRotation * rotY * rotX);
}

void OrbitCameraManipulator::move(const glm::vec3& direction)
{
}

void OrbitCameraManipulator::zoom(float step)
{
    const float scale = glm::pow(1.2f, -step * _zoomSpeed);

    auto eyeTransform = _eye->getTransform();
    auto position = eyeTransform->getLocalPosition();
    position.z *= scale;
    eyeTransform->setPosition(position);
}

std::shared_ptr<Transform> OrbitCameraManipulator::getTransform()
{
    auto transformComp = getOwner()->getComponent<TransformComponent>();
    if (!transformComp) {
        return nullptr;
    }
    return transformComp->getTransform();
}

void OrbitCameraManipulator::apply()
{
    auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
    if (inputSystem) {
        inputSystem->setMouseCaptureMode(MouseCaptureMode::WHILE_MOUSE_PRESSED);
    }

    auto camera = _eye->getOwner()->getComponent<CameraComponent>();
    if (camera) {
        camera->setMain();
    }
}

void OrbitCameraManipulator::startSupport()
{
    _supportActive = true;
}

void OrbitCameraManipulator::stopSupport()
{
    _supportActive = false;
    _sumDeltaX = 0.0f;
    _sumDeltaY = 0.0f;
    auto transformComp = getOwner()->getComponent<TransformComponent>();
    _storagedRotation = transformComp->getTransform()->getLocalRotation();
}
