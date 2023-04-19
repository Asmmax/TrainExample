#pragma once
#include "ACurve.h"
#include <glm/vec3.hpp>

class Circle2D : public ACurve
{
public:
	Circle2D(const glm::vec3& center, float radius, float parameter_distorsion = 0.0f);

	virtual glm::vec3 getValue(float parameter) const override;
	virtual glm::vec3 getDerivative(float parameter) const override;
	virtual bool isLoop() const override;
	virtual float getLength() const override;

private:
	glm::vec3 _center;
	float _radius;
};
