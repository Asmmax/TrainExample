#include "CameraView.hpp"
#include "Window.hpp"
#include "View.hpp"

CameraView::CameraView(int width, int height):
	_fboTexture(nullptr),
	_view(nullptr),
	_width(width),
	_height(height)
{
}

void CameraView::resize(int width, int height)
{
	if (_width == width && _height == height) {
		return;
	}

	_width = width;
	_height = height;
	_view->setSize(_width, _height);
}

void CameraView::init(Window* window)
{
	Loader* loader = window->getLoader();
	_fboTexture = loader->createTexture(_width, _height);
	_view = window->creteView(_fboTexture);
}

void CameraView::render(const Model& model)
{
	_view->render(&model);
}

void CameraView::setViewMatrix(const glm::mat4& matrix)
{
	_view->setMatrix(matrix);
}
