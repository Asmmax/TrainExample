#pragma once
#include "ACurve.hpp"

/// @serializable
class Spline : public ACurve
{
public:
	Spline(const std::vector<glm::vec3>& points, bool loop, unsigned int accuracy = 5);

	virtual glm::vec3 getValue(float parameter) const override;
	virtual glm::vec3 getDerivative(float parameter) const override;
	virtual bool isLoop() const override;
	virtual float getLength() const override;

private:
	class SplinePart
	{
	public:
		float parameter = 0.0f;
		glm::vec3 point_0;
		glm::vec3 point_1;
		glm::vec3 point_2;
		glm::vec3 point_3;
	};

	SplinePart getSplinePart(float parameter) const;

private:
	std::vector<glm::vec3> _points;
	bool _is_loop;
	float _part;
	unsigned int _seg_count;
	unsigned int _accuracy;
};

