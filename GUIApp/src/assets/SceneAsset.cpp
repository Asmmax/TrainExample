#include "assets/SceneAsset.hpp"
#include "assets/units/SceneUnit.hpp"
#include "World.hpp"

SceneAsset::SceneAsset(const std::vector<UnitPtr>& units):
	_units(units)
{
}

void SceneAsset::attachTo(World& world)
{
	for (auto& unit : _units) {
		unit->attachTo(world);
	}
}
