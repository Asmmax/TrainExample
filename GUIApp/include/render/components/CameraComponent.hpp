#pragma once
#include "AComponent.hpp"
#include <vector>
#include <memory>

class Transform;
class GameObject;
class CameraView;

/// @serializable
class CameraComponent : public ComponentCommon<CameraComponent>
{
private:
	std::shared_ptr<CameraView> _view;
	bool _isMainInited;

public:
	CameraComponent(bool isMain = false);

	void init() override;
	void deinit() override;

	void setMain();
};
