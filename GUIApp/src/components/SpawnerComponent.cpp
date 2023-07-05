#include "components/SpawnerComponent.hpp"
#include "input/InputSystem.hpp"
#include "World.hpp"
#include "assets/AssetManager.hpp"
#include "assets/units/SceneUnit.hpp"

SpawnerComponent::SpawnerComponent(const std::string& trainId):
	_trainId(trainId)
{
}

void SpawnerComponent::init()
{
	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (!inputSystem) {
		return;
	}

	inputSystem->bindToActionPressed("Spawn", this, [this]() {spawn(); });
}

void SpawnerComponent::spawn()
{
	getOwner()->getWorld()->spawn(_trainId);
}
