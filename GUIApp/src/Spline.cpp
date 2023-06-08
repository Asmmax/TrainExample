#include "Spline.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/spline.hpp"

Spline::Spline(const std::vector<glm::vec3>& points, bool loop, unsigned int accuracy):
	_points(points),
	_is_loop(loop),
	_part(0.0f),
	_seg_count(0),
	_accuracy(accuracy)
{

	unsigned int points_count = static_cast<unsigned int>(_points.size());
	_seg_count = _is_loop ? points_count : points_count - 1;

	_part = 1.0f / _seg_count;
}

glm::vec3 Spline::getValue(float parameter) const
{
	auto spline_part = getSplinePart(parameter);
	return glm::catmullRom(spline_part.point_0, spline_part.point_1, spline_part.point_2, spline_part.point_3, spline_part.parameter);
}

glm::vec3 Spline::getDerivative(float parameter) const
{
	auto spline_part = getSplinePart(parameter);

	float p = spline_part.parameter;
	float p2 = spline_part.parameter * spline_part.parameter;

	float f1 = -3 * p2 + 4 * p - 1;
	float f2 = 9 * p2 - 10 * p;
	float f3 = -9 * p2 + 8 * p + 1;
	float f4 = 3 * p2 - 2 * p;

	return (f1 * spline_part.point_0 + f2 * spline_part.point_1 + f3 * spline_part.point_2 + f4 * spline_part.point_3) * 0.5f / _part;
}

bool Spline::isLoop() const
{
	return _is_loop;
}

float Spline::getLength() const
{
	return getNumericalLength(_accuracy * _seg_count);
}

Spline::SplinePart Spline::getSplinePart(float parameter) const
{
	unsigned int seg_id = static_cast<unsigned int>(std::floor(parameter / _part));
	if (seg_id >= _seg_count) {
		seg_id = _seg_count - 1;
	}

	unsigned int points_count = static_cast<unsigned int>(_points.size());

	SplinePart spline_part;
	spline_part.parameter = (parameter - seg_id * _part) / _part;
	spline_part.point_0 = _points[(seg_id - 1) % points_count];
	spline_part.point_1 = _points[seg_id];
	spline_part.point_2 = _points[(seg_id + 1) % points_count];
	spline_part.point_3 = _points[(seg_id + 2) % points_count];
	return spline_part;
}
