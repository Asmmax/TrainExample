#pragma once
#include "Containers/Context.hpp"
#include <vector>
#include <memory>

class Component;
class GameObject;
class World;

using SceneObject = std::vector<std::shared_ptr<Component>>;
DECLARE_READER(SceneObject)

class SceneUnit
{
protected:
	using Ptr = std::shared_ptr<SceneUnit>;

protected:
	std::vector<SceneObject> _objects;

public:
	SceneUnit(const std::vector<SceneObject>& objects);

	std::vector<std::shared_ptr<GameObject>> attachTo(World& world);
	const std::vector<SceneObject>& getObjects() const { return _objects; }
};
