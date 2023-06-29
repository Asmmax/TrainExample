#pragma once
#include "assets/units/SceneUnit.hpp"

class Component;

/// @serializable
struct SceneObjectChange 
{
	using CompPtr = std::shared_ptr<Component>;

	unsigned int objectId;
	std::vector<CompPtr> overrides;
};

/// @serializable
struct SceneUnitChange
{
	std::shared_ptr<SceneUnit> original;
	std::vector<SceneObjectChange> changes;
};

/// @serializable
class OverriddenSceneUnit : public SceneUnit
{
	using CompPtr = std::shared_ptr<Component>;

public:
	OverriddenSceneUnit(const std::vector<SceneObject>& objects, const std::vector<SceneUnitChange>& units);

private:
	void addOverridenUnit(const Ptr& original, const std::vector<SceneObjectChange>& changes);
	static SceneObject overrideObject(const SceneObject& original, const std::vector<CompPtr>& overrides);
};
