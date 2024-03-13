#include "components/SpawnerComponent.hpp"
#include "input/InputSystem.hpp"
#include "World.hpp"

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

void SpawnerComponent::deinit()
{
	World* world = getOwner()->getWorld();

	for (auto& task : _delayTasks) {
		if (world->isValidTask(task.taskId)) {
			getOwner()->getWorld()->stop(task.taskId);
			for (const auto& go : task.spawnedObjects) {
				if (const auto ptr = go.lock()) {
					world->removeGameObject(ptr);
				}
			}
		}
	}
	_delayTasks.clear();

	Super::deinit();
}

void SpawnerComponent::spawn()
{
	auto& task = _delayTasks.emplace_back();
	auto currentIt = --_delayTasks.end();
	task.spawnedObjects = getOwner()->getWorld()->spawn(_trainId);
	task.taskId = getOwner()->getWorld()->delay(_delay, [this, currentIt](World* world) {
		for (const auto& go : currentIt->spawnedObjects) {
			if (const auto ptr = go.lock()) {
				world->removeGameObject(ptr);
			}
		}
		_delayTasks.erase(currentIt);
	});
}
