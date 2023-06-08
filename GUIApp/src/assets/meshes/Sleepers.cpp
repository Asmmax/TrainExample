#include "assets/meshes/Sleepers.hpp"
#include "MeshGenerator.hpp"
#include "ACurve.hpp"
#include "ParallelCurve.hpp"

Sleepers::Sleepers(const std::shared_ptr<ACurve>& path, float thickness, float width, float step)
{
	float length = path->getLength();
	int seg_count = static_cast<int>(std::roundf(length / step));

	auto parameters = path->getUniformDistribution(seg_count + 1);

	MeshGenerator generator;

	ParallelCurve left_backward(path, glm::vec3(-width / 2, 0, thickness / 2));
	ParallelCurve left_forward(path, glm::vec3(-width / 2, 0, -thickness / 2));

	std::vector<glm::vec3> left;
	left.reserve(parameters.size() * 2);
	for (auto param : parameters) {
		left.push_back(left_backward.getValue(param));
		left.push_back(left_forward.getValue(param));
	}

	ParallelCurve right_backward(path, glm::vec3(width / 2, 0, thickness / 2));
	ParallelCurve right_forward(path, glm::vec3(width / 2, 0, -thickness / 2));

	std::vector<glm::vec3> right;
	right.reserve(parameters.size() * 2);
	for (auto param : parameters) {
		right.push_back(right_backward.getValue(param));
		right.push_back(right_forward.getValue(param));
	}

	generator.meshPoints(left, right);

	_data = generator.getMeshData();
}
