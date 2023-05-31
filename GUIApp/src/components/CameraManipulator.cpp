#include "components/CameraManipulator.hpp"
#include "components/CameraComponent.hpp"
#include "InputController.hpp"
#include "Transform.hpp"
#include "WorldContext.hpp"
#include "GameObject.hpp"

CameraManipulator::CameraManipulator() :
	_storagedRotation(1.0f, 0.0f, 0.0f ,0.0f),
	_sumDeltaX(0.0f),
	_sumDeltaY(0.0f)
{
}

void CameraManipulator::init()
{
	_input = WorldContext::getInstance().getInput();
	_storagedRotation = getOwner()->getTransform()->getLocalRotation();
}

void CameraManipulator::update(float delta_time)
{
	auto camera = getOwner()->getComponent<CameraComponent>();
	if (!camera) {
		return;
	}

	float deltaX = static_cast<float>(_input->GetXDelta());
	float deltaY = static_cast<float>(_input->GetYDelta());

	if (_input->isLeftButtonPressed()) {

		if (deltaX != 0.0f || deltaY != 0.0f) {

			_sumDeltaX += deltaX;
			_sumDeltaY += deltaY;

			std::shared_ptr<Transform> target = getOwner()->getTransform();

			auto rotY = glm::angleAxis(-glm::radians(_sumDeltaX), glm::vec3(0.0f, 1.0f, 0.0f));
			auto rotX = glm::angleAxis(-glm::radians(_sumDeltaY), glm::vec3(1.0f, 0.0f, 0.0f));

			target->setRotation(_storagedRotation * rotY * rotX);
		}
	}
	else {
		_sumDeltaX = 0.0f;
		_sumDeltaY = 0.0f;
		_storagedRotation = getOwner()->getTransform()->getLocalRotation();
	}

	double scale = _input->GetScrollDelta();

	std::shared_ptr<Transform> eye = camera->getTransform();

	auto position = eye->getLocalPosition();
	position.z *= static_cast<float>(scale);
	eye->setPosition(position);
}
