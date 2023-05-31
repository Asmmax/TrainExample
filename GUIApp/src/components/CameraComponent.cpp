#include "components/CameraComponent.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "ICameraView.hpp"

CameraComponent::CameraComponent():
	_transform(std::make_shared<Transform>())
{
}

void CameraComponent::init()
{
}

void CameraComponent::predraw()
{
	auto viewMatrix = glm::inverse(_transform->getGlobalMatrix());
	for (auto& view : _views)
	{
		view->setViewMatrix(viewMatrix);
	}
}

void CameraComponent::addView(const CameraViewPtr& cameraView)
{
	_views.push_back(cameraView);
}

void CameraComponent::removeView(const CameraViewPtr& cameraView)
{
	auto foundIt = std::find(_views.begin(), _views.end(), cameraView);
	_views.erase(foundIt);
}
