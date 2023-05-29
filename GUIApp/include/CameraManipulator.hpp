#pragma once
#include "APlayerController.hpp"
#include <memory>

class Camera;

class CameraManipulator : public APlayerController
{
private:
	std::shared_ptr<Camera> _camera;
	std::shared_ptr<InputController> _input;

public:
	CameraManipulator(const std::shared_ptr<Camera>& camera);

	void init(const std::shared_ptr<InputController>& input) override;
	void update(float deltaTime) override;
};