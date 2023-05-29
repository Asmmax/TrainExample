#include "CameraManipulator.hpp"
#include "Camera.hpp"
#include "InputController.hpp"
#include "Transform.hpp"
#include <iostream>

CameraManipulator::CameraManipulator(const std::shared_ptr<Camera>& camera) :
	_camera(camera),
	_input(nullptr),
	_storagedRotation(1.0f, 0.0f, 0.0f ,0.0f),
	_sumDeltaX(0.0f),
	_sumDeltaY(0.0f)
{
}

void CameraManipulator::init(const std::shared_ptr<InputController>& input)
{
	_input = input;
	_storagedRotation = _camera->getTransform()->getLocalRotation();
}

void CameraManipulator::update(float deltaTime)
{
	float deltaX = static_cast<float>(_input->GetXDelta());
	float deltaY = static_cast<float>(_input->GetYDelta());

	if (_input->isLeftButtonPressed()) {

		if (deltaX != 0.0f || deltaY != 0.0f) {

			_sumDeltaX += deltaX;
			_sumDeltaY += deltaY;

			std::shared_ptr<Transform> target = _camera->getTransform();

			auto rotY = glm::angleAxis(-glm::radians(_sumDeltaX), glm::vec3(0.0f, 1.0f, 0.0f));
			auto rotX = glm::angleAxis(-glm::radians(_sumDeltaY), glm::vec3(1.0f, 0.0f, 0.0f));

			target->setRotation(_storagedRotation * rotY * rotX);
		}
	}
	else {
		_sumDeltaX = 0.0f;
		_sumDeltaY = 0.0f;
		_storagedRotation = _camera->getTransform()->getLocalRotation();
	}

	double scale = _input->GetScrollDelta();

	std::shared_ptr<Transform> eye = _camera->getEye();

	auto position = eye->getLocalPosition();
	position.z *= static_cast<float>(scale);
	eye->setPosition(position);
}
