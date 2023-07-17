#include "components/SpawnerComponent.hpp"
#include "input/InputSystem.hpp"
#include "World.hpp"
#include "assets/AssetManager.hpp"
#include "assets/units/SceneUnit.hpp"

SpawnerComponent::SpawnerComponent(const std::string& trainId, float delay):
	_trainId(trainId),
	_delay(delay)
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
	auto gameObjects = getOwner()->getWorld()->spawn(_trainId);
	getOwner()->getWorld()->delay(_delay, [gameObjects](World* world) {
		for (const auto& go : gameObjects) {
			world->removeGameObject(go);
		}
		});
}
