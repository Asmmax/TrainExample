#pragma once
#include "Path.hpp"
#include "DIAssets.hpp"
#include <string>
#include <memory>

class Loader;

class AssetManager
{
private:
	std::unique_ptr<Path> _path;
	Loader* _loader;

public:
	static AssetManager& getInstance();

	AssetManager();

	template<typename AssetType>
	std::shared_ptr<AssetType> getAsset(const std::string& assetId);

	template<typename AssetType>
	std::shared_ptr<AssetType> cloneAsset(const std::string& assetId);

	Loader* getLoader() { return _loader; }
	const Path& getPath() { return *_path; }

	void init(const std::string& config, Loader* loader);
};

template<typename AssetType>
std::shared_ptr<AssetType> AssetManager::getAsset(const std::string& assetId)
{
	return ContextManager::Instance().GetContext(assetId).GetContainer<AssetType>()->Get();
}

template<typename AssetType>
std::shared_ptr<AssetType> AssetManager::cloneAsset(const std::string& assetId)
{
	auto container = ContextManager::Instance().GetContext(assetId).GetContainer<AssetType>();

	auto firstId = container->GetFirstId();

	container->PrepareCache(firstId);
	container->FillCache(firstId);
	container->InitFromCache(firstId);
	auto result = container->GetFromCache(firstId);
	container->CleanupCache(firstId);

	return result;
}
