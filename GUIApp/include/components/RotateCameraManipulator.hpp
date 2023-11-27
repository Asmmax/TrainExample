#pragma once
#include "ComponentCommon.hpp"
#include "components/ICameraManipulator.hpp"
#include <glm/glm.hpp>

class RotateCameraManipulator : public ComponentCommon<RotateCameraManipulator>, public ICameraManipulator
{
private:
	glm::vec3 _eulerAngles;

	float _rotSpeed;

public:
	RotateCameraManipulator(float rotSpeed);

	void init() override;
	void update(float deltaTime) override;

	void rotate(float stepX, float stepY) override;
	void move(const glm::vec3& direction) override;
	void zoom(float step) override;
	std::shared_ptr<Transform> getTransform() override;

	void apply() override;
};
