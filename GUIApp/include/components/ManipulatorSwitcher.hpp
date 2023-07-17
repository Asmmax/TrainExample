#pragma once
#include "AComponent.hpp"
#include <memory>
#include <vector>

class ICameraManipulator;

/// @serializable
class ManipulatorSwitcher : public ComponentCommon<ManipulatorSwitcher>
{
private:
	using ManipulatorPtr = std::shared_ptr<ICameraManipulator>;
	std::vector<ManipulatorPtr> _manipulators;

public:
	ManipulatorSwitcher(const std::vector<ManipulatorPtr>& manipulators);

	void init() override;
	void addManipulator(ManipulatorPtr manipulator);
	void removeManipulator(ManipulatorPtr manipulator);

protected:
	void switchManipulator();
};
