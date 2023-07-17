#include "components/ManipulatorSwitcher.hpp"
#include "components/ICameraManipulator.hpp"
#include "components/PlayerController.hpp"
#include "systems/PlayerManager.hpp"
#include "input/InputSystem.hpp"
#include "World.hpp"

ManipulatorSwitcher::ManipulatorSwitcher(const std::vector<ManipulatorPtr>& manipulators) :
	_manipulators(manipulators)
{
}

void ManipulatorSwitcher::init()
{
	auto inputSystem = getOwner()->getWorld()->getSystem<InputSystem>();
	if (inputSystem) {
		inputSystem->bindToActionPressed("SwitchManipulator", this, [this]() {switchManipulator(); });
	}
}

void ManipulatorSwitcher::addManipulator(ManipulatorPtr manipulator)
{
	_manipulators.push_back(manipulator);
}

void ManipulatorSwitcher::removeManipulator(ManipulatorPtr manipulator)
{
	auto foundIt = std::find(_manipulators.begin(), _manipulators.end(), manipulator);
	if (foundIt == _manipulators.end()) {
		return;
	}
	_manipulators.erase(foundIt);

	auto playerManager = getOwner()->getWorld()->getSystem<PlayerManager>();
	if (playerManager) {
		auto controller = playerManager->getCurrentController();
		if (controller->getManipulator() == manipulator) {
			switchManipulator();
		}
	}
}

void ManipulatorSwitcher::switchManipulator()
{
	auto playerManager = getOwner()->getWorld()->getSystem<PlayerManager>();
	if (!playerManager) {
		return;
	}

	auto controller = playerManager->getCurrentController();

	if (_manipulators.empty()) {
		controller->setManipulator(nullptr);
		return;
	}

	auto foundIt = std::find(_manipulators.begin(), _manipulators.end(), controller->getManipulator());
	if (foundIt != _manipulators.end()) {
		foundIt++;
	}
	ManipulatorPtr target = nullptr;
	if (foundIt == _manipulators.end()) {
		target = _manipulators.front();
	}
	else {
		target = *foundIt;
	}

	controller->setManipulator(target);
	target->apply();
}
