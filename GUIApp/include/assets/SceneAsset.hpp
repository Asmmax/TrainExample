#pragma once
#include <memory>
#include <vector>

class World;
class SceneUnit;

class SceneAsset
{
	using UnitPtr = std::shared_ptr<SceneUnit>;

private:
	std::vector<UnitPtr> _units;

public:
	SceneAsset(const std::vector<UnitPtr>& units);

	void attachTo(World& world);
};
