#include "ParallelCurve.hpp"
#include "ACurve.hpp"
#include <glm/glm.hpp>

ParallelCurve::ParallelCurve(const std::shared_ptr<ACurve>& base, const glm::vec3& offset):
	_base(base),
	_offset(offset)
{
}

glm::vec3 ParallelCurve::getValue(float parameter) const
{
	auto derivative = _base->getDerivative(parameter);
	auto z_dir = -glm::normalize(derivative);
	auto x_dir = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), z_dir));
	auto y_dir = glm::cross(z_dir, x_dir);

	return _base->getValue(parameter) + x_dir * _offset.x + y_dir * _offset.y + z_dir * _offset.z;
}

std::vector<glm::vec3> ParallelCurve::getValues(const std::vector<float>& params) const
{
	std::vector<glm::vec3> points;
	points.reserve(params.size());

	for (auto& param : params) {
		points.push_back(getValue(param));
	}

	return points;
}
