#pragma once
#include <glm/vec3.hpp>
#include <memory>
#include <vector>

class ACurve;

//Эквидистанта к произвольной параметрической кривой
class ParallelCurve
{
public:
	ParallelCurve(ACurve* base, const glm::vec3& offset);

	glm::vec3 getValue(float parameter) const;
	std::vector<glm::vec3> getValues(const std::vector<float>& params) const;

private:
	ACurve* _base;
	glm::vec3 _offset;
};
