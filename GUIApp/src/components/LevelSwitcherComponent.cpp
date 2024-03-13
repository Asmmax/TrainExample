#include "components/LevelSwitcherComponent.hpp"
#include "input/InputSystem.hpp"
#include "World.hpp"
#include "systems/LevelManager.hpp"

void LevelSwitcherComponent::init()
{
	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (!inputSystem) {
		return;
	}

	inputSystem->bindToActionPressed("NextLevel", this, [this]() {nextLevel(); });
	inputSystem->bindToActionPressed("PrevLevel", this, [this]() {prevLevel(); });
}

void LevelSwitcherComponent::nextLevel()
{
	auto levelManager = getOwner()->getWorld()->getSystem<LevelManager>();
	if (!levelManager) {
		return;
	}

	levelManager->nextLevel();
}

void LevelSwitcherComponent::prevLevel()
{
	auto levelManager = getOwner()->getWorld()->getSystem<LevelManager>();
	if (!levelManager) {
		return;
	}

	levelManager->prevLevel();
}
