#pragma once
#include "ICameraView.hpp"
#include <glm/mat4x4.hpp>

class MainCameraViewImpl : public ICameraView
{
private:
	Window* _window;
	glm::mat4 _viewMatrix;

public:
	MainCameraViewImpl();

	void init(Window* window) override;
	void render(const Model& model) override;
	void setViewMatrix(const glm::mat4& matrix) override;
};
