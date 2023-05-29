#include "CameraManipulator.hpp"
#include "Camera.hpp"
#include "InputController.hpp"
#include "Transform.hpp"
#include <iostream>

CameraManipulator::CameraManipulator(const std::shared_ptr<Camera>& camera) :
	_camera(camera),
	_input(nullptr)
{
}

void CameraManipulator::init(const std::shared_ptr<InputController>& input)
{
	_input = input;
}

void CameraManipulator::update(float deltaTime)
{
	float deltaX = static_cast<float>(_input->GetXDelta());
	float deltaY = static_cast<float>(_input->GetYDelta());

	if (_input->isLeftButtonPressed() && (deltaX != 0.0f || deltaY != 0.0f)) {

		std::shared_ptr<Transform> target = _camera->getTransform();

		auto rotatation = target->getLocalRotation();

		auto rotY = glm::angleAxis(-glm::radians(deltaX), glm::vec3(0.0f, 1.0f, 0.0f));
		auto rotX = glm::angleAxis(-glm::radians(deltaY), glm::vec3(1.0f, 0.0f, 0.0f));

		rotatation *= rotX * rotY;

		target->setRotation(rotatation);
	}

	double scale = _input->GetScrollDelta();

	std::shared_ptr<Transform> eye = _camera->getEye();

	auto position = eye->getLocalPosition();
	position.z *= static_cast<float>(scale);
	eye->setPosition(position);
}
