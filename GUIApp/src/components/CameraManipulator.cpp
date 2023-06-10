#include "components/CameraManipulator.hpp"
#include "render/components/CameraComponent.hpp"
#include "common/components/TransformComponent.hpp"
#include "common/Transform.hpp"
#include "input/InputSystem.hpp"
#include "World.hpp"

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
}

void CameraManipulator::update(float delta_time)
{
	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (!inputSystem) {
		return;
	}

	auto transformComp = getOwner()->getComponent<TransformComponent>();

	float deltaX = static_cast<float>(inputSystem->GetXDelta());
	float deltaY = static_cast<float>(inputSystem->GetYDelta());

	if (inputSystem->isLeftButtonPressed()) {

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

	double scale = inputSystem->GetScrollDelta();

	auto eyeTransform = _eye->getTransform();
	auto position = eyeTransform->getLocalPosition();
	position.z *= static_cast<float>(scale);
	eyeTransform->setPosition(position);
}

void CameraManipulator::setEye(const std::shared_ptr<TransformComponent>& eye)
{
	_eye = eye;
}
