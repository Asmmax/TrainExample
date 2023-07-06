#pragma once
#include "AComponent.hpp"
#include <glm/gtx/quaternion.hpp>
#include <memory>

class TransformComponent;

/// @serializable
class OrbitCameraManipulator : public ComponentCommon<OrbitCameraManipulator>
{
private:
	std::shared_ptr<TransformComponent> _eye;
	glm::quat _storagedRotation;
	float _sumDeltaX;
	float _sumDeltaY;

	float _rotSpeed;
	float _zoomSpeed;

public:
	OrbitCameraManipulator(float rotSpeed, float zoomSpeed);

	void init() override;
	void update(float deltaTime) override;

	/// @inject
	void setEye(const std::shared_ptr<TransformComponent>& eye);
};