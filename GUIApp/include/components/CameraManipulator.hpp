#pragma once
#include "AComponent.hpp"
#include <glm/gtx/quaternion.hpp>
#include <memory>

class TransformComponent;

/// @serializable
class CameraManipulator : public ComponentCommon<CameraManipulator>
{
private:
	std::shared_ptr<TransformComponent> _eye;
	glm::quat _storagedRotation;
	float _sumDeltaX;
	float _sumDeltaY;

public:
	CameraManipulator();

	void init() override;
	void update(float delta_time) override;

	/// @inject
	void setEye(const std::shared_ptr<TransformComponent>& eye);
};