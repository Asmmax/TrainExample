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
	using CompPtr = std::shared_ptr<Component>;
	using ComopReaderPtr = std::shared_ptr<IReaderStrategy<CompPtr>>;

private:
	ComopReaderPtr _compReader;

public:
	SceneObjectReader(const ComopReaderPtr& compReader):
		_compReader(compReader)
	{
	}

	SceneObject Create(const nlohmann::json& node) override
	{
		SceneObject object;
		object.reserve(node.size());
		for (auto& child : node) {
			auto comp = _compReader->Create(child);
			object.push_back(comp);
		}
		return object;
	}

	void Init(const nlohmann::json& node) override
	{
		for (auto& child : node) {
			_compReader->Init(child);
		}
	}

	void PrepareCache(const nlohmann::json& node) override
	{
		for (auto& child : node) {
			_compReader->PrepareCache(child);
		}
	}

	void CleanupCache(const nlohmann::json& node) override
	{
		for (auto& child : node) {
			_compReader->CleanupCache(child);
		}
	}

	SceneObject CreateViaCache(const nlohmann::json& node) override
	{
		SceneObject object;
		object.reserve(node.size());
		for (auto& child : node) {
			auto comp = _compReader->CreateViaCache(child);
			object.push_back(comp);
		}
		return object;
	}

	void InitViaCache(const nlohmann::json& node) override
	{
		for (auto& child : node) {
			_compReader->InitViaCache(child);
		}
	}
};

template<>
std::shared_ptr<IReaderStrategy<SceneObject>> Context::GetReader()
{
	auto compReader = GetReader<std::shared_ptr<Component>>();
	return std::make_shared<SceneObjectReader>(compReader);
}
