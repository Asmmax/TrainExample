#pragma once
#include "DynamicObject.hpp"
#include <vector>

class Transform;
class ICameraView;

class Camera : public GameObject
{
	using CameraViewPtr = std::shared_ptr<ICameraView>;

private:
	std::vector<CameraViewPtr> _views;
	std::shared_ptr<Transform> _eye;

public:
	Camera();
	Camera(const std::shared_ptr<SharedMesh>& mesh);

	void update(float delta_time) override;

	const std::shared_ptr<Transform>& getEye() const { return _eye; }

	const std::vector<CameraViewPtr>& getViews() const { return _views; }
	void addView(const CameraViewPtr& cameraView);
	void removeView(const CameraViewPtr& cameraView);
};
