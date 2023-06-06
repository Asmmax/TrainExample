#pragma once
#include "ICameraView.hpp"

class Texture;
class View;

class CameraViewImpl : public ICameraView
{
private:
	Texture* _fboTexture;
	View* _view;

	int _width;
	int _height;

public:
	CameraViewImpl();

	void resize(int width, int height);

	void init(Window* window) override;
	void render(const Model& model) override;
	void setViewMatrix(const glm::mat4& matrix) override;
};
