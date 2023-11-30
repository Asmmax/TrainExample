#pragma once
#include <glm/mat4x4.hpp>

class Window;
class Model;

class ICameraView
{
public:
	virtual ~ICameraView() {}
	virtual void init(Window* window) = 0;
	virtual void deinit(Window* window) = 0;
	virtual void render(const Model& model) = 0;
	virtual void setViewMatrix(const glm::mat4& matrix) = 0;
};
