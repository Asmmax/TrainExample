#pragma once
#include "SystemCommon.hpp"
#include <memory>

class PlayerController;

class PlayerManager : public SystemCommon<PlayerManager>
{
	using ContollerPtr = std::shared_ptr<PlayerController>;

private:
	ContollerPtr _currentController;

public:
	PlayerManager();

	void init() override;

	void setCurrentController(const ContollerPtr& contoller);
	ContollerPtr getCurrentController() const { return _currentController; }
};
