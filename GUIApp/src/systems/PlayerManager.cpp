#include "systems/PlayerManager.hpp"
#include <assert.h>

PlayerManager::PlayerManager():
	_currentController(nullptr)
{
}

void PlayerManager::init()
{
}

void PlayerManager::setCurrentController(PlayerController* controller)
{
	_currentController = controller;
}
