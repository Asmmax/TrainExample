#pragma once
#include "ComponentCommon.hpp"
#include <memory>
#include <vector>

class ICameraManipulator;

class PlayerController : public ComponentCommon<PlayerController>
{
private:
	using ManipulatorPtr = std::shared_ptr<ICameraManipulator>;
	ManipulatorPtr _target;
	bool _isInited;

public:
	PlayerController();

	void setManipulator(ManipulatorPtr target);

	ManipulatorPtr getManipulator() const { return _target; }

	void init() override;
	void update(float deltaTime) override;
};
