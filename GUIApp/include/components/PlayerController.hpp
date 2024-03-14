#pragma once
#include "ComponentCommon.hpp"

class ICameraManipulator;

class PlayerController : public ComponentCommon<PlayerController>
{
private:
	ICameraManipulator* _target;
	bool _isInited;

public:
	PlayerController();

	void setManipulator(ICameraManipulator* target);

	ICameraManipulator* getManipulator() const { return _target; }

	void init() override;
	void update(float deltaTime) override;
	void deinit() override;
};
