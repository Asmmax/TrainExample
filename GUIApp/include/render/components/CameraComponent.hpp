#pragma once
#include "AComponent.hpp"
#include <vector>
#include <memory>

class Transform;
class GameObject;
class CameraView;

class CameraComponent : public Component
{
private:
	std::shared_ptr<CameraView> _view;
	bool _isMainInited;

public:
	CameraComponent();

	void init() override;

	void setMain();
};
