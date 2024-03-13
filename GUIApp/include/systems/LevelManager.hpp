#pragma once
#include "SystemCommon.hpp"
#include <vector>
#include <string>

class World;

class LevelManager : public SystemCommon<LevelManager>
{
private:
	std::vector<std::string> _levels;
	size_t _currentLevel;

public:
	LevelManager(const std::vector<std::string>& levels, const std::string& currentLevel);

	void init() override;

	void nextLevel();
	void prevLevel();
};
