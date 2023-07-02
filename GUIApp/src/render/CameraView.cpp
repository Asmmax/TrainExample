#include "render/CameraView.hpp"
#include "render/CameraViewImpl.hpp"
#include "render/MainCameraViewImpl.hpp"
#include "common/Transform.hpp"

CameraView::CameraView(const std::shared_ptr<Transform>& transform):
	_slaveImpl(std::make_shared<CameraViewImpl>()),
	_mainImpl(std::make_shared<MainCameraViewImpl>()),
	_impl(_slaveImpl),
	_transform(transform)
{
}

void CameraView::init(Window* window)
{
	_mainImpl->init(window);
	_slaveImpl->init(window);
}

void CameraView::update()
{
	if (!_transform) {
		return;
	}

	auto viewMatrix = glm::inverse(_transform->getGlobalMatrix());
	_impl->setViewMatrix(viewMatrix);
}

void CameraView::render(const Model& model)
{
	_impl->render(model);
}

void CameraView::setSlave()
{
	_impl = _slaveImpl;
}

void CameraView::setMain()
{
	_impl = _mainImpl;
}
