#include "Path.hpp"
#include <fstream>
#include <filesystem>
#include <array>

Path::Path(const std::string& settings)
{
	loadSettings(settings);
}

std::string Path::find(const std::string& localPath) const
{
	for (auto& path : _resorcePaths) {
		std::filesystem::path fullPath(path);
		fullPath /= localPath;
		fullPath.make_preferred();
		if (std::filesystem::exists(fullPath)) {
			return fullPath.string();
		}
	}
	return std::string();
}

std::string Path::relative(const std::string& fullPath) const
{
	for (auto& path : _resorcePaths) {
		std::filesystem::path basePath(path);
		std::filesystem::path fullPath(fullPath);

		auto parent = fullPath.parent_path();
		while (!parent.empty() && parent != basePath) {
			parent = parent.parent_path();
		}
		
		if (parent.empty()) {
			continue;
		}

		auto relPath = std::filesystem::relative(fullPath, basePath);
		relPath.make_preferred();
		return relPath.string();
	}
	return std::string();
}

std::vector<std::string> Path::findByExtension(const std::string& extName) const
{
	std::vector<std::string> result;
	for (auto& basePath : _resorcePaths) {
		for (const auto& file : std::filesystem::recursive_directory_iterator(basePath)) {
			if (file.is_directory()) {
				continue;
			}
			const auto path = file.path().lexically_normal();
			if (path.extension() == extName) {
				result.push_back(path.string());
			}
		}
	}
	return result;
}

std::string Path::toAssetId(const std::string& assetPath) const
{
	auto relPath = relative(assetPath);
	std::filesystem::path relativePath(relPath);

	auto assetId = relativePath.replace_extension().string();
	std::replace(assetId.begin(), assetId.end(), '\\', '/');
	return assetId;
}

void Path::loadSettings(const std::string& settings)
{
	std::ifstream file;
	file.open(settings);

	if (!file.is_open()) {
		std::string settingsPath = std::filesystem::current_path().string() + "/" + settings;
		std::string errorMessage = "Settings file: " + settingsPath + " could not be open!\n";
		fprintf(stderr, errorMessage.c_str());
		return;
	}

	_resorcePaths.clear();
	for (std::array<char, 256> pathBuff; file.getline(&pathBuff[0], 256);)
		_resorcePaths.emplace_back(pathBuff.data());

	file.close();
}
