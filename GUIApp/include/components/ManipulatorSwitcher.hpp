#pragma once
#include "ComponentCommon.hpp"
#include <vector>

class ICameraManipulator;

class ManipulatorSwitcher : public ComponentCommon<ManipulatorSwitcher>
{
private:
	std::vector<ICameraManipulator*> _manipulators;

public:
	ManipulatorSwitcher(const std::vector<ICameraManipulator*>& manipulators);

	void init() override;
	void addManipulator(ICameraManipulator* manipulator);
	void removeManipulator(ICameraManipulator* manipulator);

protected:
	void switchManipulator();
};
