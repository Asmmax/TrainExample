#include "systems/LevelManager.hpp"
#include "World.hpp"

LevelManager::LevelManager(const std::vector<std::string>& levels, const std::string& currentLevel) :
	_levels(levels),
	_currentLevel(0)
{
	for (size_t idx = 0; idx < _levels.size(); idx++) {
		if (_levels[idx] == currentLevel) {
			_currentLevel = idx;
			break;
		}
	}
}

void LevelManager::init()
{
	if (!_levels.empty()) {
		getWorld()->loadScene(_levels[_currentLevel]);
	}
}

void LevelManager::nextLevel()
{
	if (_currentLevel == _levels.size() - 1) {
		_currentLevel = 0;
	}
	else {
		_currentLevel++;
	}
	getWorld()->loadScene(_levels[_currentLevel]);
}

void LevelManager::prevLevel()
{
	if (_currentLevel == 0) {
		_currentLevel = _levels.size() - 1;
	}
	else {
		_currentLevel--;
	}
	getWorld()->loadScene(_levels[_currentLevel]);
}

