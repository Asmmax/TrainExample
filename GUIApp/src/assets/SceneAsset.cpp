#include "assets/SceneAsset.hpp"
#include "GameObject.hpp"
#include "World.hpp"
#include "AComponent.hpp"

SceneAsset::SceneAsset()
{
}

void SceneAsset::setUnits(const std::vector<SceneUnit>& objects)
{
	_units = objects;
}

void SceneAsset::attachTo(World& world)
{
	for (auto& unit : _units) {
		auto object = world.createGameObject();
		for (auto& comp : unit) {
			comp->attachTo(*object);
		}
	}
}

class SceneUnitReader : public IReaderStrategy<SceneAsset::SceneUnit>
{
	using ComponentPtr = std::shared_ptr<Component>;
	using ComponentReaderPtr = std::shared_ptr<IReaderStrategy<ComponentPtr>>;

private:
	ComponentReaderPtr _compReader;

public:
	SceneUnitReader(const ComponentReaderPtr& compReader) :
		_compReader(compReader)
	{
	}

	SceneAsset::SceneUnit Create(const nlohmann::json& node) override
	{
		std::vector<ComponentPtr> components;
		components.reserve(node.size());
		for (auto& child : node) {
			auto comp = _compReader->Create(child);
			components.push_back(comp);
		}
		return components;
	}

	void Init(const nlohmann::json& node) override
	{
		for (auto& child : node) {
			_compReader->Init(child);
		}
	}
};


template<>
std::shared_ptr<IReaderStrategy<SceneAsset::SceneUnit>> Context::GetReader()
{
	auto compReader = GetReader<std::shared_ptr<Component>>();
	return std::make_shared<SceneUnitReader>(compReader);
}
