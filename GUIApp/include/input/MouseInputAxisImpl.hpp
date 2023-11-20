#pragma once
#include "input/AInputAxisImpl.hpp"

/// @serializable
enum class MouseAxis : int
{
	HORIZONTAL,
	VERTICAL,
	SCROLL
};

/// @serializable @polymorphic
class MouseInputAxisImpl : public AInputAxisImpl
{
private:
	MouseAxis _axis;
	float _sensitivity;

	double _lastXPos;
	double _lastYPos;
	double _xPos;
	double _yPos;
	double _scrollPos;

	bool _firstMousePos;

public:
	MouseInputAxisImpl(MouseAxis axis, float sensitivity, float smooth, float minSpeed);

	void init(InputDistributor* distributor) override;

	void resetMouse() override;

private:
	float getRawValue(float frameTime) const override;
	void setMousePos(double xPos, double yPos);
	void addMouseScroll(double step);
	void clear();
	float getDelta() const;
};
