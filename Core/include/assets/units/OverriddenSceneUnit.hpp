#pragma once
#include "assets/units/SceneUnit.hpp"

class Component;

struct SceneObjectChange 
{
	using CompPtr = std::shared_ptr<Component>;

	unsigned int objectId;
	std::vector<CompPtr> overrides;
};

struct SceneUnitChange
{
	std::shared_ptr<SceneUnit> original;
	std::vector<SceneObjectChange> changes;
};

class OverriddenSceneUnit : public SceneUnit
{
	using CompPtr = std::shared_ptr<Component>;

public:
	OverriddenSceneUnit(const std::vector<SceneObject>& objects, const std::vector<SceneUnitChange>& units);

private:
	void addOverridenUnit(const Ptr& original, const std::vector<SceneObjectChange>& changes);
	static SceneObject overrideObject(const SceneObject& original, const std::vector<CompPtr>& overrides);
};
