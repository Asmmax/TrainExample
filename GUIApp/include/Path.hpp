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

private:
	void loadSettings(const std::string& settings);
};