#include "assets/units/SceneUnit.hpp"
#include "World.hpp"
#include "AComponent.hpp"

SceneUnit::SceneUnit(const std::vector<SceneObject>& objects):
	_objects(objects)
{
}

void SceneUnit::attachTo(World& world)
{
	for (auto& object : _objects) {
		auto newGameObject = world.createGameObject();
		for (auto& component : object) {
			component->attachTo(*newGameObject);
		}
	}
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
