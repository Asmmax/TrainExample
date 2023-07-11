#pragma once
#include "ASystem.hpp"
#include <memory>

class PlayerController;

/// @serializable
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
