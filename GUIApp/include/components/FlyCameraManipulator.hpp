#pragma once
#include "components/RotateCameraManipulator.hpp"
#include "components/ICameraManipulator.hpp"
#include <glm/glm.hpp>

/// @serializable
class FlyCameraManipulator : public RotateCameraManipulator
{
private:
	float _speed;
	float _speedUpCoef;

public:
	FlyCameraManipulator(float rotSpeed, float speed, float speedUpCoef);

	void move(const glm::vec3& direction) override;
};
