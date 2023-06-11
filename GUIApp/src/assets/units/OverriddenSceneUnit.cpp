#include "assets/units/OverriddenSceneUnit.hpp"
#include "AComponent.hpp"
#include "World.hpp"
#include <algorithm>

OverriddenSceneUnit::OverriddenSceneUnit(const Ptr& original, const std::vector<SceneObjectChange>& changes, const std::vector<SceneObject>& objects):
	SceneUnit(objects),
	_original(original)
{
	auto& origObjects = _original->getObjects();
	for (size_t objectId = 0; objectId < origObjects.size(); objectId++) {
		auto foundChange = std::find_if(changes.begin(), changes.end(), [objectId](const SceneObjectChange& change) {
			return change.objectId == objectId;
			});
		if (foundChange == changes.end()) {
			_objects.push_back(origObjects[objectId]);
			continue;
		}

		auto newObject = overrideObject(origObjects[objectId], foundChange->overrides);
		_objects.push_back(newObject);
	}
}

SceneObject OverriddenSceneUnit::overrideObject(const SceneObject& original, const std::vector<CompPtr>& overrides)
{
	SceneObject result(original);

	for (auto& overrideComp : overrides) {
		auto foundIt = std::find_if(result.begin(), result.end(), [overrideComp](auto& currentComp) {
			return currentComp->isSameType(overrideComp.get());
			});
		if (foundIt != result.end()) {
			*foundIt = overrideComp;
		}
	}
	return result;
}
