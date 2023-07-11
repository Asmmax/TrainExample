#include "systems/PlayerManager.hpp"
#include <assert.h>

PlayerManager::PlayerManager():
	_currentController(nullptr)
{
}

void PlayerManager::init()
{
}

void PlayerManager::setCurrentController(const ContollerPtr& contoller)
{
	assert(!_currentController);
	_currentController = contoller;
}
