#pragma once
#include "ICameraView.hpp"
#include <glm/mat4x4.hpp>

class MainCameraView : public ICameraView
{
private:
	Window* _window;
	glm::mat4 _viewMatrix;

public:
	MainCameraView();

	void init(Window* window) override;
	void render(const Model& model) override;
	void setViewMatrix(const glm::mat4& matrix) override;
};
