#pragma once
#include "AComponent.hpp"
#include <memory>
#include <vector>

class ICameraManipulator;

/// @serializable
class PlayerController : public ComponentCommon<PlayerController>
{
private:
	using ManipulatorPtr = std::shared_ptr<ICameraManipulator>;
	std::vector<ManipulatorPtr> _manipulators;
	ManipulatorPtr _target;

public:
	PlayerController(const std::vector<ManipulatorPtr>& manipulators);

	void init() override;
	void update(float deltaTime) override;

protected:
	void switchManipulator();
};