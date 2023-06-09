#include "assets/SystemGroupAsset.hpp"
#include "ASystem.hpp"

SystemGroupAsset::SystemGroupAsset()
{
}

void SystemGroupAsset::setSystems(const std::vector<SystemPtr>& systems)
{
	_systems = systems;
}

void SystemGroupAsset::init(Window* window)
{
	for (auto& sys : _systems) {
		sys->setWindow(window);
	}
}

void SystemGroupAsset::attachTo(World& world)
{
	for (auto& sys : _systems) {
		sys->attachTo(world);
	}
}
