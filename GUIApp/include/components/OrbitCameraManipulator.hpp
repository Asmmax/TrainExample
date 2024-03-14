#pragma once
#include "ComponentCommon.hpp"
#include "components/ICameraManipulator.hpp"
#include <glm/gtx/quaternion.hpp>
#include <memory>

class TransformComponent;

class OrbitCameraManipulator : public ComponentCommon<OrbitCameraManipulator>, public ICameraManipulator
{
private:
	TransformComponent* _eye;
	glm::quat _storagedRotation;
	float _sumDeltaX;
	float _sumDeltaY;

	float _rotSpeed;
	float _zoomSpeed;
	bool _supportActive;

public:
	OrbitCameraManipulator(float rotSpeed, float zoomSpeed);

	void setEye(TransformComponent* eye);

	void init() override;
	void update(float deltaTime) override;

	void rotate(float stepX, float stepY) override;
	void move(const glm::vec3& direction) override;
	void zoom(float step) override;
	std::shared_ptr<Transform> getTransform() override;

	void apply() override;

protected:
	void startSupport();
	void stopSupport();
};