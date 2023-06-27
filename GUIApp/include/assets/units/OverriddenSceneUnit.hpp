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
class OverriddenSceneUnit : public SceneUnit
{
	using CompPtr = std::shared_ptr<Component>;

private:
	Ptr _original;

public:
	/// @inject @prototyping original
	OverriddenSceneUnit(const Ptr& original, const std::vector<SceneObjectChange>& changes, const std::vector<SceneObject>& objects);

private:
	static SceneObject overrideObject(const SceneObject& original, const std::vector<CompPtr>& overrides);
};
