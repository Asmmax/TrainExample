#pragma once
#include "components/AComponent.hpp"
#include <vector>
#include <memory>

class Transform;
class GameObject;
class ICameraView;

class CameraComponent : public Component
{
	using CameraViewPtr = std::shared_ptr<ICameraView>;

private:
	std::vector<CameraViewPtr> _views;
	std::shared_ptr<Transform> _transform;

public:
	CameraComponent();

	void init() override;
	void predraw() override;

	const std::shared_ptr<Transform>& getTransform() const { return _transform; }

	const std::vector<CameraViewPtr>& getViews() const { return _views; }
	void addView(const CameraViewPtr& cameraView);
	void removeView(const CameraViewPtr& cameraView);
};
