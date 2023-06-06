#pragma once
#include "ICameraView.hpp"
#include <memory>

class Transform;

class CameraView
{
private:
	std::shared_ptr<ICameraView> _slaveImpl;
	std::shared_ptr<ICameraView> _impl;
	std::shared_ptr<Transform> _transform;

public:
	CameraView(const std::shared_ptr<Transform>& transform);

	void init(Window* window);
	void update();
	void render(const Model& model);

	void setSlave();
	void setMain();
};
