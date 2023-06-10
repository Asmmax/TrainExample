#include "render/components/CameraComponent.hpp"
#include "common/components/TransformComponent.hpp"
#include "common/Transform.hpp"
#include "GameObject.hpp"
#include "World.hpp"
#include "render/RenderSystem.hpp"
#include "render/CameraView.hpp"

CameraComponent::CameraComponent(bool isMain):
	_isMainInited(isMain)
{
}

void CameraComponent::init()
{
	auto renderSystem = getOwner()->getWorld()->getSystem<RenderSystem>();
	if (!renderSystem) {
		return;
	}

	auto transformComp = getOwner()->getComponent<TransformComponent>();
	_view = renderSystem->createCameraView(transformComp->getTransform());
	
	if (_isMainInited) {
		renderSystem->setMainView(_view);
	}
}

void CameraComponent::setMain()
{
	_isMainInited = true;

	auto renderSystem = getOwner()->getWorld()->getSystem<RenderSystem>();
	if (!renderSystem) {
		return;
	}

	if (_view) {
		renderSystem->setMainView(_view);
	}
}
