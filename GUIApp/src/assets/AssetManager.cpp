#include "assets/AssetManager.hpp"
#include "Containers/ContextManagerImpl.hpp"

AssetManager& AssetManager::getInstance()
{
	static AssetManager instance;
	return instance;
}

AssetManager::AssetManager():
	_loader(nullptr)
{
}

void AssetManager::setLoader(Loader* loader)
{
	_loader = loader;
}

void AssetManager::init(const std::string& config)
{
	ContextManager::Instance().BindImpl(std::make_shared<ContextManagerImpl>());

	_path = std::make_unique<Path>(config);

	auto assets = _path->findByExtension(".asset");
	for (auto& assetPath : assets) {
		auto jsonAsset = SettingsLoader::LoadJson(assetPath);
		auto rawContextId = _path->toAssetId(assetPath);
		auto contextId = SettingsLoader::ReadContextId(jsonAsset, rawContextId);
		ContextManager::Instance().AddRoot(jsonAsset, contextId);
	}
	ContextManager::Instance().Read();
	ContextManager::Instance().Resolve();
}
