#include "components/ManipulatorSwitcherAdder.hpp"
#include "components/ManipulatorSwitcher.hpp"
#include "systems/PlayerManager.hpp"
#include "World.hpp"

ManipulatorSwitcherAdder::ManipulatorSwitcherAdder(const ManipulatorPtr& manipulator):
	_manipulator(manipulator)
{
}

void ManipulatorSwitcherAdder::init()
{
	auto switcher = getOwner()->getWorld()->findComponent<ManipulatorSwitcher>();
	if (!switcher) {
		return;
	}
	switcher->addManipulator(_manipulator);
}
