#pragma once
#include "AComponent.hpp"
#include <memory>
#include <vector>

class ICameraManipulator;

class ManipulatorSwitcherAdder : public ComponentCommon<ManipulatorSwitcherAdder>
{
private:
	using ManipulatorPtr = std::shared_ptr<ICameraManipulator>;
	ManipulatorPtr _manipulator;

public:
	ManipulatorSwitcherAdder(const ManipulatorPtr& manipulator);

	void init() override;
	void deinit() override;
};
