#include "Circle2D.hpp"

#include <glm/trigonometric.hpp>
#include <glm/ext/scalar_constants.hpp>

Circle2D::Circle2D(const glm::vec3& center, float radius, float parameter_distorsion) :
	_center(center),
	_radius(radius)
{
}

glm::vec3 Circle2D::getValue(float parameter) const
{
	float radians = parameter * 2 * glm::pi<float>();
	glm::vec3 point(glm::sin(radians) * _radius, 0.0f, glm::cos(radians) * _radius);
	return point + _center;
}

glm::vec3 Circle2D::getDerivative(float parameter) const
{
	float radians = parameter * 2 * glm::pi<float>();
	return glm::vec3(2 * glm::pi<float>() * glm::cos(radians) * _radius, 0.0f, -2 * glm::pi<float>() * glm::sin(radians) * _radius);
}

bool Circle2D::isLoop() const
{
	return true;
}

float Circle2D::getLength() const
{
	return 2 * glm::pi<float>() * _radius;
}
