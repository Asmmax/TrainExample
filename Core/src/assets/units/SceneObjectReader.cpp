#include "assets/units/SceneObjectReader.hpp"
#include "AComponent.hpp"

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
