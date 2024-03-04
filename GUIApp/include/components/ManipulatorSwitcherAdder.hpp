#pragma once
#include "ComponentCommon.hpp"

class ICameraManipulator;

class ManipulatorSwitcherAdder : public ComponentCommon<ManipulatorSwitcherAdder>
{
private:
	ICameraManipulator* _manipulator;

public:
	ManipulatorSwitcherAdder(ICameraManipulator* manipulator);

	void init() override;
	void deinit() override;
};
