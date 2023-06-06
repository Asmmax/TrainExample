#pragma once
#include "AComponent.hpp"
#include <glm/gtx/quaternion.hpp>
#include <memory>

class CameraManipulator : public Component
{
private:
	std::shared_ptr<GameObject> _eye;
	glm::quat _storagedRotation;
	float _sumDeltaX;
	float _sumDeltaY;

public:
	CameraManipulator();

	void init() override;
	void update(float delta_time) override;

	void setEye(const std::shared_ptr<GameObject>& eye);
};