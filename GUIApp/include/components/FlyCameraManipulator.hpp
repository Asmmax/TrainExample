#pragma once
#include "AComponent.hpp"
#include <glm/glm.hpp>

class TransformComponent;

/// @serializable
class FlyCameraManipulator : public ComponentCommon<FlyCameraManipulator>
{
private:
	glm::vec3 _eulerAngles;

	float _rotSpeed;
	float _speed;
	float _speedUpCoef;

public:
	FlyCameraManipulator(float rotSpeed, float speed, float speedUpCoef);

	void init() override;
	void update(float deltaTime) override;
};