#pragma once
#include "AComponent.hpp"
#include "components/ICameraManipulator.hpp"
#include <glm/glm.hpp>

/// @serializable
class FlyCameraManipulator : public ComponentCommon<FlyCameraManipulator>, public ICameraManipulator
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

	void rotate(float stepX, float stepY) override;
	void move(const glm::vec3& direction) override;
	void zoom(float step) override;
	std::shared_ptr<Transform> getTransform() override;

	void apply() override;
};