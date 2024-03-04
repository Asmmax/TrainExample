#pragma once
#include "SystemCommon.hpp"

class PlayerController;

class PlayerManager : public SystemCommon<PlayerManager>
{
private:
	PlayerController* _currentController;

public:
	PlayerManager();

	void init() override;

	void setCurrentController(PlayerController* controller);
	PlayerController* getCurrentController() const { return _currentController; }
};
