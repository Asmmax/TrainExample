#include "ACurve.hpp"
#include <glm/glm.hpp>

std::vector<float> ACurve::getUniformDistribution(unsigned int points_count, unsigned int accuracy) const
{
	unsigned int seg_count = isLoop() ? points_count : points_count - 1;
	assert(seg_count > 0);

	float length = getLength();
	float h = length / seg_count;

	std::vector<float> points;
	points.reserve(points_count);

	float paramter = 0.0f;
	points.push_back(0.0f);

	for (unsigned int i = 1; i < points_count; i++) {
		paramter = getNextParamByStep(paramter, h, accuracy);
		paramter = glm::clamp(paramter, 0.0f, 1.0f);
		points.push_back(paramter);
	}
	return points;
}

float ACurve::getNumericalLength(unsigned int accuracy) const
{
	float step = 1.0f / (2 * accuracy);

	float sum = glm::length(getDerivative(0.0f)) + glm::length(getDerivative(1.0f));

	float parameter = 0.0f;
	for (unsigned int i = 1; i < 2*accuracy; i++) {
		parameter += step;
		sum += ((i % 2 == 0) ? 2.0f : 4.0f) * glm::length(getDerivative(parameter));
	}

	return sum * step / 3.0f;
}

float ACurve::getNextParamByStep(float current_param, float step, unsigned int accuracy) const
{
	float dh = step / accuracy;

	float paramter = current_param;
	for (unsigned int i = 0; i < accuracy; i++) {
		paramter += dh / glm::length(getDerivative(paramter));
	}
	return paramter;
}
