#pragma once

class Window;

class InputController
{
private:
	double _scrollSpeed;

	double _lastXPos;
	double _lastYPos;
	double _xPos;
	double _yPos;
	double _scrollPos;

	bool _isRightButtonPressed;
	bool _isLeftButtonPressed;

public:
	explicit InputController(double scrollSpeed = 1.2);
	void bind(Window* window);

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