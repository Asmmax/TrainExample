#include "render/MainCameraViewImpl.hpp"
#include "Window.hpp"

MainCameraViewImpl::MainCameraViewImpl():
	_window(nullptr),
	_viewMatrix()
{
}

void MainCameraViewImpl::init(Window* window)
{
	_window = window;
}

void MainCameraViewImpl::deinit(Window* window)
{
}

void MainCameraViewImpl::render(const Model& model)
{
	_window->setViewMatrix(_viewMatrix);

	_window->prepareRender();
	_window->render(&model);
}

void MainCameraViewImpl::setViewMatrix(const glm::mat4& matrix)
{
	_viewMatrix = matrix;
}
