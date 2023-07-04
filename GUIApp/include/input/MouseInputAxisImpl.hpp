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
	float _smooth;
	float _minSpeed;
	float _value;

	double _lastXPos;
	double _lastYPos;
	double _xPos;
	double _yPos;
	double _scrollPos;

public:
	MouseInputAxisImpl(MouseAxis axis, float sensitivity, float smooth, float minSpeed);

	void init(InputDistributor* distributor) override;
	void update(float deltaTime) override;
	float getValue() const override;

private:
	void setMousePos(double xPos, double yPos);
	void addMouseScroll(double step);
	void clear();
	float getDelta() const;
};
