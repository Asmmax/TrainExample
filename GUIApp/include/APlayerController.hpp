#pragma once
#include <memory>

class InputController;

class APlayerController
{
public:
	virtual void init(const std::shared_ptr<InputController>& input) = 0;
	virtual void update(float deltaTime) = 0;
};
