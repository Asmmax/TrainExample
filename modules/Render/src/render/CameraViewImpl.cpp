#include "render/CameraViewImpl.hpp"
#include "Window.hpp"
#include "View.hpp"

CameraViewImpl::CameraViewImpl():
	_fboTexture(nullptr),
	_view(nullptr),
	_width(1),
	_height(1)
{
}

void CameraViewImpl::resize(int width, int height)
{
	if (_width == width && _height == height) {
		return;
	}

	_width = width;
	_height = height;
	if (_view) {
		_view->setSize(_width, _height);
	}
}

void CameraViewImpl::init(Window* window)
{
	Loader* loader = window->getLoader();
	_fboTexture = loader->createTexture(_width, _height);
	_view = window->creteView(_fboTexture);
}

void CameraViewImpl::deinit(Window* window)
{
	window->releaseView(_view);
	Loader* loader = window->getLoader();
	loader->release(_fboTexture);
}

void CameraViewImpl::render(const Model& model)
{
	_view->render(&model);
}

void CameraViewImpl::setViewMatrix(const glm::mat4& matrix)
{
	_view->setMatrix(matrix);
}
