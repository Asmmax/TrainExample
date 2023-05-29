#include "MainCameraView.hpp"
#include "Window.hpp"

MainCameraView::MainCameraView():
	_window(nullptr),
	_viewMatrix()
{
}

void MainCameraView::init(Window* window)
{
	_window = window;
}

void MainCameraView::render(const Model& model)
{
	_window->setViewMatrix(_viewMatrix);

	_window->beginRender();
	_window->render(&model);
	_window->endRender();
}

void MainCameraView::setViewMatrix(const glm::mat4& matrix)
{
	_viewMatrix = matrix;
}
