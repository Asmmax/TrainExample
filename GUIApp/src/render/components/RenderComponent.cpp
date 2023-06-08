#include "render/components/RenderComponent.hpp"
#include "common/components/TransformComponent.hpp"
#include "GameObject.hpp"
#include "World.hpp"
#include "render/RenderSystem.hpp"
#include "render/RenderObject.hpp"

RenderComponent::RenderComponent():
	_object(nullptr)
{
}

void RenderComponent::init()
{
	auto renderSystem = getOwner()->getWorld()->getSystem<RenderSystem>();
	if (!renderSystem) {
		return;
	}

	auto transformComp = getOwner()->getComponent<TransformComponent>();
	_object = renderSystem->createObject(_mesh, _material, transformComp->getTransform());
}

void RenderComponent::setMaterial(const std::shared_ptr<MaterialAsset>& material)
{
	_material = material;
	if (_object) {
		_object->setMaterial(_material);
	}
}

void RenderComponent::setMesh(const std::shared_ptr<MeshAsset>& mesh)
{
	_mesh = mesh;
	if (_object) {
		_object->setMesh(_mesh);
	}
}
