#include "assets/units/SceneUnit.hpp"
#include "World.hpp"
#include "AComponent.hpp"

SceneUnit::SceneUnit(const std::vector<SceneObject>& objects):
	_objects(objects)
{
}

std::vector<std::shared_ptr<GameObject>> SceneUnit::attachTo(World& world)
{
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	gameObjects.reserve(_objects.size());

	for (auto& object : _objects) {
		auto newGameObject = world.createGameObject();
		gameObjects.push_back(newGameObject);
		for (auto& component : object) {
			component->attachTo(*newGameObject);
		}
	}

	return gameObjects;
}

class SceneObjectReader : public IReaderStrategy<SceneObject>
{
public:
	SceneObject Create(Context* context, const nlohmann::json& node) override
	{
		auto compReader = context->GetReader<std::shared_ptr<Component>>();
		SceneObject object;
		object.reserve(node.size());
		for (auto& child : node) {
			auto comp = compReader->Create(context, child);
			object.push_back(comp);
		}
		return object;
	}

	void Init(Context* context, const nlohmann::json& node) override
	{
		auto compReader = context->GetReader<std::shared_ptr<Component>>();
		for (auto& child : node) {
			compReader->Init(context, child);
		}
	}
};

template<>
std::shared_ptr<IReaderStrategy<SceneObject>> Context::GetReader()
{
	return std::make_shared<SceneObjectReader>();
}
