#include "Path.hpp"
#include <fstream>
#include <filesystem>
#include <array>

Path::Path(const std::string& settings)
{
	loadSettings(settings);
}

std::string Path::find(const std::string& localPath)
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

void Path::loadSettings(const std::string& settings)
{
	std::ifstream file;
	file.open(settings);

	if (!file.is_open()) {
		std::string settingsPath = std::filesystem::current_path().string() + "/settings.dat";
		std::string errorMessage = "Settings file: " + settingsPath + " could not be open!\n";
		fprintf(stderr, errorMessage.c_str());
		return;
	}

	_resorcePaths.clear();
	for (std::array<char, 256> pathBuff; file.getline(&pathBuff[0], 256);)
		_resorcePaths.emplace_back(pathBuff.data());

	file.close();
}
