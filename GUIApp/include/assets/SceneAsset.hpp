#pragma once
#include "Containers/Context.hpp"
#include <vector>
#include <memory>

class Component;
class World;

/// @serializable @shared scenes
class SceneAsset
{
	using ComponentPtr = std::shared_ptr<Component>;
public:
	using SceneUnit = std::vector<ComponentPtr>;

private:
	std::vector<SceneUnit> _units;

public:
	SceneAsset();

	/// @inject
	void setUnits(const std::vector<SceneUnit>& objects);

	void attachTo(World& world);
};

DECLARE_READER(SceneAsset::SceneUnit)
