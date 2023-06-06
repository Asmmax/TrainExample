#pragma once
#include "ASystem.hpp"

class Window;

class InputSystem : public System
{
private:
	Window* _window;

	double _scrollSpeed;

	double _lastXPos;
	double _lastYPos;
	double _xPos;
	double _yPos;
	double _scrollPos;

	bool _isRightButtonPressed;
	bool _isLeftButtonPressed;

	bool _mouseCaptured;

public:
	explicit InputSystem(Window* window);

	void init() override;
	void update(float delta_time) override;
	void draw() override;

	void setScrollSpeed(double scrollSpeed);
	void setMouseCaptureWhilePressed(bool flag = true);

	bool isRightButtonPressed() const { return _isRightButtonPressed; }
	bool isLeftButtonPressed() const { return _isLeftButtonPressed; }

	double GetXDelta() const { return _xPos - _lastXPos; }
	double GetYDelta() const { return _yPos - _lastYPos; }

	double GetScrollDelta() const;

protected:
	void setMousePos(double xPos, double yPos);
	void addMouseScroll(double step);
	void clear();
};
