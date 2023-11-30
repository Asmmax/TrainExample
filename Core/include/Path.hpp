#pragma once
#include <string>
#include <vector>

class Path
{
private:
	std::vector<std::string> _resorcePaths;

public:
	explicit Path(const std::string& settings);

	std::string find(const std::string& localPath) const;
	std::string relative(const std::string& fullPath) const;
	std::vector<std::string> findByExtension(const std::string& extName) const;

	std::string toAssetId(const std::string& assetPath) const;

private:
	void loadSettings(const std::string& settings);
};