#pragma once
#include "components/AComponent.hpp"
#include <glm/gtx/quaternion.hpp>
#include <memory>

class InputController;

class CameraManipulator : public Component
{
private:
	std::shared_ptr<InputController> _input;
	glm::quat _storagedRotation;
	float _sumDeltaX;
	float _sumDeltaY;

public:
	CameraManipulator();

	void init() override;
	void update(float delta_time) override;
};