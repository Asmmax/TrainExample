#pragma once
#include "ComponentCommon.hpp"

class LevelSwitcherComponent : public ComponentCommon<LevelSwitcherComponent>
{
public:
	void init() override;

protected:
	void nextLevel();
	void prevLevel();
};
