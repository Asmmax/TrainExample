#include "Camera.hpp"
#include "Transform.hpp"
#include "ICameraView.hpp"

Camera::Camera():
	GameObject(),
	_eye(std::make_shared<Transform>())
{
	_eye->setPosition(glm::vec3{ 0, 0, 5 });
	getTransform()->addChild(_eye);
}

Camera::Camera(const std::shared_ptr<SharedMesh>& mesh):
	GameObject(mesh),
	_eye(std::make_shared<Transform>())
{
	getTransform()->addChild(_eye);
}

void Camera::update(float delta_time)
{
	auto viewMatrix = glm::inverse(_eye->getGlobalMatrix());
	for (auto& view : _views)
	{
		view->setViewMatrix(viewMatrix);
	}
}

void Camera::addView(const CameraViewPtr& cameraView)
{
	_views.push_back(cameraView);
}

void Camera::removeView(const CameraViewPtr& cameraView)
{
	auto foundIt = std::find(_views.begin(), _views.end(), cameraView);
	_views.erase(foundIt);
}
