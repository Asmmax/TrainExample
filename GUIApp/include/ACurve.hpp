#pragma once
#include "Vec3Reader.hpp"
#include <vector>
#include <glm/vec3.hpp>

/// @serializable @abstract @shared curves
class ACurve
{
public:
	virtual ~ACurve() = default;

	std::vector<float> getUniformDistribution(unsigned int points_count, unsigned int accuracy = 10) const;
	float getNumericalLength(unsigned int accuracy = 100) const;
	float getNextParamByStep(float current_param, float step, unsigned int accuracy = 10) const;

	virtual glm::vec3 getValue(float parameter) const = 0;
	virtual glm::vec3 getDerivative(float parameter) const = 0;
	virtual bool isLoop() const = 0;
	virtual float getLength() const = 0;
};
