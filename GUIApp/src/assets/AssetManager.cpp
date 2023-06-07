#include "assets/AssetManager.hpp"

AssetManager& AssetManager::getInstance()
{
	static AssetManager instance;
	return instance;
}

AssetManager::AssetManager():
	_loader(nullptr)
{
}

void AssetManager::init(const std::string& config, Loader* loader)
{
	_path = std::make_unique<Path>(config);
	_loader = loader;

	auto assets = _path->findByExtension(".asset");
	for (auto& assetPath : assets) {
		auto jsonAsset = SettingsLoader::LoadJson(assetPath);
		auto rawContextId = _path->toAssetId(assetPath);
		auto contextId = SettingsLoader::ReadContextId(jsonAsset, rawContextId);
		ContextManager::Instance().AddRoot(jsonAsset, contextId);
	}
	ContextManager::Instance().Read();
}
